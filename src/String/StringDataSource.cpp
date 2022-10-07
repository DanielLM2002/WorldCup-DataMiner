/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "StringDataSource.hpp"

StringDataSource::StringDataSource() {

}

StringDataSource::~StringDataSource() {

}

void StringDataSource::parse(char* buffer) {
  std::vector<std::string> lines = Util::split(buffer,"\n");
  std::vector<std::string> temp;
  for (int i = 0; i < (int) lines.size(); i++){
    temp = Util::split(lines[i],"\t");
    if (i < 4) {
      this->group.push_back(temp);
    } else {
      this->round.push_back(temp);
    }
  }
  this->orderGroupByPosition();
}

std::vector<std::vector<std::string>> StringDataSource::getGroup() {
  return this->group;
}

std::vector<std::vector<std::string>> StringDataSource::getRounds() {
  return this->round;
}

void StringDataSource::orderGroupByPosition() {
  std::vector<std::vector<std::string>> temp;
  while (this->group.size() != 0) {
    int highestScore = 0;
    for (size_t index = 0; index < this->group.size(); ++index) {
      if (this->group[index][1] > this->group[highestScore][1])
        highestScore = index;
    }
    temp.push_back(group[highestScore]);
    this->group.erase(this->group.begin() + highestScore);
  }
  this->group = temp;
}
