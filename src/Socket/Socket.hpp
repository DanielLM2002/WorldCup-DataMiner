/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef _SOCKET_
#define _SOCKET_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <iostream>

#define DEFAULT_PORT 8080;

class Socket {
 private:
  /// ID of the socket
  int id;
  /// Number of the port
  int port;
  /// Check if ipv6 is going to be used
  bool ipv6;
  /// Struct of SSL
  void* SSLStruct;
  /// Context of SSL
  void* SSLContext;
  
 public:
  /**
   * @brief Constructor
   * @param type Specifies the communication semantics
   * @param ipv6 Indicates if ipv6 is used
   */
  explicit Socket(char, bool = false);

  /**
   * @brief Constructor
   * @param id Number of id
   */
  explicit Socket(int);

  /**
   * @brief Destroyer
   */
  ~Socket();

  /**
   * @brief Method that connects with an ip address and a port for IPV4
   * @param host Ip address
   * @param port Port number
   * @return int 
   */
  int Connect(const char*, int);

  /**
   * @brief Method that connects with an ip address using a service for IPV4
   * @param hostip Ip address
   * @param service Service that is used
   * @return int 
   */
  int Connect(const char*, const char*);

  /**
   * @brief Method that connects with an ip address and a port for IPV6
   * @param host Ip address
   * @param port Port number
   * @return int 
   */
  int ConnectIPV6(const char*, int);

  /**
   * @brief Method that connects with an ip address using a service for IPV6
   * @param host Ip address
   * @param service Service that is used
   * @return int 
   */
  int ConnectIPV6(const char*, const char*);
  
  /**
   * @brief Method that closes a socket
   */
  void Close();

  /**
   * @brief Method that reads data from a socket
   * @param data Data to read
   * @param size Size of the data vector
   * @return int 
   */
  int Read(char*, int);

  /**
   * @brief Method that writes to a socket
   * @param data Data to write
   * @return int 
   */
  int Write(const char*);

  /**
   * @brief Method that indicates to the operating system that the
   *        socket is going to act passively
   * @param queue Number of queue
   * @return int 
   */
  int Listen(int);

  /**
   * @brief Method that associates the socket with a port
   * @param port Number of the port
   * @return int 
   */
  int Bind(int);

  /**
   * @brief Method that accepts conections send by clients
   * @return Socket* 
   */
  Socket* Accept();

  /**
   * @brief Method that partially closes the connectivity of a 
   *        socket
   * @param mode Type of closure to do
   * @return int 
   */
  int Shutdown(int);

  /**
   * @brief Method that sets a new ID
   * @param id Number of new id
   */
  void SetId(int);

  /**
   * @brief Method that inits the SSL properties of the socket
   */
  void InitSSL();

  /**
   * @brief Method that inits the SSL context of the socket
   */
  void InitSSLContext();

  /**
   * @brief Method that connects with an ip address and a port for IPV4 
   *        using SSL protocol
   * @param host Ip address
   * @param port Port number
   * @return int 
   */
  int SSLConnect(const char*, int);

  /**
   * @brief Method that connects with an ip address for IPV4 using a service
   *        and SSL protocol
   * @param host Ip address
   * @param service Service that is used
   * @return int 
   */
  int SSLConnect(const char*, const char*);

  /**
   * @brief Method that reads data from a socket using SSL protocol
   * @param data Data to read
   * @param size Size of the data vector
   * @return int 
   */
  int SSLRead(const void*, int);

  /**
   * @brief Method that writes to a socket using SSL protocol
   * @param data Data to write
   * @param size Size of the data vector
   * @return int 
   */
  int SSLWrite(const void*, int);

  /**
   * @brief Method that sends to a socket using UDP protocol
   * @param msg Data to write
   * @param len length of data
   * @param addr address to write
   */
  int sendTo( const void *, int, void * );
  
  /**
   * @brief Method that receives from a socket using UDP protocol
   * @param buffer where to write
   * @param len length of data
   * @param addr address to receive
   */
  int recvFrom( void *, int, void * );
};

#endif  // !_SOCKET_
