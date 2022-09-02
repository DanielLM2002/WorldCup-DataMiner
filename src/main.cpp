/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#define IPV4
#define SIZE 1024

#include <stdio.h>
#include <string.h>

#include "Socket.hpp"

#ifdef IPV4
int main(int argc, char * argv[]) {
  const char* os = "http://os.ecci.ucr.ac.cr/";
  //const char* osn = "10.1.104.187";  // Public ip
  const char* osn = "163.178.104.187";  // Private ip  
  const char* request = "GET /futbol/2018/world-cup-2018.json HTTP/1.1\r\nhost: redes.ecci\r\n\r\n";
  Socket s('s');
  char a[512];
  s.Connect(osn, 80);
  s.Write(request);
  while (s.Read(a, 512) != 0) {
    printf("%s\n", a);
    memset(a, 0, 512);
  }

  //char * os = (char *) "http://os.ecci.ucr.ac.cr/";
  //char * reqOS = (char *) "GET /futbol/2018/world-cup-2018.json HTTP/1.1\r\nhost: redes.ecci\r\n\r\n";
  //Socket s( 's', false );	// Create a new stream socket for IPv4
  //char a[ SIZE ];

  //memset( a, 0, SIZE );
  //s.InitSSL();
  //s.SSLConnect( os, (char *) "https" );
  //s.SSLWrite(  (void *) reqOS, strlen( reqOS ) );
  //while ( (s.SSLRead( a, SIZE )) > 0 ) {   // Waits until conection close
  //  printf( "%s\n", a );
  //  memset( a, 0, SIZE );
  //}
  //printf( "%s\n", a );
}
#endif

#ifdef IPV6
int main( int argc, char * argv[] ) {
  const char* os = "fe80::194d:4e78:60c:fedc%eno1";
  const char* request = "GET / HTTP/1.1\r\nhost: redes.ecci\r\n\r\n";

  Socket s('s', true);
  char a[512];

  memset(a, 0, 512);
  s.Connect(os, (char *) "http");
  s.Write(request);
  s.Read(a, 512);
  printf("%s\n", a);
}
#endif
