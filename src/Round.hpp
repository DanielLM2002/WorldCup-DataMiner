/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef ROUND_HPP
#define ROUND_HPP

#include <vector>

#include "Match.hpp"

class Round {
 private:
  std::string code;
  std::string name;
  std::vector<Match> matches;

 public:
  explicit Round(std::string, std::string);
  ~Round();
  void addMatch(Match);
  std::string getCode();
  std::string getName();
  std::vector<Match> getMatches();
  void setCode(std::string);
  void setName(std::string);
  void setMatches(std::vector<Match>);
};

#endif  // !ROUND_HPP
