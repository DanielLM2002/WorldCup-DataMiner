/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef MATCH_HPP
#define MATCH_HPP

#include <iostream>

class Match {
 private:
  int homeScore;
  int awayScore;
  std::string date;
  std::string loser;
  std::string winner;
  std::string homeTeam;
  std::string awayTeam;
 public:
  explicit Match(int, int, std::string, std::string, std::string, std::string, std::string);
  ~Match();
  int getHomeScore();
  int getAwayScore();
  std::string getDate();
  std::string getLoser();
  std::string getWinner();
  std::string getHomeTeam();
  std::string getAwayTeam();
  void setHomeScore(int);
  void setAwayScore(int);
  void setDate(std::string);
  void setLoser(std::string);
  void setWinner(std::string);
  void setHomeTeam(std::string);
  void setAwayTeam(std::string);
};

#endif  // !MATCH_HPP
