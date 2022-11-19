/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _ROUTER_
#define _ROUTER_

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Router {
 private:
  std::map<std::string, char> serverTable;
  std::map<std::string, std::vector<std::string>> groupsTable;

 public:
  explicit Router();
  ~Router();
  void fillGroupsTable(std::string);
  void addServer(std::string, char);
  void removeServer(std::string);
  void listenForClients();
  void listenForServers();
  void sendWakeUpBroadcast();
  char getGroupByServer(std::string);
  std::string getServerByGroup(char);
};

#endif // !_ROUTER_
