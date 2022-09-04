/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "Round.hpp"

Round::Round(std::string code, std::string name) {
  this->code = code;
  this->name = name;
}

Round::~Round() {

}

void Round::addMatch(Match match) {
  this->matches.push_back(match);
}

std::string Round::getCode() {
  return this->code;
}

std::string Round::getName() {
  return this->name;
}

std::vector<Match> Round::getMatches() {
  return this->matches;
}

void Round::setCode(std::string code) {
  this->code = code;
}

void Round::setName(std::string name) {
  this->name = name;
}

void Round::setMatches(std::vector<Match> matches) {
  this->matches = matches;
}