#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

struct HTTPResponse {
    long statusCode;
    std::string body;
};

class HTTPClient {
public:
    HTTPResponse get(const std::string& url);
};

#endif // HTTP_CLIENT_H
