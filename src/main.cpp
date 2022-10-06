/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

// #define JSON
#define SIZE 1024
#define CLIENT_CODE

#include <stdio.h>
#include <string.h>

#include "Output.hpp"
#include "OutputString.hpp"
#include "Util.hpp"
#include "Server.hpp"
#include "Client.hpp"

#ifdef JSON
int main() { 
  Output output;
  output.getInput();
}
#endif

#ifdef SERVER_CODE
int main( int argc, char ** argv ) {
   Server ser(9876);
   ser.serve();

}
#endif


#ifdef CLIENT_CODE
int main( int argc, char ** argv ) {

   Client client("127.0.0.1",9573);
   client.start();
}

#endif // CLIENT_CODE