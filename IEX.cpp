/* UNOFFICIAL IEX TRADING API for C++
BY: Justin Chudley
https://github.com/Chudleyj/
OFFICIAL API: https://iextrading.com/developer/docs/
Refer to the official docs to understand the return of each function.
GET examples and JSON examples commented above each function are from the offical API.
ALL credit for those examples belongs to IEX.

“Data provided for free by IEX (https://iextrading.com/developer/).
View IEX’s Terms of Use (https://iextrading.com/api-exhibit-a/).”

*/
//TODO CHECK ALL SYMBOLS FOR VALID SYMBOL
#include "IEX.h"

int main(){
//  curl_global_init(CURL_GLOBAL_DEFAULT); //TODO auto execute somewhere?
  Json::Value test;
  test = IEX::stocks::batch("aapl");
  test = IEX::stocks::book("aapl");
  test = IEX::stocks::chart("aapl");
  test = IEX::stocks::chartRange("aapl", "1m");
  test = IEX::stocks::chartDate("aapl", "20180801");
  test = IEX::stocks::chartDynamic("aapl");
  test = IEX::stocks::company("aapl");
  test = IEX::stocks::delayedQuote("aapl");
  test = IEX::stocks::dividends("aapl", "5y");
  test = IEX::stocks::earnings("aapl");
  test = IEX::stocks::effectiveSpread("aapl");
  test =  IEX::stocks::financials("aapl");
  test =  IEX::stocks::stats("aapl");
  test =  IEX::stocks::largestTrades("aapl");
  test =  IEX::stocks::list("gainers");
  test =  IEX::stocks::logo("aapl");
  test =  IEX::stocks::news("market", 5);
  test =  IEX::stocks::news("market");
  test =  IEX::stocks::news("aapl");
  test =  IEX::stocks::OHLC("aapl");
  test =  IEX::stocks::OHLC("market");
  test =  IEX::stocks::peers("aapl");
  test =  IEX::stocks::previous("aapl");
  test =  IEX::stocks::previous("market");
  test =  IEX::stocks::price("aapl");
  test =  IEX::stocks::quote("aapl");
  test =  IEX::stocks::quote("aapl", true);
  test =  IEX::stocks::relevant("aapl");
  test =  IEX::stocks::sectorPerformance();
  test =  IEX::stocks::relevant("aapl");
  test =  IEX::stocks::splits("aapl","5y");
  test =  IEX::stocks::timeSeries("aapl");
  test =  IEX::stocks::VolumeByVenue("aapl");
  std:: cout << test << std::endl << "DONE";
  //curl_global_cleanup(); //TODO auto execute somewhere?
}

//Callback function used by sendGetRequest to get the result from curl.
std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out){
    const std::size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}

//Use LIBCURL to send the GET requests
void IEX::sendGetRequest(Json::Value &jsonData, const std::string url){
  CURL* curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  long int httpCode(0); //Having this as a normal int will cause a segmentation fault for some requests being too large.
  std::unique_ptr<std::string> httpData(new std::string());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
  curl_easy_perform(curl);
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
  curl_easy_cleanup(curl);

  Json::Reader jsonReader;
  jsonReader.parse(*httpData, jsonData); //TODO error handle
}

