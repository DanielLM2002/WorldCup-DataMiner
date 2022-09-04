/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _JSON_DATA_SOURCE_
#define _JSON_DATA_SOURCE_

#include "Socket.hpp"
#include "Round.hpp"
#include <map>
using namespace std;

class JsonDataSource {
 public:
   JsonDataSource();
   ~JsonDataSource();

   /**
    * @brief Get the Round object
    * 
    * @return Round 
    */
   Round getRound(string roundName);
 
 private:

   string data;

   /**
    * @brief fetchs the data from the server
    * 
    */
   int fetchData();

   /**
    * @brief storing rounds associated to each round type
    *        like "group_a" associated to Round with type "group_a"
    * 
    */
   map <string, Round> rounds;

   /**
    * @brief Parse the data obtained from the server
    *        and parses it to Rounds;
    */
   void parseDataToRounds();

};

#endif //  _JSON_DATA_SOURCE_