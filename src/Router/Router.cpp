/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "Router.hpp"

#define SERVER_PORT   2020
#define ROUTER_PORT   2022
#define MAXLINE       1024 

Router::Router() {

}

Router::~Router() {
  
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
  int socketDescriptor;
  int clientSocketDescriptor;
  int portNumber;
  int clientLength;
  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;

  // socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  // if (socketDescriptor < 0) {
  //   perror("ERROR opening socket\n");
  //   exit(1);
  // }
  // bzero((char *) &serverAddress, sizeof(serverAddress));
  // portNumber = 8080;
  // serverAddress.sin_family = AF_INET;
  // serverAddress.sin_addr.s_addr = INADDR_ANY;
  // serverAddress.sin_port = htons(portNumber);
  // if (bind(socketDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
  //   perror("ERROR on binding\n");
  //   exit(1);
  // }
  // listen(socketDescriptor, 5);
  // clientLength = sizeof(clientAddress);
  // while (1) {
  //   clientSocketDescriptor = accept(socketDescriptor, (struct sockaddr *) &clientAddress, (socklen_t *) &clientLength);
  //   if (clientSocketDescriptor < 0) {
  //     perror("ERROR on accept\n");
  //     exit(1);
  //   }
  //   std::thread(&Router::handleClient, this, clientSocketDescriptor).detach();
  // }
  // close(socketDescriptor);

}

void Router::listenForServers() {
  int sockfd; 
  int n, len; 
  char buffer[MAXLINE]; 
  char *hello = (char *) "127.0.0.1\tE"; //ip y grupo 
  struct sockaddr other;
  Socket server( 'd' ), *s2;	// Creates an UDP socket: datagram
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
      std::cout << "server up from: " << buffer << std::endl;
      std::vector<std::string> message = Util::split(buffer, "\t");
      this->addServer(message[0],message[1][0]);
      //server.sendTo( (const void *) hello, strlen( hello ), (void *) &other );
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
  char *hello = (char *) "127.0.0.1"; 
  struct sockaddr_in other;
  std::vector<std::string> hosts = {"127.0.0.1"};

  server = new Socket( 'd' );	// Creates an UDP socket: datagram

  memset( &other, 0, sizeof( other ) ); 
  
  other.sin_family = AF_INET; 
  other.sin_port = htons(SERVER_PORT); 
  for (std::string host : hosts) {
    // convertir las ips pasarlas en la linea siguiente
    other.sin_addr.s_addr = INADDR_ANY;
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
