#ifndef DB_CONNECTOR_H
#define DB_CONNECTOR_H

#include <string>
#include <cppconn/driver.h>
#include <cppconn/connection.h>

struct QueryResult {
    bool success;
};

class DBConnector {
public:
    DBConnector(const std::string& host, const std::string& user, const std::string& password, const std::string& db);
    ~DBConnector(); // Destructor to close connection
    bool isConnected() const;
    QueryResult executeQuery(const std::string& query);

private:
    sql::Connection *con;
    bool connected;
};

#endif // DB_CONNECTOR_H