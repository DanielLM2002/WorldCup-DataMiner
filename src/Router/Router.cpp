/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "Router.hpp"

Router::Router() {
  this->router = new RouterTable();
  this->router->addEntry("New table");

}

Router::~Router() {
  delete this->router;
  
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

  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketDescriptor < 0) {
    perror("ERROR opening socket\n");
    exit(1);
  }
  bzero((char *) &serverAddress, sizeof(serverAddress));
  portNumber = 8080;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(portNumber);
  if (bind(socketDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
    perror("ERROR on binding\n");
    exit(1);
  }
  listen(socketDescriptor, 5);
  clientLength = sizeof(clientAddress);
  while (1) {
    clientSocketDescriptor = accept(socketDescriptor, (struct sockaddr *) &clientAddress, (socklen_t *) &clientLength);
    if (clientSocketDescriptor < 0) {
      perror("ERROR on accept\n");
      exit(1);
    }
    std::thread(&Router::handleClient, this, clientSocketDescriptor).detach();
  }
  close(socketDescriptor);

}

void Router::listenForServers() {
  int socketDescriptor;
  int clientSocketDescriptor;
  int portNumber;
  int clientLength;
  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;

  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketDescriptor < 0) {
    perror("ERROR opening socket\n");
    exit(1);
  }
  bzero((char *) &serverAddress, sizeof(serverAddress));
  portNumber = 8081;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(portNumber);
  if (bind(socketDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
    perror("ERROR on Binding\n");
    exit(1);
  }
  listen(socketDescriptor, 5);
  clientLength = sizeof(clientAddress);
  while (1) {
    clientSocketDescriptor = accept(socketDescriptor, (struct sockaddr *) &clientAddress, (socklen_t *) &clientLength);
    if (clientSocketDescriptor < 0) {
      perror("ERROR on accept\n");
      exit(1);
    }
    std::thread(&Router::handleServer, this, clientSocketDescriptor).detach();
  }
  close(socketDescriptor);
}

void Router::sendWakeUpBroadcast() {
  int socketDescriptor;
  int portNumber;
  int n;
  struct sockaddr_in serverAddress;
  struct hostent *server;
  char buffer[256];

  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketDescriptor < 0) {
    perror("ERROR opening socket\n");
    exit(1);
  }
  server = gethostbyname("localhost");
  if (server == NULL) {
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }
  bzero((char *) &serverAddress, sizeof(serverAddress));
  portNumber = 8081;
  serverAddress.sin_family = AF_INET;
  bcopy((char *) server->h_addr, (char *) &serverAddress.sin_addr.s_addr, server->h_length);
  serverAddress.sin_port = htons(portNumber);
  if (connect(socketDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
    perror("ERROR connecting\n");
    exit(1);
  }
  bzero(buffer, 256);
  strcpy(buffer, "WAKEUP");
  n = write(socketDescriptor, buffer, strlen(buffer));
  if (n < 0) {
    perror("ERROR writing to socket\n");
    exit(1);
  }
  close(socketDescriptor);

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
