/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

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

};

#endif // !_CLIENT_HPP_
