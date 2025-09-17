#include "HTTPClient.h"
#include <cpr/cpr.h>

HTTPResponse HTTPClient::get(const std::string& url) {
    cpr::Response r = cpr::Get(cpr::Url{url});
    return {r.status_code, r.text};
}
