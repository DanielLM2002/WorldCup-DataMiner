/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "HttpParser.hpp"

HttpParser::HttpParser(int nPort) {
    port = nPort;
}

HttpParser::~HttpParser() {

}

std::string HttpParser::getHeaderValues(std::string header, std::string &method, std::string &path, std::string &version) {
    std::vector<std::string> headerParts = Util::split(header, " ");
    method = headerParts[0];
    path = headerParts[1];
    version = headerParts[2];
    return headerParts[0];
}

std::string HttpParser::getPathValues(std::string path, std::string &pathName, std::string &pathExtension) {
    std::vector<std::string> pathParts = Util::split(path, ".");
    pathName = pathParts[0];
    pathExtension = pathParts[1];
    return pathParts[0];
}
