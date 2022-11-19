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

}

void Router::listenForServers() {

}

void Router::sendWakeUpBroadcast() {

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
