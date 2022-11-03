#include "syscall.h"

int main() {
   int id;
   char a[ 512 ];

   id = Socket( AF_INET_NachOS, SOCK_STREAM_NachOS );
   Connect( id, "127.0.0.1", 9876 );
   Write( "GET /fifa/2018/CRC HTTP/1.1\r\nhost: grupoh.ecci \r\n\r\n", 57, id );
   Read( a, 512, id );
   Write( a, 512, 1 );
   Close( id );

}

