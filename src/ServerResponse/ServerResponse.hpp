/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _SERVER_RESPONSE_
#define _SERVER_RESPONSE_

#include <stdio.h>
#include <string.h>

#include <vector>
#include <sstream>

#include "common/Util.hpp"
#include "../Round/Round.hpp"
#include "../Socket/Socket.hpp"
#include "../data/CountryCodes.hpp"
#include "../JSON/JsonDataSource.hpp"

#ifndef _STRUCT_POINTS_BY_COUNTRY
#define _STRUCT_POINTS_BY_COUNTRY
/**
 * @brief Structure that saves the statistics of a selection in a group
 */
typedef struct {
  /// Played games
  int PJ = 0;
  /// Won matches
  int PG = 0;
  /// Tied matches
  int PE = 0;
  /// Lost matches
  int PP = 0;
  /// Goals for
  int GF = 0;
  /// Goals Against
  int GC = 0;
  /// Goal difference
  int GD = 0;
  /// Points
  int Pts = 0;
  /// Country name
  std::string country = "";
} PointsByCountry;
#endif // !_STRUCT_POINTS_BY_COUNTRY

class ServerResponse {
 private: 
  /// Data source
  JsonDataSource json;
  /// Selected country
  std::string country;
  /// Group of selected country
  std::string group;

 public:
  /// Buffer
  std::stringstream stringBuffer;

  /**
   * @brief Constructor
   */
  explicit ServerResponse(std::string country);

  /**
   * @brief Destroyer
   */
  ~ServerResponse();

  /**
   * @brief Method that reads the data entered by the user
   */
  void getInput();

  /**
   * @brief Method that builds the titles of the table and obtains the data 
   *        of each team such as points and goals
   * @param roundMatches Matches played in the round
   * @param countriesByGroup Data of the teams of the round
   */
  void buildTable(std::vector<Match>, std::vector<PointsByCountry>);

  /**
   * @brief Method that asks the user if he wants to obtain the route of a team 
   *        in the world cup
   */
  void askAgain();

  /**
   * @brief Method that obtains the name of the countries through their FIFA 
   *        code and checks that it is valid
   */
  void handleCountry();

  /**
   * @brief Method that prints the information of the selections of a certain group
   * @param group Name of the group
   */
  void printGroup(std::string);

  /**
   * @brief Method that prints the statistics of each country in the group table
   * @param countriesByGroup Data for each country in the group
   */
  void printTable(std::vector<PointsByCountry>);

  /**
   * @brief Metod that prints all country codes available
   */
  void printCountryCodes();

  /**
   * @brief Method that prints the statistics of all knockout instance games 
   *        played by the country entered by the user
   */
  void printMatches();

  /**
   * @brief Method that prints statistics of a match in instances of knockout
   * @param match Match played
   */
  void printMatch(Match);

  /**
   * @brief Method that checks that the selected country is in a group and 
   *        if so, returns that group
   * @return std::string 
   */
  std::string getGroup();

  /**
   * @brief Method that converts a string to uppercase
   * @param str String
   * @return std::string 
   */
  std::string toUpperCase(std::string);
};

#endif  // !_SERVER_RESPONSE_
