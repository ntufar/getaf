#include "gtest/gtest.h"
#include "Framework/HTTPClient.h" // This file doesn't exist yet

TEST(HTTPClientTest, CanPerformGetRequest) {
    HTTPClient client;
    HTTPResponse response = client.get("https://www.google.com");
    ASSERT_EQ(response.statusCode, 200);
    ASSERT_FALSE(response.body.empty());
}

TEST(HTTPClientTest, CanHandleNotFound) {
    HTTPClient client;
    // Use a URL that is expected to return a 404 Not Found status
    HTTPResponse response = client.get("https://httpbin.org/status/404");
    ASSERT_EQ(response.statusCode, 404);
    // The body might not be empty, depending on the 404 page content
}
