/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include <stdio.h>
#include <string.h>
#include <thread>         // std::thread

#include "Server/Server.hpp"
#include "Client/Client.hpp"
#include "Router/Router.hpp"

int server() {
  Server ser(9876);
  std::thread serv(&Server::serve, ser);
  std::thread responseToWakeUps(&Server::listenForWakeUps, ser);
  
  ser.sendWakeUpBroadcast();

  responseToWakeUps.join();
  serv.join();
  // ser.respondToWakeUp();
  return EXIT_SUCCESS;
}

int router() {
  Router router;
  // TODO to check this method
  // router.fillGroupsTable("data/world-cup-2018.json");
  router.sendWakeUpBroadcast();
  std::thread listenServers(&Router::listenForServers, router);
  //TODO implement listen for clients
  std::thread listenClients(&Router::listenForClients, router);
  listenServers.join();
  listenClients.join();
  return EXIT_SUCCESS;
}

int client() {
  Client client("127.0.0.1", ROUTER_HTTP_PORT);
  client.start();
  return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
  std::string type = "";

  if (argc == 2) {
    type = argv[1];
  } else {
    std::cout << "Invalid argument" << std::endl;
  }

  if (type.compare("server") == 0) {
    server();
  } else if (type.compare("client") == 0) {
    client();
  } else if (type.compare("router") == 0){
    router();
  } else {
    std::cout << "Invalid argument" << std::endl;
  }
  return EXIT_SUCCESS;
}
