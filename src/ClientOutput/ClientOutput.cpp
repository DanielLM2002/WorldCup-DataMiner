/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "ClientOutput.hpp"

#include "../common/Util.hpp"
#include "../String/StringDataSource.hpp"
#include "../../data/RoundNames.hpp"
#include "../../data/CountryCodes.hpp"

ClientOutput::ClientOutput() {}

ClientOutput::~ClientOutput() {}

void ClientOutput::handleBuffer(char* buffer) {
  StringDataSource string;
  string.parse(buffer);
  if (string.getHeader() != "HTTP/1.1 404 Not Found") {
    this->printGroup(string.getGroup());
    this->printMatches(string.getRounds());
  }
}

void ClientOutput::printGroup(std::vector<std::vector<std::string>> group) {
  CountryCodes countryNames;
  std::cout << "Country         "
            << "PJ" << '\t' 
            << "PG" << '\t' 
            << "PE" << '\t' 
            << "PP" << '\t' 
            << "GF" << '\t' 
            << "GC" << '\t' 
            << "GD" << '\t' 
            << "Pts" << std::endl;

  for (size_t i = 0; i < group.size(); i++) {
    for (size_t j = 0; j < group[i].size(); j++) {
      if (j == 0){
        printf("%-16s", countryNames.countries[group[i][j]].c_str());
      } else if (j == 1) {
        int PJ = stoi(group[i][2]) + stoi(group[i][3]) + stoi(group[i][4]);
        std::cout << PJ << "\t";
      } else {
        std::cout << group[i][j] << "\t";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void ClientOutput::printMatches(std::vector<std::vector<std::string>> rounds) {
  RoundNames roundNames;
  CountryCodes countryNames;
  if (rounds.size() > 1){
    for (size_t i = 0; i < rounds.size()-1 ; i++) {
      // std::cout << roundNames.rounds.find(rounds[i][0])->second << std::endl;
      std::cout << rounds[i][0] << std::endl;
      std::cout << "Country" << '\t' 
            << "Country" << '\t' 
            << "Score" << std::endl;
      for (size_t j = 1; j < rounds[i].size() ; j++) {
        if(j == 1 || j == 2){
          std::cout << countryNames.countries[rounds[i][j]] << "\t";
        } else {
          std::cout << rounds[i][j] << "\t";
        }
      }
      std::cout << std::endl << std::endl;
    }
  }
}