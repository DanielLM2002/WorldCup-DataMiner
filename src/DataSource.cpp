/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _DATA_SOURCE_
#define _DATA_SOURCE_

#include "Match.hpp"
#include "Round.hpp"
#include <map>
using namespace std;

class DataSource {

 public:
   //DataSource() {}
   virtual ~DataSource() {}

   /**
    * @brief Get the Round object
    * 
    * @return Round
    */
   virtual Round getRound(string);

 protected:
   map <string, Round> rounds;   

};

#endif  // _DATA_SOURCE_