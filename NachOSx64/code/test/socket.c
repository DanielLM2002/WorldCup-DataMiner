#include "syscall.h"

void MemSetter(char* buffer, int newValue, int size) {
   int i = 0;
   for(i; i < size; i++) {
      buffer[i] = (char) 0;
   }
}

int StringLength (char * sl){
   int count = 0;
   int keep =1;
   while(keep ==1){
      ++count;
      if(sl[count] == 0){
         keep =0;
      }
   }
   return count;
}

int main() {
   int id;

   char country[3];
   char * askCountryCode = "Enter the country code: .\n";
   Write(askCountryCode, StringLength(askCountryCode),1);
   Read(country, 3, 2);
   char a[ 512 ];
   Write("Creating Socket\n", StringLength("Creating Socket\n"), 1);
   id = Socket( AF_INET_NachOS, SOCK_STREAM_NachOS );
   Connect( id, "127.0.0.1", 9876 );
   Write("Socket connected, fetching info\n\n", 
            StringLength("Socket connected fetching info\n\n"), 1);
   char * req = "GET /fifa/2018/FRA HTTP/1.1\r\nhost: grupoh.ecci \r\n\r\n";
   int c = 15;
   int i = 0;
   for(; i < 3; ++i){
      req[c + i] = country[i];
   }

   Write( req , StringLength(req), id );
   Write("\nInfo:\n", 
            StringLength("\nInfo:\n"), 1);
   while(Read(a, 512, id) > 0) {
      Write( a, 512, 1 );
      MemSetter(&a, 0, 512);
   }
   Write("-----------\n",StringLength("-----------\n"),1);
   Shutdown( id, 1 );
   Close(id);
}
