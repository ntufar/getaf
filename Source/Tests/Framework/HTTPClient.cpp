#include "gtest/gtest.h"
#include "Framework/HTTPClient.h"
#include <chrono>
#include <thread>
#include <string>

// Mock HTTP Server for testing
class MockHTTPServer {
public:
    static bool shouldTimeout;
    static bool shouldFailNetwork;
    static int responseStatus;
    static std::string responseBody;
    
    static void reset() {
        shouldTimeout = false;
        shouldFailNetwork = false;
        responseStatus = 200;
        responseBody = "{}";
    }
    
    static std::string getTestUrl() {
        return "http://localhost:8080/test";
    }
};

bool MockHTTPServer::shouldTimeout = false;
bool MockHTTPServer::shouldFailNetwork = false;
int MockHTTPServer::responseStatus = 200;
std::string MockHTTPServer::responseBody = "{}";

class HTTPClientTest : public ::testing::Test {
protected:
    void SetUp() override {
        MockHTTPServer::reset();
    }
    
    void TearDown() override {
        MockHTTPServer::reset();
    }
};

// Basic HTTP Request Tests
TEST_F(HTTPClientTest, SuccessfulGetRequest) {
    HTTPClient client;
    MockHTTPServer::responseBody = "{\"status\": \"success\"}";
    
    HTTPResponse response = client.get(MockHTTPServer::getTestUrl());
    ASSERT_EQ(response.statusCode, 200);
    ASSERT_EQ(response.body, "{\"status\": \"success\"}");
}

TEST_F(HTTPClientTest, NotFoundResponse) {
    HTTPClient client;
    MockHTTPServer::responseStatus = 404;
    MockHTTPServer::responseBody = "Not Found";
    
    HTTPResponse response = client.get(MockHTTPServer::getTestUrl() + "/nonexistent");
    ASSERT_EQ(response.statusCode, 404);
    ASSERT_EQ(response.body, "Not Found");
}

TEST_F(HTTPClientTest, ServerError) {
    HTTPClient client;
    MockHTTPServer::responseStatus = 500;
    MockHTTPServer::responseBody = "Internal Server Error";
    
    HTTPResponse response = client.get(MockHTTPServer::getTestUrl() + "/error");
    ASSERT_EQ(response.statusCode, 500);
    ASSERT_EQ(response.body, "Internal Server Error");
}

// Error Handling Tests
TEST_F(HTTPClientTest, NetworkFailure) {
    HTTPClient client;
    MockHTTPServer::shouldFailNetwork = true;
    
    HTTPResponse response = client.get(MockHTTPServer::getTestUrl());
    ASSERT_EQ(response.statusCode, -1);  // Expected error code for network failure
    ASSERT_TRUE(response.body.empty());
}

TEST_F(HTTPClientTest, Timeout) {
    HTTPClient client;
    MockHTTPServer::shouldTimeout = true;
    
    HTTPResponse response = client.get(MockHTTPServer::getTestUrl());
    ASSERT_EQ(response.statusCode, -2);  // Expected error code for timeout
    ASSERT_TRUE(response.body.empty());
}

// URL Validation Tests
TEST_F(HTTPClientTest, InvalidUrl) {
    HTTPClient client;
    HTTPResponse response = client.get("not_a_valid_url");
    ASSERT_EQ(response.statusCode, -3);  // Expected error code for invalid URL
    ASSERT_TRUE(response.body.empty());
}

TEST_F(HTTPClientTest, EmptyUrl) {
    HTTPClient client;
    HTTPResponse response = client.get("");
    ASSERT_EQ(response.statusCode, -3);  // Expected error code for invalid URL
    ASSERT_TRUE(response.body.empty());
}

TEST_F(HTTPClientTest, UnsupportedProtocol) {
    HTTPClient client;
    HTTPResponse response = client.get("ftp://example.com");
    ASSERT_EQ(response.statusCode, -4);  // Expected error code for unsupported protocol
    ASSERT_TRUE(response.body.empty());
}

// Response Parsing Tests
TEST_F(HTTPClientTest, JsonResponse) {
    HTTPClient client;
    MockHTTPServer::responseBody = "{\"key\": \"value\"}";
    
    HTTPResponse response = client.get(MockHTTPServer::getTestUrl());
    ASSERT_EQ(response.statusCode, 200);
    ASSERT_EQ(response.body, "{\"key\": \"value\"}");
}

TEST_F(HTTPClientTest, BinaryResponse) {
    HTTPClient client;
    std::string binaryData(1024, '\0');  // 1KB of binary data
    MockHTTPServer::responseBody = binaryData;
    
    HTTPResponse response = client.get(MockHTTPServer::getTestUrl() + "/binary");
    ASSERT_EQ(response.statusCode, 200);
    ASSERT_EQ(response.body.size(), 1024);
}

TEST_F(HTTPClientTest, LargeResponse) {
    HTTPClient client;
    std::string largeData(5 * 1024 * 1024, 'x');  // 5MB of data
    MockHTTPServer::responseBody = largeData;
    
    HTTPResponse response = client.get(MockHTTPServer::getTestUrl() + "/large");
    ASSERT_EQ(response.statusCode, 200);
    ASSERT_EQ(response.body.size(), 5 * 1024 * 1024);
}

// Edge Cases
TEST_F(HTTPClientTest, RedirectHandling) {
    HTTPClient client;
    MockHTTPServer::responseStatus = 302;
    MockHTTPServer::responseBody = "";  // No body for redirect
    
    HTTPResponse response = client.get(MockHTTPServer::getTestUrl() + "/redirect");
    ASSERT_EQ(response.statusCode, 302);
}

TEST_F(HTTPClientTest, SlowResponse) {
    HTTPClient client;
    MockHTTPServer::responseBody = "Delayed Response";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate slow response
    
    HTTPResponse response = client.get(MockHTTPServer::getTestUrl() + "/slow");
    ASSERT_EQ(response.statusCode, 200);
    ASSERT_EQ(response.body, "Delayed Response");
}

TEST_F(HTTPClientTest, SpecialCharacters) {
    HTTPClient client;
    MockHTTPServer::responseBody = "Special チャラクターズ 😊";
    
    HTTPResponse response = client.get(MockHTTPServer::getTestUrl() + "/special");
    ASSERT_EQ(response.statusCode, 200);
    ASSERT_EQ(response.body, "Special チャラクターズ 😊");
}
