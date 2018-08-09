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
    Json::Value batch(std::string symbol);
    Json::Value book(std::string symbol);
    Json::Value chart(std::string symbol);
    Json::Value chartRange(std::string symbol, std::string range);
    Json::Value chartDate(std::string symbol, std::string date);
    Json::Value chartDynamic(std::string symbol);
    Json::Value company(std::string symbol);
    Json::Value delayedQuote(std::string symbol);
    Json::Value dividends(std::string symbol, std::string range);
    Json::Value earnings(std::string symbol);
    Json::Value effectiveSpread(std::string symbol);
    Json::Value financials(std::string symbol);
    Json::Value stats(std::string symbol);
    Json::Value largestTrades(std::string symbol);
    Json::Value list(std::string listType);
    Json::Value logo(std::string symbol);
    Json::Value news(std::string symbol, int last = 0);
    Json::Value OHLC(std::string symbol);
    Json::Value peers(std::string symbol);
    Json::Value previous(std::string symbol);
  }
}

#endif
