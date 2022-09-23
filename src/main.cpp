/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

// #define JSON
#define SIZE 1024
#define SERVER_CODE

#include <stdio.h>
#include <string.h>

#include "Output.hpp"
#include "Util.hpp"

#ifdef JSON
int main() { 
  Output output;
  output.getInput();
}
#endif

#ifdef SERVER_CODE
int main( int argc, char ** argv ) {
   int childpid;
   char a[512];
   Socket s1('s'), *s2;

   s1.Bind( 9876 );		// Port to access this mirror server
   s1.Listen( 5 );		// Set backlog queue to 5 conections
   std::cout << "listening on 9876" << std::endl;
   for( ; ; ) {
      s2 = s1.Accept();	 	// Wait for a conection
      childpid = fork();	// Create a child to serve the request
      if ( childpid < 0 )
         perror("server: fork error");
      else if (0 == childpid) {  // child code
              s1.Close();	// Close original socket in child
              s2->Read( a, 512 );
              std::cout<< "Received: " << a << std::endl; // Read a string from client
              // to check if the 
              std::vector<std::string> request = Util::split(a, "\r\n");
              // std::cout << "Size: " << request.at(0).size() << std::endl;
              // std::cout << "at 0: " << request.at(0) << "." << std::endl;
              if(Util::trim(request.at(0)).compare("hi:connect")==0){
                std::vector<std::string> fromParts = 
                                              Util::split(request.at(0),":");
                std::cout << "Client:" << fromParts[1] << std::endl;// from who

                const char * response = "hi:accepted\r\n\r\n";
                s2->Write( response );	// Write it back to client, this is the mirror function

                // read next request
                memset(a, 0, 512);
                s2->Read(a, 512);
                std::cout << "Received back from client:\n" << a << std::endl;
                std::string stringResponse = "CRC,USA,3,0\r\n\r\n";
                const char * resCountry = &stringResponse[0];
                s2->Write(resCountry);
              }
              exit( 0 );	// Exit
      }
      s2->Close();		// Close socket in parent
   }

}
#endif


#ifdef CLIENT_CODE
int main( int argc, char ** argv ) {

   std::string input;
   std::cout << "Please enter the code of the country you wish to check (or type h to check country codes): ";
   getline(std::cin, input);

   Socket s('s');     // Crea un socket de IPv4, tipo "stream"
   char buffer[ 512 ];
   std::cout<<"trying to connect"<<std::endl;
   s.Connect( "127.0.0.1", 9876 ); // Same port as server
   std::cout<<"Connected"<<std::endl;
   const char * b = "hi:connect\r\nfrom:client-ubuntu\r\n\r\n";
   std::cout << "Sending connection request: \n" << b << std::endl;
   s.Write( b );		// Send first program argument to server
   s.Read( buffer, 512 );	// Read the answer sent back from server
   printf( "Response from server:\n%s.\n", buffer );	// Print the received string
   
   
   std::string req = "get\r\ncountry:"+input+"\r\n\r\n";
   std::cout << "Sending get request: \n" << req << std::endl;
   s.Write(&req[0]);
   memset(buffer,0, 512);
   s.Read( buffer, 512 );	// Read the answer sent back from server
   printf( "Response from get:\n%s.\n", buffer );
}

#endif // CLIENT_CODE