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
  std::vector<PointsByCountry> countriesByGroup;
  Round round = json.getRound(group);
  std::vector<Match> roundMatches = round.getMatches();
  std::cout << round.getName() << std::endl << std::endl;
  int index = 0;
  for (size_t i = 0; i < roundMatches.size(); i++) {
    Match match = roundMatches[i];
    bool foundCountry = false;
    for (size_t j = 0; j < countriesByGroup.size(); j++){
      if (countriesByGroup[j].country == match.getHomeTeam()) {
        foundCountry = true;
      }
    }
    if (!foundCountry) {
      PointsByCountry pts;
      countriesByGroup.push_back(pts);
      countriesByGroup[index].country = match.getHomeTeam();
      index++;
    }
  }
  buildTable(roundMatches, countriesByGroup);
  printMatches();
}

void Output::buildTable(std::vector<Match> roundMatches, std::vector<PointsByCountry> countriesByGroup) {
  std::cout << "Country" << "\t\t" << "PJ" << '\t' << "PG" << '\t' << "PE" << '\t' << "PP" << '\t' << "GF" << '\t' << "GC" << '\t' << "GD" << '\t' << "Pts" << std::endl;
  for (size_t i = 0; i < roundMatches.size(); ++i) {
    Match match = roundMatches[i];
    for (size_t j = 0; j < countriesByGroup.size(); j++) {
      if (match.getAwayTeam() == countriesByGroup[j].country) {
        countriesByGroup[j].PJ++;
        countriesByGroup[j].GF += match.getAwayScore();
        countriesByGroup[j].GC += match.getHomeScore();
        if (match.getHomeScore() < match.getAwayScore()) {
          countriesByGroup[j].PG++;
        }
        if (match.getHomeScore() > match.getAwayScore()) {
          countriesByGroup[j].PP++;
        }
        if (match.getHomeScore() == match.getAwayScore()) {
          countriesByGroup[j].PE++;
        }
      }
      if (match.getHomeTeam() == countriesByGroup[j].country) {
        countriesByGroup[j].PJ++;
        countriesByGroup[j].GF += match.getHomeScore();
        countriesByGroup[j].GC += match.getAwayScore();
        if (match.getHomeScore() > match.getAwayScore()) {
          countriesByGroup[j].PG++;
        }
        if (match.getHomeScore() < match.getAwayScore()) {
          countriesByGroup[j].PP++;
        }
        if (match.getHomeScore() == match.getAwayScore()) {
          countriesByGroup[j].PE++;
        }
      }
    }
  }
  for (size_t i = 0; i < countriesByGroup.size(); ++i) {
    countriesByGroup[i].GD = countriesByGroup[i].GF - countriesByGroup[i].GC;
    countriesByGroup[i].Pts = (3*countriesByGroup[i].PG) + countriesByGroup[i].PE;
  }
  printTable(countriesByGroup);
}

void Output::printTable(std::vector<PointsByCountry> countriesByGroup) { 
  while (countriesByGroup.size() != 0) {
    int highestScore = 0;
    for (size_t i = 0; i < countriesByGroup.size(); ++i) {
      if (countriesByGroup[i].Pts > countriesByGroup[highestScore].Pts) {
        highestScore = i;
      }
    }
    std::cout << countriesByGroup[highestScore].country << "\t\t" << countriesByGroup[highestScore].PJ << '\t' << countriesByGroup[highestScore].PG << '\t' << countriesByGroup[highestScore].PE << '\t' << countriesByGroup[highestScore].PP << '\t' << countriesByGroup[highestScore].GF << '\t' << countriesByGroup[highestScore].GC << '\t' << countriesByGroup[highestScore].GD << '\t' << countriesByGroup[highestScore].Pts << std::endl;
    countriesByGroup.erase(countriesByGroup.begin() + highestScore);
  }
  std::cout << std::endl;
}

void Output::printCountryCodes() {
  CountryCodes codes;
  for (auto& x: codes.countries) {
    std::cout << x.first << ": " << x.second << '\n';
  }
  std::cout << std::endl;
  getInput();
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
        std::cout << tempRound.getName() << std::endl;
        printMatch(roundMatches[j]);
      }
    }
  }
}

void Output::printMatch(Match match) {
  std::cout << "Country" << '\t' << "Country" << "\t\t" << "Score" << std::endl;
  std::string score = "";
  score += std::to_string(match.getHomeScore());
  score += " - ";
  score += std::to_string(match.getAwayScore());
  std::cout << match.getHomeTeam() << '\t' << match.getAwayTeam() << "\t\t" << score << std::endl << std::endl;
}