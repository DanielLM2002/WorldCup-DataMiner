/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "Server.hpp"
#include "HttpParser.hpp"

Server::Server(int nPort): port(nPort) {

}

Server::~Server() {

}

void Server::serve(){
  int childpid;
  char a[512];
  Socket s1('s'), *s2;

  s1.Bind( this->port );		// Port to access this mirror server
  s1.Listen( 5 );		// Set backlog queue to 5 conections
  std::cout << "listening on 9876" << std::endl;
  for( ; ; ) {
    std::cout << "waiting for a request" << std::endl;
    s2 = s1.Accept();	 	// Wait for a conection
    childpid = fork();	// Create a child to serve the request
    if (childpid < 0)
      perror("server: fork error");
    else if (0 == childpid) {  // child code
      s1.Close();	// Close original socket in child
      s2->Read( a, 512 );
      std::cout<< "Received: \n" << a << std::endl; // Read a string from client
      
      HttpParser parser(a);

      std::string country = parser.getCountry();
      std::cout << "Country code: " << country << "." << std::endl;

      //get country data
      ServerResponse os(country);
      os.handleCountry();
      std::string result = os.stringBuffer.str();
      const char* resCountry = &result[0];
      s2->Write(resCountry);
      exit( 0 );	// Exit
    }
    s2->Close();		// Close socket in parent
  }
}
