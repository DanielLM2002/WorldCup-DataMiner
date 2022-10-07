/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _STRING_DATA_SOURCE_
#define _STRING_DATA_SOURCE_

#include <stdio.h>
#include <string.h>

#include <vector>
#include <iostream>

#include "../common/Util.hpp"

class StringDataSource {
 private:
  /// Value of the group
  std::vector<std::vector<std::string>> group;
  /// Value of the round
  std::vector<std::vector<std::string>> round;
  
 public:
  /**
   * @brief Constructor
   */
  explicit StringDataSource();

  /**
   * @brief Destroyer
   */
  ~StringDataSource();

  /**
   * @brief Method that parses the data in the buffer
   * @param buffer Buffer
   */
  void parse(char*);

  /**
   * @brief Method that ranks countries according to their score
   */
  void orderGroupByPosition();

  /**
   * @brief Method that gets the group
   * @return std::vector<std::vector<std::string>> 
   */
  std::vector<std::vector<std::string>> getGroup();

  /**
   * @brief Method that gets the round
   * @return std::vector<std::vector<std::string>> 
   */
  std::vector<std::vector<std::string>> getRounds();
};

#endif // !_STRING_DATA_SOURCE_
