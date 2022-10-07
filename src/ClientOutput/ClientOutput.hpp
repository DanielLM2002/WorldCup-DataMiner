/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _CLIENT_OUTPUT_
#define _CLIENT_OUTPUT_

#include <stdio.h>
#include <string.h>

#include <vector>

#include "../Round/Round.hpp"
#include "../Socket/Socket.hpp"
#include "../JSON/JsonDataSource.hpp"
#include "../../data/CountryCodes.hpp"

class ClientOutput {
 private: 
  /// Selected country
  std::string country;

 public:
  /**
   * @brief Constructor
   */
  explicit ClientOutput();

  /**
   * @brief Destroyer
   */
  ~ClientOutput();

  /**
   * @brief Method that obtains the name of the countries through their FIFA 
   *        code and checks that it is valid
   */
  void handleBuffer(char*);

  /**
   * @brief Method that prints the statistics of each country in the group table
   * @param countriesByGroup Data for each country in the group
   */
  void printGroup(std::vector<std::vector<std::string>>);

  /**
   * @brief Method that prints the statistics of all knockout instance games 
   *        played by the country entered by the user
   */
  void printMatches(std::vector<std::vector<std::string>>);
};

#endif  // !_CLIENT_OUTPUT_
