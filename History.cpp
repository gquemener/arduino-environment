#include "History.h"
#include "StateStore.h"

History::History(HttpClient *client, String token, Logger *logger)
{
  this->client = client;
  this->token = token;
  this->logger = logger;
}

void History::handle(char type, State *state)
{
  if (type != ATMOS_PRESSURE_WAS_MEASURED) {
    return;
  }
  
  if (state->atmosPressure == "830.76") {
    return;
  }
  
  const size_t capacity = 2 * JSON_OBJECT_SIZE(2);
  DynamicJsonDocument doc(capacity);
  doc["name"] = "AddWeatherReport";
  JsonObject payload = doc.createNestedObject("payload");
  payload["pressure"] = state->atmosPressure;
  payload["date"] = state->datetime;
  
  String body = "";
  serializeJson(doc, body);
  
  String authorizationHeader = "Bearer ";
  authorizationHeader.concat(this->token);
  
  this->logger->info(body.c_str());
  
  this->client->beginRequest();
  this->client->post("/commands");
  this->client->sendHeader("Authorization", authorizationHeader);
  this->client->sendHeader("Content-Type", "application/json");
  this->client->sendHeader("Content-Length", body.length());
  this->client->beginBody();
  this->client->print(body);
  this->client->endRequest();
  
  int statusCode = this->client->responseStatusCode();
  
  this->logger->info(String("Response status code: " + String(statusCode)));
}
