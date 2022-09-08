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

class Output {
  private: 
    JsonDataSource json;
    std::string country;

  public:
    explicit Output();
    ~Output();
    void getInput();
    void buildTable();
    void askAgain();
    void handleCountry();
    void printGroup(std::string);
    void printCountryCodes();
    void printMatches();
    void printMatch(Match);
    std::string getGroup();
    std::string toUpperCase(std::string);
    std::string print();

};

#endif  // !OUTPUT_HPP
