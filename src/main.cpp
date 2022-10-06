/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include <stdio.h>
#include <string.h>

#include "Output/Output.hpp"
#include "Util.hpp"
#include "Server/Server.hpp"
#include "Client/Client.hpp"

int server() {
  
  Server ser(9876);
  ser.serve();

  return EXIT_SUCCESS;
}

int client() {
  Client client("127.0.0.1",9876);
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
  } else {
    std::cout << "Invalid argument" << std::endl;
  }
  return EXIT_SUCCESS;
}
