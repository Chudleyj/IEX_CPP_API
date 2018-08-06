# IEX_CPP_API
Unofficial C++ Lib for the IEXtrading API 

For the OFFICIAL API and its docs and  all credit to the data pulled by this program go to: https://iextrading.com/developer/docs/

This lib will allow for easier use of IEXtrading GET requests in C++ through the use of prebuilt functions. 

As it stands currently, the dependancies used in this lib will need to be manually installed:

Libcurl: https://curl.haxx.se/docs/install.html

Jsoncpp: https://github.com/open-source-parsers/jsoncpp

**NOTE:**

The code currently in "int main()" is simply test cases as this is still in dev. The final product would not use an "int main()", it just shows examples of how to use each function currently in the lib. 

**Using the lib:**
Formal docs to be added when this project gets closer to done, however some basic examples plus the offical docs should make this easy to use. See the int main() code for examples on using each currently supported function. Each function returns a JSON data type. This lib uses the Jsoncpp API for its' JSON data types. See the Jsoncpp docs linked above for info on how to use the JSON objects. 

**Ex: 

**_To Do:_**

**Stocks:**
  ~~Batch Requests~~ (Half implemented, still needs parameteres)
  ~~Book~~
  ~~Chart~~ (Completed all range options, some additional params not in yet)
  ~~Company~~
  ~~Delayed Quote~~
  ~~Dividends~~
  ~~Earnings~~
  ~~Effective Spread~~
  ~~Financials~~
  ~~Historical Prices~~ (Done VIA "Chart" as the official API does.)
  IEX Regulation SHO Threshold Securities List (Can't get this to return anything, unsure if not supported or me being dumb, will revisit later)
  IEX Short Interest List(Can't get this to return anything, unsure if not supported or me being dumb, will revisit later)
  ~~Key Stats~~
  ~~Largest Trades~~
  ~~List~~
  ~~Logo~~
  News
  OHLC
  Open/Close
  Peers
  Previous
  Price
  Quote
  Relevant
  Splits
  Time Series
  Volume by Venue

**Reference Data:**
  Symbols
  IEX Corporate Actions
  IEX Dividends
  IEX Next Day Ex Date
  IEX Listed Symbol Directory 

**IEX Market Data:**
  TOPS
  Last
  HIST
  DEEP
  Book
  Trades
  System Event
  Trading Status
  Operational Hault Status
  Short Sale Price Test Status
  Security Event
  Trade Break
  Auction 
  Official Price
  
**IEX Stats:**
  Intraday
  Recent
  Records
  Historical Summary
  Historical Daily
  
**Markets**
  Market
