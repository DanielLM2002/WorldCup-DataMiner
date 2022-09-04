/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "JsonDataSource.hpp"
#include "Socket.hpp"
#include "Match.hpp"
#include "Round.hpp"
#include <sstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <map>
using namespace std;

JsonDataSource::JsonDataSource() {
    int result = this->fetchData();;
    if(result == 0) {
        this->parseDataToRounds();
    } else {
        perror("Cannot get data");
    }
}

JsonDataSource::~JsonDataSource() {

}

Round JsonDataSource::getRound(string roundName){
    return this->rounds.at(roundName);
}

int JsonDataSource::fetchData() {

    const char* osn = "10.1.104.187";  // Public ip
    //const char* osn = "163.178.104.187";  // Private ip 
    const char* request = "GET /futbol/2018/world-cup-2018.json HTTP/1.1\r\nhost: redes.ecci\r\n\r\n";
    
    
    Socket  s( 's' );	// Create a new stream socket for IPv4
    int result = s.Connect( osn, 80 );

    if(result == -1) {
        perror("JsonDataSource Cannot connect to source");
    }

    char a[512];
    s.Write(  request );
    int read = s.Read( a, 512 );
    std::stringstream ss;
    while(read > 0) {
        ss << a;
        memset(a, 0, 512);
        read = s.Read( a, 512 );
    }
    this->data = ss.str();
    s.Close();

    return 1;
}

void JsonDataSource::parseDataToRounds() {

    json jsonValue = json::parse(this->data);

    std::cout << "to implement \n";
}