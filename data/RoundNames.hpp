/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _ROUND_NAMES_
#define _ROUND_NAMES_

#include <map>
#include <iostream>

struct RoundNames {
  /// Array with the rounds and their names
  std::map<std::string, std::string> rounds;

  /**
   * @brief Constructor
   */
  explicit RoundNames() {
    this->rounds.insert({"round_16", "Round of 16"});
    this->rounds.insert({"round_8", "Quarter-finals"});
    this->rounds.insert({"round_4", "Semi-finals"});
    this->rounds.insert({"round_2_loser", "Third place play-off"});
    this->rounds.insert({"round_2", "Final"});
  };
};

#endif // !_ROUND_NAMES_
