/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "Match.hpp"

Match::Match(int homeScore, int awayScore, std::string date, std::string loser, std::string winner, std::string homeTeam, std::string awayTeam) {
  this->homeScore = homeScore;
  this->awayScore = awayScore;
  this->date = date;
  this->loser = loser;
  this->winner = winner;
  this->homeTeam = homeScore;
  this->awayTeam = awayScore;
}

Match::~Match() {

}

int Match::getHomeScore() {
  return this->homeScore;
}

int Match::getAwayScore() {
  return this->awayScore;
}

std::string Match::getDate() {
  return this->date;
}

std::string Match::getLoser() {
  return this->loser;
}

std::string Match::getWinner() {
  return this->winner;
}

std::string Match::getHomeTeam() {
  return this->homeTeam;
}

std::string Match::getAwayTeam() {
  return this->awayTeam;
}

void Match::setHomeScore(int homeScore) {
  this->homeScore = homeScore;
}

void Match::setAwayScore(int awayScore) {
  this->awayScore = awayScore;
}

void Match::setDate(std::string date) {
  this->date = date;
}

void Match::setLoser(std::string loser) {
  this->loser = loser;
}

void Match::setWinner(std::string winner) {
  this->winner = winner;
}

void Match::setHomeTeam(std::string homeTeam) {
  this->homeTeam = homeTeam;
}

void Match::setAwayTeam(std::string awayTeam) {
  this->awayTeam = awayTeam;
}
