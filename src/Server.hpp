#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include "Socket.hpp"
#include "common/Util.hpp"
#include "OutputString.hpp"

#include <string>
#include <vector>
using namespace std;

class Server{
private:
    /* data */
    int port;
public:
    Server(int nPort);
    ~Server();
    void serve();
};

#endif  // _SERVER_HPP_
