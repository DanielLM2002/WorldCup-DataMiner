/// @copyright 2022 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Michelle Fonseca Carrillo <michelle.fonsecacarrillo@ucr.ac.cr>
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Jorge Loría López <jorge.lorialopez@ucr.ac.cr>
/// This code is released under the GNU Public License version 3

#include "JsonDataSource.hpp"

#include "Util.hpp"

JsonDataSource::JsonDataSource() {
  int result = this->fetchDataSSL();
  if(result == 1)
    this->parseDataToRounds();
  else
    perror("Cannot get data");
}

JsonDataSource::~JsonDataSource() {

}

Round JsonDataSource::getRound(std::string roundName){
  return this->rounds.at(roundName);
}

int JsonDataSource::fetchData() {
  // const char* osn = "10.1.104.187";  // Public ip
  const char* osn = "163.178.104.187";  // Private ip 
  const char* request = "GET /futbol/2018/world-cup-2018.json HTTP/1.1\r\nhost: redes.ecci\r\n\r\n";  
  Socket s('s');	// Create a new stream socket for IPv4
  char responseRead[8];
  int read;
  int firstChar;
  int result = s.Connect(osn, 80);
  int responseReadSize = 8;

  if(result == -1)
    perror("JsonDataSource Cannot connect to source");

  s.Write(request);
  read = s.Read(responseRead, responseReadSize);
  std::stringstream ss;
  while(read > 0) {
    ss << responseRead;
    memset(responseRead, '\0', responseReadSize);
    read = s.Read(responseRead, responseReadSize);
  }    
  s.Close();
    
  this->data = ss.str();
  // remove http headers
  firstChar = this->data.find("{",0);
  this->data = this->data.erase(0, firstChar);
  return result;
}

int JsonDataSource::fetchDataSSL() {
  // const char* osn = "10.1.104.187";  // Public ip
  const char* osn = (char *) "163.178.104.187";  // Private ip 
  const char* request = (char *) "GET /futbol/2018/world-cup-2018.json HTTP/1.1\r\nhost: redes.ecci\r\n\r\n";  
  Socket s('s', false);	// Create a new stream socket for IPv4
  char responseRead[8];
  int read;
  int firstChar;
  s.InitSSL();
  int result = s.SSLConnect(osn, 443);
  int responseReadSize = 8;

  if(result == -1) {
    perror("JsonDataSource Cannot connect to source");
  }

  s.SSLWrite(request, strlen(request));
  read = s.SSLRead(responseRead, responseReadSize);
  std::stringstream ss;
  while(read > 0) {
    ss << responseRead;
    memset(responseRead, '\0', responseReadSize);
    read = s.SSLRead(responseRead, responseReadSize);
  }    
  s.Close();
  
  this->data = ss.str();
  // remove http headers
  firstChar = this->data.find("{",0);
  this->data = this->data.erase(0, firstChar);
  return result;
}

void JsonDataSource::parseDataToRounds() {
  json jsonData = json::parse(this->data);
  this->parseRounds(jsonData, "groups", "group_");
  this->parseRounds(jsonData, "knockout", "");
}

void JsonDataSource::parseRounds(json jsonData, std::string roundsKey, std::string roundCodePref) {
  json rounds = jsonData[roundsKey];
  for (json::iterator it = rounds.begin(); it != rounds.end(); ++it) {
    std::string roundKey = it.key();
    std::string roundCode = roundCodePref + roundKey;
    std::string roundName = it.value()["name"];
    Round round(roundCode, roundName);    
    json matches = it.value()["matches"];
    round.setMatches( this->parseMatches(matches) );
    this->rounds.insert({roundCode, round});
  }
}

std::vector<Match> JsonDataSource::parseMatches(json matches) {
  std::vector<Match> matchesArray;
  std::string homeScoreString;
  std::string awayScoreString;
  std::string winner;
  std::string loser;
  int homeScore;
  int awayScore;
  json info;
  for(json::iterator matchIt = matches.begin(); matchIt != matches.end(); ++matchIt) {
    info = matchIt.value();
    homeScoreString = info["home_score"];
    awayScoreString = info["away_score"];
    homeScore = std::atoi(&homeScoreString[0]);
    awayScore = std::atoi(&awayScoreString[0]);
    // if winner/loser field is null/not-set then calculate it
    winner = info["home_team"];
    loser = info["away_team"];
    if (!info.contains("winner")) {
      if (homeScore < awayScore) {
        winner = info["away_team"];
        loser = info["home_team"];
      } else {
        winner = "none";
        loser = "none";
      }
    }
    Match tempMatch(
      homeScore,
      awayScore,
      info["date"],
      Util::trim(loser),
      Util::trim(winner),
      Util::trim( info["home_team"] ),
      Util::trim( info["away_team"] )
    );
    matchesArray.push_back(tempMatch);
  }
  return matchesArray;
}
