/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
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
  this->SSLStruct = nullptr;
  this->SSLContext = nullptr;
  if (!this->ipv6)
    this->id = type == 's' ? socket(AF_INET, SOCK_STREAM, 0)
                           : socket(AF_INET, SOCK_DGRAM, 0);
  else
    this->id = type == 's' ? socket(AF_INET6, SOCK_STREAM, 0)
                           : socket(AF_INET6, SOCK_DGRAM, 0);
}

Socket::Socket( int id ) {
  this->id = id;
}

/**
 * @brief Method that closes a socket
 */
Socket::~Socket() {
  this->Close();
  // SSL destroy
  if (this->SSLContext == nullptr)
    SSL_CTX_free( (SSL_CTX *) this->SSLContext );
  if (this->SSLStruct == nullptr)
    SSL_free( (SSL *) this->SSLStruct );
}

void Socket::Close(){
  close(this->id);
}

/**
 * @brief Method that connects with a port and an ip address
 * @param hostip Ip address
 * @param port Port number
 * @return int 
 */
int Socket::Connect(const char* hostip, int port) {
  struct sockaddr_in host4;
  memset(reinterpret_cast<char *>(&host4), 0, sizeof(host4));
  host4.sin_family = AF_INET;
  inet_pton(AF_INET, hostip, &host4.sin_addr);
  host4.sin_port = htons(port);
  int st = connect(this->id, reinterpret_cast<sockaddr *>(&host4),
    sizeof(host4));
  if (st == -1) {
    perror("Socket::Connect");
    exit(2);
  }
  return st;
}

/**
 * @brief Method that connects with a port and an ip address
 * @param hostip Ip address
 * @param port Port address
 * @return int 
 */
int Socket::Connect(const char* hostip, const char* port) {
  struct sockaddr_in host4;
  memset(reinterpret_cast<char *>(&host4), 0, sizeof(host4));
  host4.sin_family = AF_INET;
  inet_pton(AF_INET, hostip, &host4.sin_addr);
  host4.sin_port = htons(atoi(port));
  int st = connect(this->id, reinterpret_cast<sockaddr *>(&host4),
           sizeof(host4));
  if (st == -1) {
    perror("Socket::Connect");
    exit(2);
  }
  return st;
}

/**
 * @brief Method that connects with a port and an ip address
 * in IPV6
 * @param hostip Ip address
 * @param port Port address
 * @return int 
 */
int Socket::ConnectIPV6(const char* hostip, int port) {
  struct sockaddr_in6 host6;
  memset(reinterpret_cast<char *>(&host6), 0, sizeof(host6));
  host6.sin6_family = AF_INET6;
  inet_pton(AF_INET6, hostip, &host6.sin6_addr);
  host6.sin6_port = htons(port);
  int st = connect(this->id, reinterpret_cast<sockaddr *>(&host6),
           sizeof(host6));
  if (st == -1) {
    perror("Socket::Connect");
    exit(2);
  }
  return st;
}

/**
 * @brief Method that connects with a port and an ip address
 * in IPV6
 * @param hostip Ip address
 * @param port Port address
 * @return int 
 */
int Socket::ConnectIPV6(const char* hostip, const char* port) {
  struct sockaddr_in6 host6;
  memset(reinterpret_cast<char *>(&host6), 0, sizeof(host6));
  host6.sin6_family = AF_INET6;
  inet_pton(AF_INET6, hostip, &host6.sin6_addr);
  host6.sin6_port = htons(atoi(port));
  int st = connect(this->id, reinterpret_cast<sockaddr *>(&host6),
           sizeof(host6));
  if (st == -1) {
    perror("Socket::Connect");
    exit(2);
  }
  return st;
}

/**
 * @brief Method that reads from a socket
 * @param info Information to read
 * @param length Size of the information vector
 * @return int 
 */
int Socket::Read(char* info, int length) {
  return read(this->id, info, length);
}

/**
 * @brief Method that writes to a socket
 * @param info Information to write
 * @return int 
 */
int Socket::Write(const char* info) {
  return write(this->id, info, strlen(info));
}

/**
 * @brief 
 */
void Socket::InitSSLContext() {
  const SSL_METHOD* method = TLS_client_method();
  SSL_CTX* context = SSL_CTX_new(method);
  if (context == nullptr) {
    perror( "Socket::InitSSLContext" );
    exit( 23 );
  }
  this->SSLContext = (void *) context;
}

/**
 * @brief 
 */
void Socket::InitSSL() {
  this->InitSSLContext();
  SSL* ssl = SSL_new(((SSL_CTX *) this->SSLContext));
  if (ssl == nullptr) {
    perror( "Socket::InitSSL" );
    exit( 23 );
  }
  this->SSLStruct = (void *) ssl;
}

/**
 * @brief 
 * @param host 
 * @param port 
 * @return int 
 */
int Socket::SSLConnect(const char* host, int port) {
  int result;
  this->Connect( host, port );  // Establish a non ssl connection first
  SSL_set_fd((SSL *) this->SSLStruct, this->id);
  result = SSL_connect((SSL *) this->SSLStruct);
  if (result == -1) {
    perror( "Socket::SSLConnect" );
    exit( 23 );
  }
  return result;
}

/**
 * @brief 
 * @param host 
 * @param service 
 * @return int 
 */
int Socket::SSLConnect(const char* host, const char* service) {
  int result;
  this->Connect(host, service);
  SSL_set_fd((SSL *) this->SSLStruct, this->id);
  result = SSL_connect((SSL *) this->SSLStruct);
  if (result == -1) {
    perror( "Socket::SSLConnect" );
    exit( 23 );
  }
  return result;
}

/**
 * @brief 
 * @param buffer 
 * @param size 
 * @return int 
 */
int Socket::SSLRead(const void* buffer, int size) {
  int result;
  result = SSL_read((SSL *) this->SSLStruct, (void *) buffer, size);
  if (result == -1) {
    perror( "Socket::SSLRead" );
    exit( 23 );
  }
  return result;
}

/**
 * @brief 
 * @param buffer 
 * @param size 
 * @return int 
 */
int Socket::SSLWrite(const void* buffer, int size) {
  int result;
  result = SSL_write((SSL *) this->SSLStruct, buffer, size);
  if ( result == -1) {
    perror( "Socket::SSLWrite" );
    exit( 23 );
  }
  return result;
}
