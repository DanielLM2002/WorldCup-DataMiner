/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _CLIENT_
#define _CLIENT_

#include <stdio.h>
#include <string.h>

#include <iostream>

#include "../Socket/Socket.hpp"

class Client {
 private:
  /// Number of the host
  std::string host;
  /// Number of the port
  int port;
  /// Buffer
  char buffer[512];

 public:
  /**
   * @brief Constructor
   * @param nHost Number of the host
   * @param nPort Number of the port
   */
  explicit Client(std::string nHost, int nPort);

  /**
   * @brief Destroyer
   */
  ~Client();

  /**
   * @brief Method that starts the client
   */
  void start();

  /**
   * @brief Method that reads the data entered by the user
   */
  void getInput(Socket*);

  /**
   * @brief Method that asks the user if he wants to obtain the route of a team 
   *        in the world cup
   */
  void askAgain(Socket*);

  /**
   * @brief Metod that prints all country codes available
   */
  void printCountryCodes(Socket*);

  /**
   * @brief Method that converts a string to uppercase
   * @param str String
   * @return std::string 
   */
  std::string toUpperCase(std::string);
};

#endif // !_CLIENT_
