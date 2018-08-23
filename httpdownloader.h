#ifndef HTTPDOWNLOADER_HPP
#define HTTPDOWNLOADER_HPP

#include <string>
#include <curl/curl.h>

class HTTPDownloader {
public:
    HTTPDownloader();
    ~HTTPDownloader();
    std::string download(const std::string url);
private:
    CURL *curl;
    CURLcode res;
};
#endif
