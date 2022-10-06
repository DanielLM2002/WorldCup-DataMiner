/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _ROUND_
#define _ROUND_

#include <vector>

#include "Match.hpp"

class Round {
 private:
  /// Code of the round
  std::string code;
  /// Name of the round
  std::string name;
  /// Matches in the round
  std::vector<Match> matches;

 public:
  /**
   * @brief Constructor
   * @param code Code of the round
   * @param name Name of the round
   */
  explicit Round(std::string, std::string);

  /**
   * @brief Destroyer
   */
  ~Round();

  /**
   * @brief Method that adds a match to the matches array
   * @param match Match object
   */
  void addMatch(Match);

  /**
   * @brief Method that gets the code
   * @return std::string 
   */
  std::string getCode();

  /**
   * @brief Method that gets the name
   * @return std::string 
   */
  std::string getName();

  /**
   * @brief Method that gets the matches array
   * @return std::vector<Match> 
   */
  std::vector<Match> getMatches();

  /**
   * @brief Methot that sets the code
   * @param code Code of the round
   */
  void setCode(std::string);

  /**
   * @brief Methot that sets the name
   * @param name Name of the round
   */
  void setName(std::string);

  /**
   * @brief Methot that sets the matches array
   * @param matches Matches in the round
   */
  void setMatches(std::vector<Match>);
};

#endif  // !_ROUND_
