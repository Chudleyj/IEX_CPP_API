#ifndef IEX_h
#define IEX_h

#include <json/json.h>
#include <curl/curl.h>
#include <string>
#include <iostream>

#define IEX_ENDPOINT "https://api.iextrading.com/1.0"

namespace IEX{
  void sendGetRequest(Json::Value &data, std::string url);
  namespace stocks{
    Json::Value batchRequest(std::string symbol);
    Json::Value bookRequest(std::string symbol);
  }
}

#endif
