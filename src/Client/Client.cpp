/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "Client.hpp"
#include "../ClientOutput/ClientOutput.hpp"

Client::Client(std::string nHost, int nPort):
               host(nHost), port(nPort) {
}

Client::~Client() {
}

void Client::start() {
  this->getInput();
}

void Client::getInput() {
  bool validInput = true;
  std::string input;
  std::cout << "Please enter the code of the country you wish to check (or type h to check country codes): ";
  getline(std::cin, input);
  for (int index = 0; input[index]; ++index) {
    if (!isalpha(input[index])) {
      validInput = false;
      break;
    }
  }

  if (validInput == true) {
    input = toUpperCase(input);
    std::cout << std::endl;
    if (input == "H") {
      this->printCountryCodes();
    } else {
      Socket s('s'); // Crea un socket de IPv4, tipo "stream"
      s.Connect(&(this->host)[0], this->port); // Same port as server
    
      std::string req = "GET /fifa/2018/"+input+" HTTP/1.1\r\nhost: grupoh.ecci \r\n\r\n";
      //std::cout << "Sending get request: \n" << req << std::endl;
      s.Write(&req[0]);
      memset(this->buffer,0, 512);
      s.Read( buffer, 512 );	// Read the answer sent back from server
      std::string localBuffer(this->buffer);
      if(localBuffer.find("HTTP/1.1 404 (NOT FOUND)\r\n") != std::string::npos) {
        std::cout << "Input error: 404 (NOT FOUND)" << std::endl;
      } else { //todo check for empty message
        // llamar a la clase output
        ClientOutput output;
        output.handleBuffer(this->buffer);
      }
    }
  } else {
    std::cout << "Invalid argument" << std::endl;
  }
  this->askAgain();
}

std::string Client::toUpperCase(std::string str){
  std::string temp = "";
   for (size_t index = 0; index < str.length(); index++)
    temp += std::toupper(str[index]);
  return temp;
}

void Client::askAgain() {
  std::string answer;
  std::cout << "Would you like to check another country (yes/no): ";
  getline (std::cin, answer);
  answer = toUpperCase(answer);
  if (answer == "YES") {
    std::cout << std::endl;
    this->getInput();
  }
  else {
    std::cout << std::endl << "Goodbye! :C" << std::endl;
  }
}

void Client::printCountryCodes() {
  CountryCodes codes;
  for (auto& x: codes.countries)
    std::cout << x.first << ": " << x.second << '\n';
  std::cout << std::endl;
  this->getInput();
}