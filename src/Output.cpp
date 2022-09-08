/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "Output.hpp"
#include "CountryCodes.hpp"

Output::Output() {
  this->country = "CRC";
}

Output::~Output() {
}

void Output::getInput() {
  std::string input;
  std::cout << "Please enter the code of the country you wish to check (or type h to check country codes): ";
  getline (std::cin, input);
  input = toUpperCase(input);
  std::cout << std::endl;
  if (input == "H") {
    printCountryCodes();
  }
  else {
    this->country = input;
    handleCountry();
  }
}

void Output::handleCountry() {
  std::string group = ""; 
  if (this->country.length() == 3) {
    CountryCodes codes;
    if (codes.countries.count(this->country) == 1) {
      this->country = codes.countries.find(this->country)->second;
      group = getGroup();
      if (group == ""){
        std::cout << "This team did not qualify in the world cup" << std::endl;
        askAgain();
      } else {
        printGroup(group);
        askAgain();
      }
    }
    else {
      std::cout << "Country code not available" << std::endl;
      askAgain();
    }
  }
}

std::string Output::toUpperCase(std::string str){
  std::string temp = "";
   for (size_t i = 0; i < str.length(); i++) {
    temp += std::toupper(str[i]);
  }
  return temp;
}

std::string Output::getGroup() {
  bool foundGroup = false;
  std::string index = "";
  std::vector<std::string> group = {
    "group_a",
    "group_b",
    "group_c",
    "group_d",
    "group_e",
    "group_f",
    "group_g",
    "group_h"
    };
  for (size_t i = 0; i < group.size() && !foundGroup; i++) {
    Round tempRound = json.getRound(group[i]);
    std::vector<Match> roundMatches = tempRound.getMatches();
    for (size_t j = 0; j < roundMatches.size() && !foundGroup; j++) {
      if (roundMatches[j].getHomeTeam() == this->country || roundMatches[j].getAwayTeam() == this->country) {
        foundGroup = true;
        index = group[i];
      }
    }
  }
  return index;
}

void Output::buildTable() {
}

std::string Output::print() {
  return 0;
}

void Output::askAgain() {
  std::string answer;
  std::cout << "Would you like to check another country (yes/no): ";
  getline (std::cin, answer);
  answer = toUpperCase(answer);
  if (answer == "YES") {
    std::cout << std::endl;
    getInput();
  }
  else {
    std::cout << std::endl << "Goodbye! :C" << std::endl;
  }
}

void Output::printGroup(std::string group) { 
  Round round = json.getRound(group);
  std::vector<Match> roundMatches = round.getMatches();
  std::cout << round.getName() << std::endl << std::endl;
  std::cout << "Country" << "\t\t" << "PJ" << '\t' << "PG" << '\t' << "PE" << '\t' << "PP" << '\t' << "GF" << '\t' << "GC" << '\t' << "GD" << '\t' << "Pts" << std::endl;
  for (size_t index = 0; index < roundMatches.size(); ++index) {
    Match match = roundMatches[index];
    // print group
  }
  printMatches();
}

void Output::printCountryCodes() {

}

void Output::printMatches() {
  std::vector<std::string> round = {
    "round_16",
    "round_8",
    "round_4",
    "round_2_loser",
    "round_2"
    };
  for (size_t i = 0; i < round.size() ; i++) {
    Round tempRound = json.getRound(round[i]);
    std::vector<Match> roundMatches = tempRound.getMatches();
    for (size_t j = 0; j < roundMatches.size() ; j++) {
      if (roundMatches[j].getHomeTeam() == this->country || roundMatches[j].getAwayTeam() == this->country) {
        printMatch(roundMatches[j]);
      }
    }
  }
}

void Output::printMatch(Match match) {
  // std::cout << round[i] << std::endl;
  std::cout << "Country" << '\t' << "Country" << "\t\t" << "Score" << std::endl;
  std::string score = "";
  score += std::to_string(match.getHomeScore());
  score += " - ";
  score += std::to_string(match.getAwayScore());
  std::cout << match.getHomeTeam() << '\t' << match.getAwayTeam() << "\t\t" << score << std::endl << std::endl;
}