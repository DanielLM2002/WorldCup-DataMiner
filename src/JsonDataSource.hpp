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
#include <sstream>

#include "Round.hpp"
#include "Socket.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonDataSource {
 private:
  std::string data;

 public:
  explicit JsonDataSource();
  ~JsonDataSource();

  /**
   * @brief Get the Round object
   * 
   * @return Round 
   */
  Round getRound(std::string roundName);
 
 private:
  /**
   * @brief fetchs the data from the server
   * 
   */
  int fetchData();

  /**
   * @brief storing rounds associated to each round type
   *        like "group_a" associated to Round with type "group_a"
   * 
   */
  std::map <std::string, Round> rounds;

  /**
   * @brief Parse the data obtained from the server
   *        and parses it to Rounds;
   */
  void parseDataToRounds();

  /**
   * @brief extract groups(a,b,c,d...) from json
   * 
   */
   void parseGroups(json);

   void parseRounds(json, std::string, std::string, std::string);

  /**
   * @brief extract information about matches,
   *        and returns a list of the matches
   * @json object with array of matches, like jsonObject["matches"]
   * 
   * @return vector<Match> 
   */
  std::vector<Match> parseMatches(json);
};

#endif // !_JSON_DATA_SOURCE_