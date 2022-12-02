/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _SERVER_
#define _SERVER_

#include <string>
#include <vector>

#include "common/Util.hpp"
#include "common/common.hpp"
#include "../Socket/Socket.hpp"
#include "../ServerResponse/ServerResponse.hpp"

class Server {
 private:
  /// Number of the port
  int port;

  std::string getServerGroups();

 public:
  /**
   * @brief Constructor
   * @param nPort Number of the port
   */
  explicit Server(int nPort);

  /**
   * @brief Destroyer
   */
  ~Server();

  /**
   * @brief Method that starts the server
   */
  void serve();

  /**
   * @brief Method to start listening to 
   * UDP messages from Routers (maybe add the port is a good option)
   */
  void listenForWakeUps();

  /**
   * @brief Method that starts the server to start listening to 
   * UDP messages from Routers
   */
  void sendWakeUpBroadcast();

  /**
   * @brief send the dead broadcast to routers
   * 
   */
  void sendDeadBroadcast();
};

#endif  // !_SERVER_
