/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#ifndef SOCKET_HPP
#define SOCKET_HPP

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
  int id;
  int port;
  bool ipv6;
  void* SSLStruct;
  void* SSLContext;
  
 public:
  explicit Socket(char, bool = false);
  explicit Socket(int);
  ~Socket();
  int Connect(const char*, int);
  int Connect(const char*, const char*);
  int ConnectIPV6(const char*, int);
  int ConnectIPV6(const char*, const char*);
  void Close();
  int Read(char*, int);
  int Write(const char*, int);
  int Write(const char*);
  int Listen(int);
  int Bind(int);
  Socket* Accept();
  int Shutdown(int);
  void SetId(int);
  // SSL Methods
  void InitSSLContext();
	void InitSSL();
	int SSLConnect(const char*, int);
	int SSLConnect(const char*, char*);
	int SSLRead(void*, int);
	int SSLWrite(void*, int);
};

#endif  // !SOCKET_HPP
