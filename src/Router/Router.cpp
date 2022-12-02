/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "Router.hpp"

Router::Router() {

}

Router::~Router() {
  
}

char Router::findGroupByCountry(std::string country){
  char group = 'X';
  bool found = false;
  auto pp = this->groupsTable.begin();
  for(;  pp != this->groupsTable.end() && !found ; ++pp){
    for(std::string countryCode : pp->second){
      if(countryCode == country){
        group = pp->first[0];//first char of the string because groups
                            // are single letters
        found = true;
      }
    }
  }
  return group;
}

void Router::fillGroupsTable(std::string fileName) {
  json groups;
  json jsonData;
  int firstChar;
  std::ifstream file;
  std::string line = "";
  std::string data = "";

  file.open(fileName, std::ios::in);
  while (getline(file, line)) 
    data += line;
  // remove http headers
  firstChar = data.find("{",0);
  data = data.erase(0, firstChar);
  // std::cout << "New data after delete it the 0,0 position char: " << data << std::endl;
  jsonData = json::parse(data);
  groups = jsonData["groups"];
  for (json::iterator it = groups.begin(); it != groups.end(); ++it) {
    std::string group = it.key();
    std::vector<std::string> countries = it.value()["countries"]; 
    // Save the data in the table
    this->groupsTable[group] = countries;
  }
  file.close();
}

void Router::addServer(std::string address, char group) {
  group = toupper(group);
  this->serverTable[address] = group;
}

void Router::removeServer(std::string address) {
  this->serverTable.erase(address);
}

void Router::listenForClients() {
  int childpid;
  char a[512];
  Socket s1('s'), *s2;

  s1.Bind( ROUTER_HTTP_PORT );		// Port to access this mirror server
  s1.Listen( 5 );		// Set backlog queue to 5 conections
  std::cout << "listening on 9877" << std::endl;
  for( ; ; ) {
    std::cout << "ROUTER: waiting for a request" << std::endl;
    s2 = s1.Accept();	 	// Wait for a conection
    childpid = fork();	// Create a child to serve the request
    if (childpid < 0)
      perror("router: fork error");
    else if (0 == childpid) {  // child code
      s1.Close();	// Close original socket in child
      s2->Read( a, 512 );
      std::cout<< "Received: \n" << a << std::endl; // Read a string from client
      
      HttpParser parser(a);

      std::string country = parser.getCountry();
      std::cout << "Country code: " << country << "." << std::endl;

      char group = this->findGroupByCountry(country);
      std::string serverHostIp = this->getServerByGroup(group);

      char buffer[512];
      if(!serverHostIp.empty()){
        Socket toDataServer('s');
        //code to connect to server
        // Socket s('s'); // Crea un socket de IPv4, tipo "stream"
        toDataServer.Connect(serverHostIp.c_str(), SERVER_HTTP_PORT); // Same port as server
      
        // std::string req = "GET /fifa/2018/"+input+" HTTP/1.1\r\nhost: grupoh.ecci \r\n\r\n";
        std::cout << "Sending get request to data server: \n" << a << std::endl;
        toDataServer.Write(a);
        memset(buffer,0, 512);
        toDataServer.Read(buffer, 512 );	// Read the answer sent back from server
        std::string localBuffer(buffer);
        
        //write back to the client
        std::cout << "ROUTER: Writing back to client ";
      } else {
        const char * errMessage = "HTTP/1.1 404 Not Found";
        memcpy(buffer, errMessage, 52);
      }
      
      s2->Write(buffer);

      exit( 0 );	// Exit
    }
    s2->Close();		// Close socket in parent
  }

}

void Router::listenForServers() {
  int n;
  char buffer[MAXLINE]; 
  struct sockaddr other;
  Socket server( 'd' );	// Creates an UDP socket: datagram
  server.Bind( ROUTER_PORT );
  memset( &other, 0, sizeof( other ) ); 
  int childpid;

  for( ; ; ) {
    std::cout << "waiting for a server" << std::endl;
    n = server.recvFrom( (void *) buffer, MAXLINE, (void *) & other );	 	// Wait for a conection
    childpid = fork();	// Create a child to serve the request
    if (childpid < 0)
      perror("server: fork error");
    else if (0 == childpid) {  // child code
      buffer[n] = '\0';
      //TODO ADD VALIDATION TO CHECK IF THE MESSAGE CONTAINS `DEAD` WORD
      std::cout << "server up from: " << buffer << std::endl;
      std::vector<std::string> message = Util::split(buffer, "\t");
      // TODO(?) validate if its null and if it contains `dead` word
      if(!message.empty() && message[PROTOCOL_INDEX_IP] != "DEAD" ){
        this->addServer(message[PROTOCOL_INDEX_IP],
                        message[PROTOCOL_INDEX_GROUP][0]);
      } else {
        std::cout << "Removing server from list: " 
                  << message[PROTOCOL_INDEX_GROUP] << std::endl;
        this->removeServer(message[PROTOCOL_INDEX_GROUP]);
      }

      std::cout << "Available Servers:" << std::endl;
      std::map<std::string, char>::iterator it;
      for(it = this->serverTable.begin(); it != this->serverTable.end(); ++it){
        std::cout << it->first << ":" << it->second << std::endl;
      }
    }
  }
  server.Close();
}

void Router::sendWakeUpBroadcast() {
  Socket * server;
  int sockfd; 
  int n, len; 
  char buffer[MAXLINE]; 
  char *hello = (char *) "127.0.0.1"; // QUE MENSAJE DEBE ENVIAR EL ROUTER CUANDO HACE UN BROADCAST, SU IP? CIERTO
  struct sockaddr_in other;
  std::vector<std::string> hosts = {"127.0.0.1","192.168.100.34"};

  server = new Socket( 'd' );	// Creates an UDP socket: datagram

  memset( &other, 0, sizeof( other ) ); 
  
  other.sin_family = AF_INET; 
  other.sin_port = htons(SERVER_PORT); 
  for (std::string host : hosts) {
    // convertir la host ip 
    inet_aton(host.c_str(),&(other.sin_addr));
    n = server->sendTo( (void *) hello, strlen( hello ), (void *) & other ); 
    std::cout << "Broadcast sent "<< n <<" bytes to: " << host << std::endl; 
  }
  server->Close();
}

char Router::getGroupByServer(std::string address) {
  char group;
  auto item = this->serverTable.find(address);
  if (item != this->serverTable.end())
    group = item->second;
  return group;
}

std::string Router::getServerByGroup(char group) {
  std::string address;
  group = toupper(group);
  for (auto iter = this->serverTable.begin(); iter != this->serverTable.end(); ++iter) {
    if (iter->second == group) {
      address = iter->first;
      break;
    }
  }
  return address;
}
