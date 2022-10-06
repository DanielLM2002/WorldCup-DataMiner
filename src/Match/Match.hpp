/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _MATCH_
#define _MATCH_

#include <iostream>

class Match {
 private:
  /// Score of the home team
  int homeScore;
  /// Score of the away team
  int awayScore;
  /// Dtae of the match
  std::string date;
  /// Loser team
  std::string loser;
  /// Winner team
  std::string winner;
  /// Home team
  std::string homeTeam;
  /// Away team
  std::string awayTeam;

 public:
  /**
   * @brief Constructor
   * @param homeScore Score of the home team
   * @param awayScore Score of the away team
   * @param date Date of the match
   * @param loser Loser team
   * @param winner Winner team
   * @param homeTeam Home team
   * @param awayTeam Away team
   */
  explicit Match(int, int, std::string, std::string, std::string, std::string, std::string);
  
  /**
   * @brief Destroyer
   */
  ~Match();

  /**
   * @brief Method that gets the home score
   * @return int 
   */
  int getHomeScore();

  /**
   * @brief Method that gets the away score
   * @return int 
   */
  int getAwayScore();

  /**
   * @brief Method that gets the date
   * @return std::string 
   */
  std::string getDate();

  /**
   * @brief Method that gets the loser
   * @return std::string 
   */
  std::string getLoser();

  /**
   * @brief Method that gets the winner
   * @return std::string 
   */
  std::string getWinner();

  /**
   * @brief Method that gets the home team
   * @return std::string 
   */
  std::string getHomeTeam();

  /**
   * @brief Method that gets the away team
   * @return std::string 
   */
  std::string getAwayTeam();

  /**
   * @brief Method that sets the home score
   */
  void setHomeScore(int);

  /**
   * @brief Method that sets the away score
   */
  void setAwayScore(int);

  /**
   * @brief Method that sets the date
   */
  void setDate(std::string);

  /**
   * @brief Method that sets the loser
   */
  void setLoser(std::string);

  /**
   * @brief Method that sets the winner
   */
  void setWinner(std::string);

  /**
   * @brief Method that sets the home team
   */
  void setHomeTeam(std::string);

  /**
   * @brief Method that sets the away team
   */
  void setAwayTeam(std::string);
};

#endif  // !_MATCH_
