/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _JSON_DATA_SOURCE_
#define _JSON_DATA_SOURCE_

#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../Round/Round.hpp"
#include "../Socket/Socket.hpp"

using json = nlohmann::json;

class JsonDataSource {
 private:
  /// Data extracted from JSON
  std::string data;

 public:
  /**
   * @brief Constructor
   */
  explicit JsonDataSource();

  /**
   * @brief Destroyer
   */
  ~JsonDataSource();

  /**
   * @brief Method that gets the Round
   * @return Round
   */
  Round getRound(std::string roundName);
 
 private:
  /**
   * @brief Method that fetchs the data from the server
   */
  int fetchData();

  /**
   * @brief Method that fetchs the data from the server using SSL
   */
  int fetchDataSSL();

  /**
   * @brief  Method that storing rounds associated to each round type
   *        like "group_a" associated to Round with type "group_a"
   */
  std::map <std::string, Round> rounds;

  /**
   * @brief Method that parses the data obtained from the server
   *        and parses it to Rounds
   */
  void parseDataToRounds();

  /**
   * @brief Method that parses the data obtained from the server according 
   *        to a key, it associates the data with a key
   * @param jsonData Data extracted from JSON
   * @param roundKey Key
   * @param roundCodePref Round prefix
   * @param namePref name prefix
   */
  void parseRounds(json, std::string, std::string);

  /**
   * @brief Method that extracts information about matches, and returns a 
   *        list of the matches
   * @param matches JSON object with array of matches, like jsonObject["matches"]
   * @return vector<Match> 
   */
  std::vector<Match> parseMatches(json);
};

#endif // !_JSON_DATA_SOURCE_
