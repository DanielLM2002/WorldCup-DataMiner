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
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <threads.h>

#include "Socket.hpp"
#include "Util.hpp"
#include "HttpParser.hpp"

using json = nlohmann::json;


#define SERVER_PORT   2020
#define SERVER_HTTP_PORT 9876
#define ROUTER_PORT   2022
#define ROUTER_HTTP_PORT 9877
#define MAXLINE       1024
#define PROTOCOL_INDEX_IP 0
#define PROTOCOL_INDEX_GROUP 1
#define ROUTER_HOST_IP "127.0.0.1" // IP OF THE COMPUTER WHERE THE ROUTER IS RUNNING

class Router {
 private:
  /// Table that associates a server to a group
  std::map<std::string, char> serverTable;
  /// Table that associates a group to an array of countries
  std::map<std::string, std::vector<std::string>> groupsTable;///2018 / 2022

 public:
  /**
   * @brief Constructor
   */
  explicit Router();

  /**
   * @brief Destroyer
   */
  ~Router();

  /**
   * @brief Method that fills the group table with the data from a JSON
   * @param fileName File path
   */
  void fillGroupsTable(std::string);

  /**
   * @brief Method that adds a server associated to a group to the 
   *        servers table
   * @param address IP address of the server
   * @param group Group letter
   */
  void addServer(std::string, char);

  /**
   * @brief Method that removes a server associated to a group to the 
   *        servers table
   * @param addres IP address of the server
   */
  void removeServer(std::string);

  /**
   * @brief 
   * 
   */
  void listenForClients();

  /**
   * @brief 
   * 
   */
  void listenForServers();

  /**
   * @brief 
   * 
   */
  void sendWakeUpBroadcast();

  /**
   * @brief Method that gets the group associated with a server
   * @param address IP address of the server
   * @return char 
   */
  char getGroupByServer(std::string);

  /**
   * @brief Method that gets the server associated with a group
   * @param group Group letter
   * @return std::string 
   */
  std::string getServerByGroup(char);

  /**
   * @brief Method that gets the country's group in the world cup
   * @param countryCode 3 letters code for country(FIFA OFFICIAL) 
   * @return char group letter
   */
  char findGroupByCountry(std::string);
   
};

#endif // !_ROUTER_
