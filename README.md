# IEX_CPP_API
Unofficial C++ Lib for the IEXtrading API 

For the OFFICIAL API and its docs and  all credit to the data pulled by this program go to: https://iextrading.com/developer/docs/

This lib will allow for easier use of IEXtrading GET requests in C++ through the use of prebuilt functions. 

As it stands currently, the dependancies used in this lib will need to be manually installed:

Libcurl: https://curl.haxx.se/docs/install.html

Jsoncpp: https://github.com/open-source-parsers/jsoncpp

**_Why use this lib over official API?_**

   **C++ code with the official API:**
    
    namespace
    {
        std::size_t callback(
        const char* in,
        std::size_t size,
        std::size_t num,
        std::string* out)
        {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
        }
    }

    Json::Value acquireJSONofAAPLchart{
        const std::string url("https://api.iextrading.com/1.0/stock/aapl/chart");
        
        CURL* curl = curl_easy_init();
        
        // Set remote URL.
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        // Don't bother trying IPv6, which would increase DNS resolution time.
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
        
        // Don't wait forever, time out after 10 seconds.
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        
        // Follow HTTP redirects if necessary.
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        
        // Response information.
        int httpCode(0);
        std::unique_ptr<std::string> httpData(new std::string());
        
        // Hook up data handling function.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        
        // Hook up data container (will be passed as the last parameter to the
        // callback handling function).  Can be any pointer type, since it will
        // internally be passed as a void pointer.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
        
        // Run our HTTP GET command, capture the HTTP response code, and clean up.
        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);
        
        JSONdata parsedData;
        if (httpCode == 200)
        {
        std::cout << "\nGot successful response from " << url << std::endl;
        
        // Response looks good - done using Curl now.  
        Json::Reader jsonReader;
        Json::Value jsonData;
        jsonReader.parse(*httpData, jsonData); //TODO error handle
        
        return jsonValue;
        
        
    }
   
   **C++ code with IEX_CPP_API:**
   
      IEX::stocks::chart("aapl");


**NOTE:**

The code currently in "int main()" is simply test cases as this is still in dev. The final product would not use an "int main()", it just shows examples of how to use each function currently in the lib. 

**Using the lib:**

Formal docs to be added when this project gets closer to done, however some basic examples plus the offical docs should make this easy to use. See the int main() code for examples on using each currently supported function. Each function returns a JSON data type. This lib uses the Jsoncpp API for its' JSON data types. See the Jsoncpp docs linked above for info on how to use the JSON objects. 



**_To Do:_**

**Stocks:**
 - ~~Batch Requests~~ (Half implemented, still needs parameteres)
 - ~~Book~~
 - ~~Chart~~ (Completed all range options, some additional params not in yet)
 - ~~Company~~
 - ~~Crypto~~
 - ~~Delayed Quote~~
 - ~~Dividends~~
 - ~~Earnings~~
 - ~~Earnings Today~~
 - ~~Effective Spread~~
 - ~~Financials~~
 - ~~Historical Prices~~ (Done VIA "Chart" as the official API does.)
 - ~~Upcoming IPOS~~
 - ~~Today's IPOS~~
 - IEX Regulation SHO Threshold Securities List (Can't get this to return anything, unsure if not supported or me being dumb, will revisit later)
 - IEX Short Interest List(Can't get this to return anything, unsure if not supported or me being dumb, will revisit later)
 - ~~Key Stats~~
 - ~~Largest Trades~~
 - ~~List~~
 - ~~Logo~~
 - ~~News~~
 - ~~OHLC~~
 - ~~Open/Close~~ (OHLC function per offical API docs)
 - ~~Peers~~
 - ~~Previous~~
 - ~~Price~~
 - ~~Quote~~
 - ~~Relevant~~
 - ~~Splits~~
 - ~~Time Series~~
 - ~~Volume by Venue~~

**Reference Data:**
 - ~~Symbols~~
 - ~~IEX Corporate Actions~~
 - ~~IEX Dividends~~
 - ~~IEX Next Day Ex Date~~
 - ~~IEX Listed Symbol Directory~~

**IEX Market Data:**
 - TOPS
 - Last
 - HIST
 - DEEP
 - Book
 - Trades
 - System Event
 - Trading Status
 - Operational Hault Status
 - Short Sale Price Test Status
 - Security Event
 - Trade Break
 - Auction 
 - Official Price
  
**IEX Stats:**
 - ~~Intraday~~
 - ~~Recent~~
 - ~~Records~~
 - ~~Historical Summary~~
 - ~~Historical Daily~~
  
**Markets**
 - ~~Market~~
