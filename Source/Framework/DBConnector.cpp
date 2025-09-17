#include "DBConnector.h"
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

DBConnector::DBConnector(const std::string& host, const std::string& user, const std::string& password, const std::string& db)
    : con(nullptr), connected(false)
{
    sql::mysql::MySQL_Driver *driver;

    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(host, user, password);
        con->setSchema(db);
        connected = true;
        std::cout << "Successfully connected to database: " << db << std::endl;
    } catch (sql::SQLException &e) {
        std::cerr << "Could not connect to MySQL server. Error: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        connected = false;
    }
}

DBConnector::~DBConnector() {
    if (con) {
        con->close();
        delete con;
        con = nullptr;
    }
}

bool DBConnector::isConnected() const {
    return connected;
}

QueryResult DBConnector::executeQuery(const std::string& query) {
    QueryResult result;
    result.success = false;

    if (!connected || !con) {
        std::cerr << "Cannot execute query: Not connected to database." << std::endl;
        return result;
    }

    sql::Statement *stmt = nullptr;
    try {
        stmt = con->createStatement();
        stmt->execute(query);
        result.success = true;

        delete stmt;

    } catch (sql::SQLException &e) {
        std::cerr << "Failed to execute query: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << ")" << std::endl;
        result.success = false;
    }

    if (stmt) {
        delete stmt;
    }

    return result;
}
