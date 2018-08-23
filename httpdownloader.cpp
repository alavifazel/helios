#include "httpdownloader.h"
#include <stdexcept>
#include <iostream>
using namespace std;
HTTPDownloader::HTTPDownloader()
{
    curl = curl_easy_init();
}

HTTPDownloader::~HTTPDownloader()
{
    curl_easy_cleanup(curl);
}

std::string data;
size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up) {
    for (int c = 0; c<size*nmemb; c++)
    {
        data.push_back(buf[c]);
    }

    return size*nmemb;
}

std::string HTTPDownloader::download(const std::string url)
{

    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

      res = curl_easy_perform(curl);
      if(res != CURLE_OK)
      {
        throw std::runtime_error(curl_easy_strerror(res));
      }
    }
    return data;
}
