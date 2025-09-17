#ifndef DB_CONNECTOR_H
#define DB_CONNECTOR_H

#include <string>

struct QueryResult {
    bool success;
};

class DBConnector {
public:
    DBConnector(const std::string& host, const std::string& user, const std::string& password, const std::string& db);
    bool isConnected() const;
    QueryResult executeQuery(const std::string& query);

private:
    bool connected;
};

#endif // DB_CONNECTOR_H
