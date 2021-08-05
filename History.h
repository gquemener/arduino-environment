#ifndef HISTORY_H
#define HISTORY_H

#include "Subscriber.h"
#include "Logger.h"
#include <ArduinoHttpClient.h>
#include "ArduinoJson.h"

class History: public Subscriber
{
  private:
    HttpClient *client;
    String token;
    Logger *logger;
      
  public:
    History(HttpClient *client, String token, Logger *logger);
    
    void handle(char type, State *state);
};

#endif
