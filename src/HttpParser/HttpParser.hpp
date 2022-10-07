/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _HTTP_PARSER_
#define _HTTP_PARSER_

#include <string>
#include <vector>

#include "common/Util.hpp"
#include "../Socket/Socket.hpp"
#include "../ServerResponse/ServerResponse.hpp"

class HttpParser {
 private:
  /// Number of the port
  std::string country;
  /// Message
  std::string httpMessage;

 public:
  /**
   * @brief Constructor
   * @param nPort Number of the port
   */
  explicit HttpParser(std::string message);

  /**
   * @brief Destroyer
   */
  ~HttpParser();

  /**
   * @brief Method that gets the header value of the JSON
   * @param header Header
   * @param method Method
   * @param path Path
   * @param version Version
   * @return std::string 
   */
  std::string getHeaderValues(std::string header, std::string &method, std::string &path, std::string &version);

  /**
   * @brief Method that gets the country
   * @return std::string 
   */
  std::string getCountry();

  /**
   * @brief Method that parses the message
   */
  void parse();
};

#endif  // !_HTTP_PARSER_