Json::Value IEX::stocks::batch(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url+="/stock/"+symbol+"/batch";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/* GET /stock/{symbol}/book
{
  "quote": {...},
  "bids": [...],
  "asks": [...],
  "trades": [...],
  "systemEvent": {...},
}
*/
Json::Value IEX::stocks::book(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url+="/stock/"+symbol+"/book";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*GET /stock/{symbol}/chart/{range}
// .../1d

[
    {
        "date": "20171215"
        "minute": "09:30",
        "label": "09:30 AM",
        "high": 143.98,
        "low": 143.775,
        "average": 143.889,
        "volume": 3070,
        "notional": 441740.275,
        "numberOfTrades": 20,
        "marktHigh": 143.98,
        "marketLow": 143.775,
        "marketAverage": 143.889,
        "marketVolume": 3070,
        "marketNotional": 441740.275,
        "marketNumberOfTrades": 20,
        "open": 143.98,
        "close": 143.775,
        "marktOpen": 143.98,
        "marketClose": 143.775,
        "changeOverTime": -0.0039,
        "marketChangeOverTime": -0.004
    } // , { ... }
]
*/
Json::Value IEX::stocks::chart(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url+="/stock/"+symbol+"/chart";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

//Same as chart function, except it takes a range in.
//Range must be: 5y, 2y, 1y, ytd, 6m, 3m, 1m, 1d
Json::Value IEX::stocks::chartRange(std::string symbol, std::string range){
  Json::Value jsonData;
  if(range == "5y" || range == "2y" || range == "1y" || range == "ytd" || range == "6m" || range == "3m" || range == "1m" || range == "1d"){
    std::string url(IEX_ENDPOINT);
    url+="/stock/"+symbol+"/chart/"+range;
    IEX::sendGetRequest(jsonData, url);
  }
  else{
    std::cout << std::endl << "Incorrect 'range' input in function chartRange. Exiting." << std::endl;
    exit(1);
  }
  return jsonData;
}

//Specific date entry for chart, YYYYMMDD format, 30 trailing calander days
Json::Value IEX::stocks::chartDate(std::string symbol, std::string date){
  Json::Value jsonData;
  if(date.size() == 8){
    std::string url(IEX_ENDPOINT);
    url+="/stock/"+symbol+"/chart/date/"+date;
    IEX::sendGetRequest(jsonData, url);
  }
  else{
    std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
    exit(1);
  }
  return jsonData;
}

//Dynamic chart. See offical API docs.
Json::Value IEX::stocks::chartDynamic(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/chart/dynamic";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*
GET /stock/{symbol}/company
{
  "symbol": "AAPL",
  "companyName": "Apple Inc.",
  "exchange": "Nasdaq Global Select",
  "industry": "Computer Hardware",
  "website": "http://www.apple.com",
  "description": "Apple Inc is an American multinational technology company. It designs, manufactures, and markets mobile communication and media devices, personal computers, and portable digital music players.",
  "CEO": "Timothy D. Cook",
  "issueType": "cs",
  "sector": "Technology",
}*/
Json::Value IEX::stocks::company(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/company";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*
GET /stock/{symbol}/delayed-quote
{
  "symbol": "AAPL",
  "delayedPrice": 143.08,
  "delayedSize": 200,
  "delayedPriceTime": 1498762739791,
  "processedTime": 1498763640156
}*/
Json::Value IEX::stocks::delayedQuote(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/delayed-quote";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*
GET /stock/{symbol}/dividends/{range}
[
    {
        "exDate": "2017-08-10",
        "paymentDate": "2017-08-17",
        "recordDate": "2017-08-14",
        "declaredDate": "2017-08-01",
        "amount": 0.63,
        "type": "Dividend income",
        "qualified": "Q"
    } // , { ... }
]
REQUIRES a range: 5y,2y,1y,ytd,6m,3m,1m */
Json::Value IEX::stocks::dividends(std::string symbol, std::string range){
  Json::Value jsonData;
  if(range == "5y" || range == "2y" || range == "1y" || range == "ytd" || range == "6m" || range == "3m" || range == "1m"){
    std::string url(IEX_ENDPOINT);
    url+="/stock/"+symbol+"/dividends/"+range;
    IEX::sendGetRequest(jsonData, url);
  }
  else{
    std::cout << std::endl << "Incorrect 'range' input in function dividends. Exiting." << std::endl;
    exit(1);
  }
  return jsonData;
}

/*GET /stock/{symbol}/earnings
{
  "symbol": "AAPL",
  "earnings": [
    {
      "actualEPS": 2.1,
      "consensusEPS": 2.02,
      "estimatedEPS": 2.02,
      "announceTime": "AMC",
      "numberOfEstimates": 14,
      "EPSSurpriseDollar": 0.08,
      "EPSReportDate": "2017-05-02",
      "fiscalPeriod": "Q2 2017",
      "fiscalEndDate": "2017-03-31",
      "yearAgo": 1.67,
      "yearAgoChangePercent": .30,
      "estimatedChangePercent": .28,
      "symbolId": 11
    },
    {
      "actualEPS": 3.36,
      "consensusEPS": 3.22,
      "estimatedEPS": 3.22,
      "announceTime": "AMC",
      "numberOfEstimates": 15,
      "EPSSurpriseDollar": 0.14,
      "EPSReportDate": "2017-01-31",
      "fiscalPeriod": "Q1 2017",
      "fiscalEndDate": "2016-12-31",
      "yearAgo": 1.67,
      "yearAgoChangePercent": .30,
      "estimatedChangePercent": .28,
      "symbolId": 11
    },
  ]
}*/
Json::Value IEX::stocks::earnings(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/earnings";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*GET /stock/{symbol}/effective-spread
[
  {
    "volume": 4899,
    "venue": "XCHI",
    "venueName": "CHX",
    "effectiveSpread": 0.02253725,
    "effectiveQuoted": 0.9539362,
    "priceImprovement": 0.0008471116999999999
  },
  {
    "volume": 9806133,
    "venue": "XBOS",
    "venueName": "NASDAQ BX",
    "effectiveSpread": 0.0127343,
    "effectiveQuoted": 0.9313967,
    "priceImprovement": 0.0007373158
  },
  {
    "volume": 6102991,
    "venue": "IEXG",
    "venueName": "IEX",
    "effectiveSpread": 0.005881705,
    "effectiveQuoted": 0.4532043,
    "priceImprovement": 0.003949427
  }
]*/
Json::Value IEX::stocks::effectiveSpread(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/effective-spread";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*GET /stock/{symbol}/financials
The above example will return JSON with the following keys

{
  "symbol": "AAPL",
  "financials": [
    {
      "reportDate": "2017-03-31",
      "grossProfit": 20591000000,
      "costOfRevenue": 32305000000,
      "operatingRevenue": 52896000000,
      "totalRevenue": 52896000000,
      "operatingIncome": 14097000000,
      "netIncome": 11029000000,
      "researchAndDevelopment": 2776000000,
      "operatingExpense": 6494000000,
      "currentAssets": 101990000000,
      "totalAssets": 334532000000,
      "totalLiabilities": 200450000000,
      "currentCash": 15157000000,
      "currentDebt": 13991000000,
      "totalCash": 67101000000,
      "totalDebt": 98522000000,
      "shareholderEquity": 134082000000,
      "cashChange": -1214000000,
      "cashFlow": 12523000000,
      "operatingGainsLosses": null
    } // , { ... }
  ]
}*/
Json::Value IEX::stocks::financials(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/financials";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*GET /stock/{symbol}/stats
{
  "companyName": "Apple Inc.",
  "marketcap": 760334287200,
  "beta": 1.295227,
  "week52high": 156.65,
  "week52low": 93.63,
  "week52change": 58.801903,
  "shortInterest": 55544287,
  "shortDate": "2017-06-15",
  "dividendRate": 2.52,
  "dividendYield": 1.7280395,
  "exDividendDate": "2017-05-11 00:00:00.0",
  "latestEPS": 8.29,
  "latestEPSDate": "2016-09-30",
  "sharesOutstanding": 5213840000,
  "float": 5203997571,
  "returnOnEquity": 0.08772939519857577,
  "consensusEPS": 3.22,
  "numberOfEstimates": 15,
  "symbol": "AAPL",
  "EBITDA": 73828000000,
  "revenue": 220457000000,
  "grossProfit": 84686000000,
  "cash": 256464000000,
  "debt": 358038000000,
  "ttmEPS": 8.55,
  "revenuePerShare": 42.2830389885382,
  "revenuePerEmployee": 1900491.3793103448,
  "peRatioHigh": 25.5,
  "peRatioLow": 8.7,
  "EPSSurpriseDollar": null,
  "EPSSurprisePercent": 3.9604,
  "returnOnAssets": 14.15,
  "returnOnCapital": null,
  "profitMargin": 20.73,
  "priceToSales": 3.6668503,
  "priceToBook": 6.19,
  "day200MovingAvg": 140.60541,
  "day50MovingAvg": 156.49678,
  "institutionPercent": 32.1,
  "insiderPercent": null,
  "shortRatio": 1.6915414,
  "year5ChangePercent": 0.5902546932200027,
  "year2ChangePercent": 0.3777449874142869,
  "year1ChangePercent": 0.39751716851558366,
  "ytdChangePercent": 0.36659492036160124,
  "month6ChangePercent": 0.12208398133748043,
  "month3ChangePercent": 0.08466584665846649,
  "month1ChangePercent": 0.009668596145283263,
  "day5ChangePercent": -0.005762605699968781
}*/
Json::Value IEX::stocks::stats(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/stats";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*GET /stock/{symbol}/largest-trades
[
  {
    "price": 186.39,
    "size": 10000,
    "time": 1527090690175,
    "timeLabel": "11:51:30",
    "venue": "EDGX",
    "venueName": "Cboe EDGX"
  },
  ...
] */
Json::Value IEX::stocks::largestTrades(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/largest-trades";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*GET /stock/market/list
[
  {
      "symbol": "AAPL",
      "companyName": "Apple Inc.",
      "primaryExchange": "Nasdaq Global Select",
      "sector": "Technology",
      "calculationPrice": "tops",
      "latestPrice": 158.73,
      "latestSource": "Previous close",
      "latestTime": "September 19, 2017",
      "latestUpdate": 1505779200000,
      "latestVolume": 20567140,
      "iexRealtimePrice": 158.71,
      "iexRealtimeSize": 100,
      "iexLastUpdated": 1505851198059,
      "delayedPrice": 158.71,
      "delayedPriceTime": 1505854782437,
      "previousClose": 158.73,
      "change": -1.67,
      "changePercent": -0.01158,
      "iexMarketPercent": 0.00948,
      "iexVolume": 82451,
      "avgTotalVolume": 29623234,
      "iexBidPrice": 153.01,
      "iexBidSize": 100,
      "iexAskPrice": 158.66,
      "iexAskSize": 100,
      "marketCap": 751627174400,
      "peRatio": 16.86,
      "week52High": 159.65,
      "week52Low": 93.63,
      "ytdChange": 0.3665,
  } // , { ... }
]
LISTTYPE REQUIRED: mostactive, gainers, losers, iexvolume, or iexmarketpercent*/
Json::Value IEX::stocks::list(std::string listType){
  Json::Value jsonData;
  if(listType == "mostactive" || listType == "gainers" || listType == "losers" || listType == "iexvolume" || listType == "iexmarketpercent"){
    std::string url(IEX_ENDPOINT);
    url+="/stock/market/list/"+listType;
    IEX::sendGetRequest(jsonData, url);
  }
  else{
    std::cout << std::endl << "Incorrect 'listType' input in function list. Exiting." << std::endl;
    exit(1);
  }
  return jsonData;
}

/*
GET /stock/{symbol}/logo
{
  "url": "https://storage.googleapis.com/iex/api/logos/AAPL.png"
}*/
Json::Value IEX::stocks::logo(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/logo";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*
GET /stock/{symbol}/news/last/{last}

[
 {
   "datetime": "2017-06-29T13:14:22-04:00",
   "headline": "Voice Search Technology Creates A New Paradigm For Marketers",
   "source": "Benzinga via QuoteMedia",
   "url": "https://api.iextrading.com/1.0/stock/aapl/article/8348646549980454",
   "summary": "<p>Voice search is likely to grow by leap and bounds, with technological advancements leading to better adoption and fueling the growth cycle, according to Lindsay Boyajian, <a href=\"http://loupventures.com/how-the-future-of-voice-search-affects-marketers-today/\">a guest contributor at Loup Ventu...",
   "related": "AAPL,AMZN,GOOG,GOOGL,MSFT",
   "image": "https://api.iextrading.com/1.0/stock/aapl/news-image/7594023985414148"
 }
]
EITHER PASS A SYMBOL OR A SYMOL AND A NUMBER FOR LAST X ARTICLES (SEE OFFICAL DOCS)
OR PASS MARKET AS SYMBOL FOR MARKETWIDE NEWS*/
Json::Value IEX::stocks::news(std::string symbol, int last){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  last == 0 ? url += "/stock/"+symbol+"/news" : url += "/stock/"+symbol+"/news/last/"+std::to_string(last);
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*GET /stock/{symbol}/ohlc
{
  "open": {
    "price": 154,
    "time": 1506605400394
  },
  "close": {
    "price": 153.28,
    "time": 1506605400394
  },
  "high": 154.80,
  "low": 153.25
}
Can take in a specific symbol OR market as symbol */
Json::Value IEX::stocks::OHLC(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/ohlc";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*
GET /stock/{symbol}/peers
[
    "MSFT",
    "NOK",
    "IBM",
    "BBRY",
    "HPQ",
    "GOOGL",
    "XLK"
] */
Json::Value IEX::stocks::peers(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/peers";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*
GET /stock/{symbol}/previous
{
  "symbol": "AAPL",
  "date": "2017-09-19",
  "open": 159.51,
  "high": 159.77,
  "low": 158.44,
  "close": 158.73,
  "volume": 20810632,
  "unadjustedVolume": 20810632,
  "change": 0.06,
  "changePercent": 0.038,
  "vwap": 158.9944
}
Takes symbol or market as symbol */
Json::Value IEX::stocks::previous(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/previous";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

// GET /stock/{symbol}/price
Json::Value IEX::stocks::price(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/price";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*
GET /stock/{symbol}/quote
{
  "symbol": "AAPL",
  "companyName": "Apple Inc.",
  "primaryExchange": "Nasdaq Global Select",
  "sector": "Technology",
  "calculationPrice": "tops",
  "open": 154,
  "openTime": 1506605400394,
  "close": 153.28,
  "closeTime": 1506605400394,
  "high": 154.80,
  "low": 153.25,
  "latestPrice": 158.73,
  "latestSource": "Previous close",
  "latestTime": "September 19, 2017",
  "latestUpdate": 1505779200000,
  "latestVolume": 20567140,
  "iexRealtimePrice": 158.71,
  "iexRealtimeSize": 100,
  "iexLastUpdated": 1505851198059,
  "delayedPrice": 158.71,
  "delayedPriceTime": 1505854782437,
  "extendedPrice": 159.21,
  "extendedChange": -1.68,
  "extendedChangePercent": -0.0125,
  "extendedPriceTime": 1527082200361,
  "previousClose": 158.73,
  "change": -1.67,
  "changePercent": -0.01158,
  "iexMarketPercent": 0.00948,
  "iexVolume": 82451,
  "avgTotalVolume": 29623234,
  "iexBidPrice": 153.01,
  "iexBidSize": 100,
  "iexAskPrice": 158.66,
  "iexAskSize": 100,
  "marketCap": 751627174400,
  "peRatio": 16.86,
  "week52High": 159.65,
  "week52Low": 93.63,
  "ytdChange": 0.3665,
}
OPTIONAL VALUE TO DISPLAY PERCENT, SEE OFFICAL API */
Json::Value IEX::stocks::quote(std::string symbol, bool displayPercent){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);

  displayPercent ? url += "/stock/"+symbol+"/quote?displayPercent=true" : url += "/stock/"+symbol+"/quote";



  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*
GET /stock/{symbol}/relevant
{
  "peers": true,
  "symbols": [
      "MSFT",
      "NOK",
      "IBM",
      "BBRY",
      "HPQ",
      "GOOGL",
      "XLK"
  ]
}*/
Json::Value IEX::stocks::relevant(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/relevant";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*
GET /stock/market/sector-performance
[
  {
    "type": "sector",
    "name": "Industrials",
    "performance": 0.00711,
    "lastUpdated": 1533672000437
  },
  ...
]*/
Json::Value IEX::stocks::sectorPerformance(){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/market/sector-performance";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*
GET /stock/{symbol}/splits/{range}
[
    {
        "exDate": "2017-08-10",
        "declaredDate": "2017-08-01",
        "recordDate": "2017-08-14",
        "paymentDate": "2017-08-17",
        "ratio": 0.142857,
        "toFactor": 7,
        "forFactor": 1
    } // , { ... }
]*/
Json::Value IEX::stocks::splits(std::string symbol, std::string range){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);

  if(range == "5y" || range == "2y" || range == "1y" || range == "ytd" || range == "6m" || range == "3m" || range == "1m" || range == "1d"){
    url += "/stock/"+symbol+"/splits/"+range;
    IEX::sendGetRequest(jsonData, url);
  }
  else{
    std::cout << std::endl << "Incorrect 'range' input in function chartRange. Exiting." << std::endl;
    exit(1);
  }

  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

//GET /stock/{symbol}/time-series
Json::Value IEX::stocks::timeSeries(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/time-series";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

/*
GET /stock/{symbol}/delayed-quote
[
  {
    "volume": 0,
    "venue": "XNYS",
    "venueName": "NYSE",
    "marketPercent": 0,
    "avgMarketPercent": 0,
    "date": "N/A"
  },
  {
    "volume": 21655,
    "venue": "XASE",
    "venueName": "NYSE American",
    "date": "2017-09-19",
    "marketPercent": 0.0010540470343969304,
    "avgMarketPercent": 0.0021596513337820305
  },
  {
    "volume": 164676,
    "venue": "EDGA",
    "venueName": "EDGA",
    "date": "2017-09-19",
    "marketPercent": 0.008015527565751508,
    "avgMarketPercent": 0.007070162857518009
  },
  {
    "volume": 253600,
    "venue": "XCHI",
    "venueName": "CHX",
    "date": "2017-09-19",
    "marketPercent": 0.01234386182974193,
    "avgMarketPercent": 0.019123040706393757
  },
  {
    "volume": 289791,
    "venue": "IEXG",
    "venueName": "IEX",
    "date": "2017-09-19",
    "marketPercent": 0.014105441890783691,
    "avgMarketPercent": 0.01080806673166022
  },
  {
    "volume": 311580,
    "venue": "XPHL",
    "venueName": "NASDAQ PSX",
    "date": "2017-09-19",
    "marketPercent": 0.0151660113127405,
    "avgMarketPercent": 0.010991446666811688
  },
  {
    "volume": 479457,
    "venue": "XBOS",
    "venueName": "NASDAQ BX",
    "date": "2017-09-19",
    "marketPercent": 0.02333734606191868,
    "avgMarketPercent": 0.016846380315025656
  },
  {
    "volume": 501842,
    "venue": "BATY",
    "venueName": "BATS BYX",
    "date": "2017-09-19",
    "marketPercent": 0.024426925506156744,
    "avgMarketPercent": 0.020187355701732888
  },
  {
    "volume": 1242757,
    "venue": "BATS",
    "venueName": "BATS BZX",
    "date": "2017-09-19",
    "marketPercent": 0.06049061788621685,
    "avgMarketPercent": 0.060993172098918684
  },
  {
    "volume": 1865376,
    "venue": "ARCX",
    "venueName": "NYSE Arca",
    "date": "2017-09-19",
    "marketPercent": 0.09079630758878819,
    "avgMarketPercent": 0.07692002795005641
  },
  {
    "volume": 1951116,
    "venue": "EDGX",
    "venueName": "EDGX",
    "date": "2017-09-19",
    "marketPercent": 0.09496966213643043,
    "avgMarketPercent": 0.09297590135910822
  },
  {
    "volume": 5882545,
    "venue": "XNGS",
    "venueName": "NASDAQ",
    "date": "2017-09-19",
    "marketPercent": 0.2863301367793346,
    "avgMarketPercent": 0.27436519408402665
  },
  {
    "volume": 7580229,
    "venue": "TRF",
    "venueName": "Off Exchange",
    "date": "2017-09-19",
    "marketPercent": 0.36896411440773996,
    "avgMarketPercent": 0.40847022134435956
  }
]*/
Json::Value IEX::stocks::VolumeByVenue(std::string symbol){
  Json::Value jsonData;
  std::string url(IEX_ENDPOINT);
  url += "/stock/"+symbol+"/volume-by-venue";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}
