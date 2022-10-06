/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3


#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#include "../Socket/Socket.hpp"

class Client {

private:
    /* data */
    string host;
    int port;

public:
    Client(string nHost, int nPort);
    ~Client();
    void start();

};


#endif // _CLIENT_HPP_