/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _STRING_DATA_SOURCE_
#define _STRING_DATA_SOURCE_

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

class StringDataSource {

private:
  std::vector<std::vector<std::string>> group;
  std::vector<std::vector<std::string>> round;
  
public:
    StringDataSource();
    ~StringDataSource();

    void parse(char*);
    void orderGroupByPosition();
    std::vector<std::vector<std::string>> getGroup();
    std::vector<std::vector<std::string>> getRounds();
};

#endif // _STRING_DATA_SOURCE_