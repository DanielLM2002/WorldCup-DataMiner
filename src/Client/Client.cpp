#include "Client.hpp"

Client::Client(string nHost, int nPort):
                host(nHost), port(nPort)

{
}

Client::~Client()
{
}

void Client::start() {
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
   
   
   std::string req = "get\r\n"+input+"\r\n\r\n";
   std::cout << "Sending get request: \n" << req << std::endl;
   s.Write(&req[0]);
   memset(buffer,0, 512);
   s.Read( buffer, 512 );	// Read the answer sent back from server
   printf( "Response from get:\n%s.\n", buffer );
}