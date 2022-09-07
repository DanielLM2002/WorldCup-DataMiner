/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#define JSON
#define SIZE 1024

#include <stdio.h>
#include <string.h>

#include "Round.hpp"
#include "Socket.hpp"
#include "JsonDataSource.hpp"

int main() { 
  JsonDataSource dataSrc;
  Round round = dataSrc.getRound("group_c");
  std::vector<Match> roundMatches = round.getMatches();

  std::cout << round.getName() << " matches: " << std::endl;
  int size = roundMatches.size();
  for (int index = 0; index < size; ++index) {
    Match match = roundMatches[index];
    std::cout << match.getHomeTeam() <<" vs " 
              << match.getAwayTeam() << " => "
              << match.getHomeScore() << " - "
              << match.getAwayScore() << std::endl;
  }
  
  round = dataSrc.getRound("round_16");
  roundMatches = round.getMatches();

  std::cout << std::endl << std::endl;
  std::cout << round.getName() << " matches: " << std::endl;
  size = roundMatches.size();
  for (int index = 0; index < size; ++index) {
    Match match = roundMatches[index];
    std::cout << match.getHomeTeam() <<" vs " 
              << match.getAwayTeam() << " => "
              << match.getHomeScore() << " - "
              << match.getAwayScore() << std::endl;
  }
}
