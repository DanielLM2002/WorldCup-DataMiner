/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <stdio.h>
#include <string.h>
#include <vector>

#include "Round.hpp"
#include "Socket.hpp"
#include "JsonDataSource.hpp"

typedef struct {
  int PJ = 0;
  int PG = 0;
  int PE = 0;
  int PP = 0;
  int GF = 0;
  int GC = 0;
  int GD = 0;
  int Pts = 0;
  std::string country = "";
} PointsByCountry;

class Output {
  private: 
    JsonDataSource json;
    std::string country;

  public:
    explicit Output();
    ~Output();
    void getInput();
    void buildTable(std::vector<Match>, std::vector<PointsByCountry>);
    void askAgain();
    void handleCountry();
    void printGroup(std::string);
    void printTable(std::vector<PointsByCountry>);
    void printCountryCodes();
    void printMatches();
    void printMatch(Match);
    std::string getGroup();
    std::string toUpperCase(std::string);

};

#endif  // !OUTPUT_HPP
