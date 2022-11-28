/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "Server.hpp"
#include "HttpParser.hpp"

#define SERVER_PORT   2020
#define ROUTER_PORT   2022
#define MAXLINE       1024
#define HOST_IP       "192.168.100.57"
#define SEPARATOR     "\t"
#define GROUPS        "E"

Server::Server(int nPort): port(nPort) {

}

Server::~Server() {

}

void Server::serve(){
  int childpid;
  char a[512];
  Socket s1('s'), *s2;

  s1.Bind( this->port );		// Port to access this mirror server
  s1.Listen( 5 );		// Set backlog queue to 5 conections
  std::cout << "listening on 9876" << std::endl;
  for( ; ; ) {
    std::cout << "waiting for a request" << std::endl;
    s2 = s1.Accept();	 	// Wait for a conection
    childpid = fork();	// Create a child to serve the request
    if (childpid < 0)
      perror("server: fork error");
    else if (0 == childpid) {  // child code
      s1.Close();	// Close original socket in child
      s2->Read( a, 512 );
      std::cout<< "Received: \n" << a << std::endl; // Read a string from client
      
      HttpParser parser(a);

      std::string country = parser.getCountry();
      std::cout << "Country code: " << country << "." << std::endl;

      //get country data
      ServerResponse os(country);
      os.handleCountry();
      std::string result = os.stringBuffer.str();
      const char* resCountry = &result[0];
      s2->Write(resCountry);
      exit( 0 );	// Exit
    }
    s2->Close();		// Close socket in parent
  }
}

void Server::listenForWakeUps() {
  int sockfd; 
  int n, len; 
  char buffer[MAXLINE]; 
  char *hello = (char *) "127.0.0.1\tE"; //ip y grupo 
  struct sockaddr other;
  Socket server( 'd' ), *s2;	// Creates an UDP socket: datagram
  server.Bind( SERVER_PORT );
  memset( &other, 0, sizeof( other ) );
  int childpid;

  for( ; ; ) {
    std::cout << "waiting for a wakeup" << std::endl;
    n = server.recvFrom( (void *) buffer, MAXLINE, (void *) & other );	 	// Wait for a conection
    childpid = fork();	// Create a child to serve the request
    if (childpid < 0)
      perror("server: fork error");
    else if (0 == childpid) {  // child code
      buffer[n] = '\0';
      std::cout << "a router waked up from: " << buffer << std::endl;
      
      Socket * responseTo = new Socket( 'd' );	// Creates an UDP socket: datagram
      struct sockaddr_in other2;
      std::vector<std::string> hosts = {"127.0.0.1"};
      memset( &other, 0, sizeof( other2 ) ); 
      
      other2.sin_family = AF_INET; 
      other2.sin_port = htons(ROUTER_PORT);
      for (std::string host : hosts) {
        // convertir las ips pasarlas en la linea siguiente
        other2.sin_addr.s_addr = INADDR_ANY;
        n = responseTo->sendTo( (void *) hello, strlen( hello ), (void *) & other2 ); 
        std::cout << "Broadcast sent "<< n <<" bytes to: " << host << std::endl; 
      }
      
    }
  }
  server.Close();
}

std::string Server::getServerGroups(){
  //TODO change to get it from config file:
  //std::vector<std::string> config = ConfigFileFactory::getConfigurations();
  //std::string serverGroups = config[NAME_OF_CONFIGURATION_INDEX];
  //return serverGroups;
  return std::string(GROUPS);
}

void Server::sendWakeUpBroadcast() {
  Socket * server;
  int sockfd; 
  int n, len; 
  char buffer[MAXLINE];
  char *hello = (char *) HOST_IP;
  // here should be the gateway/broadcast ips
  std::vector<std::string> hosts = {"127.0.0.1","192.168.100.34"};
  std::stringstream messageBuilder;
  messageBuilder << HOST_IP << SEPARATOR << this->getServerGroups();
  std::string broadcastMessage = messageBuilder.str();

  server = new Socket( 'd' );	// Creates an UDP socket: datagram
  //TODO CREATE A SOCKET METHOD to send a UDP broadcast message
  //server->SendUdpBroadcast()

  
  struct sockaddr_in other;
  memset( &other, 0, sizeof( other ) );

  
  other.sin_family = AF_INET; 
  other.sin_port = htons(ROUTER_PORT); 
  for (std::string host : hosts) {
    // convertir la host ip 
    inet_aton(host.c_str(),&(other.sin_addr));
    n = server->sendTo( (void *) broadcastMessage.c_str(), broadcastMessage.size(), (void *) & other ); 
    std::cout << "Broadcast sent "<< n <<" bytes to: " << host << std::endl; 
  }
  server->Close();
}