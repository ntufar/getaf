#include "gtest/gtest.h"
#include "Framework/HTTPClient.h" // This file doesn't exist yet

TEST(HTTPClientTest, CanPerformGetRequest) {
    HTTPClient client;
    HTTPResponse response = client.get("https://www.google.com");
    ASSERT_EQ(response.statusCode, 200);
    ASSERT_FALSE(response.body.empty());
}
