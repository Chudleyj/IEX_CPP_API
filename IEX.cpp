#include "IEX.h"

int main(){
//  curl_global_init(CURL_GLOBAL_DEFAULT); //TODO auto execute somewhere?
  Json::Value test;
  test = IEX::stocks::batchRequest("aapl");
  test = IEX::stocks::bookRequest("aapl");
  std:: cout << test << std::endl << "DONE";
  //curl_global_cleanup(); //TODO auto execute somewhere?
}

std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out){
    const std::size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}

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

Json::Value IEX::stocks::batchRequest(std::string symbol){
  Json::Value jsonData;
  Json::Value jsonDataa;
  std::string url(IEX_ENDPOINT);
  url+="/stock/"+symbol+"/batch";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}

//TODO : add parameters from API
Json::Value IEX::stocks::bookRequest(std::string symbol){
  Json::Value jsonData;
  Json::Value jsonDataa;
  std::string url(IEX_ENDPOINT);
  url+="/stock/"+symbol+"/book";
  IEX::sendGetRequest(jsonData, url);
  return jsonData;
}
