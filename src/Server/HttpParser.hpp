/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3
#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include <string>
#include <vector>

#include "common/Util.hpp"
#include "../Socket/Socket.hpp"
#include "../ServerResponse/ServerResponse.hpp"

class HttpParser {
 private:
  /// Number of the port
  int port;

 public:
  /**
   * @brief Constructor
   * @param nPort Number of the port
   */
  explicit HttpParser(int nPort);

  /**
   * @brief Destroyer
   */
  ~HttpParser();

    std::string getHeaderValues(std::string header, std::string &method, std::string &path, std::string &version);

    std::string getPathValues(std::string path, std::string &pathName, std::string &pathExtension);
};

#endif  // !_SERVER_HPP_