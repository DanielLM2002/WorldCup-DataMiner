/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "Socket.hpp"

/**
 * @brief Socket constructor
 * @param type Specifies the communication semantics
 * @param ipv6 Indicates if ipv6 is used
 */
Socket::Socket(char type, bool ipv6) {
  this->ipv6 = ipv6;
  this->id = -1;
  this->port = DEFAULT_PORT;
  if (!this->ipv6)
    this->id = type == 's' ? socket(AF_INET, SOCK_STREAM, 0)
                           : socket(AF_INET, SOCK_DGRAM, 0);
  else
    this->id = type == 's' ? socket(AF_INET6, SOCK_STREAM, 0)
                           : socket(AF_INET6, SOCK_DGRAM, 0);
}

Socket::Socket( int id ) {
  id = this->id;
}


Socket::~Socket() {
  this->Close();

// SSL destroy
   if ( nullptr != this->SSLContext ) {
      SSL_CTX_free( (SSL_CTX *) this->SSLContext );
   }
   if ( nullptr != this->SSLStruct ) {
      SSL_free( (SSL *) this->SSLStruct );
   }

}


void Socket::Close(){
  close( this->id );
}



// SSL methods

/*
 *
 */
void Socket::InitSSLContext() {
   const SSL_METHOD * method = TLS_client_method();
   SSL_CTX * context = SSL_CTX_new( method );

   if ( nullptr == context ) {
        perror( "Socket::InitSSLContext" );
        exit( 23 );
    }

    this->SSLContext = (void *) context;

}


/*
 *
 */
void Socket::InitSSL() {

   this->InitSSLContext();
   SSL * ssl = SSL_new( ((SSL_CTX *) this->SSLContext ) );
   if ( nullptr == ssl ) {
      perror( "Socket::InitSSL" );
      exit( 23 );
   }
   this->SSLStruct = (void *) ssl;

}


/*
 *
 */
void Socket::SSLConnect( char * host, int port ) {
   int resultado;

   this->Connect( host, port );	// Establish a non ssl connection first
   SSL_set_fd( (SSL *) this->SSLStruct, this->id );
   resultado = SSL_connect( (SSL *) this->SSLStruct );
   if ( -1 == resultado ) {
      perror( "Socket::SSLConnect" );
      exit( 23 );
   }

}


/*
 *
 */
void Socket::SSLConnect( char * host, char * service ) {
   int resultado;

   this->Connect( host, service );
   SSL_set_fd( (SSL *) this->SSLStruct, this->id );
   resultado = SSL_connect( (SSL *) this->SSLStruct );
   if ( -1 == resultado ) {
      perror( "Socket::SSLConnect" );
      exit( 23 );
   }


}


/*
 *
 */
int Socket::SSLRead( void * buffer, int size ) {
   int resultado;

   resultado = SSL_read( (SSL *) this->SSLStruct, buffer, size );
   if ( -1 == resultado ) {
      perror( "Socket::SSLRead" );
      exit( 23 );
   }

   return resultado;

}


/*
 *
 */
int Socket::SSLWrite( const void *buffer, int size ) {
   int resultado;

   resultado = SSL_write( (SSL *) this->SSLStruct, buffer, size );
   if ( -1 == resultado ) {
      perror( "Socket::SSLWrite" );
      exit( 23 );
   }

   return resultado;

}

