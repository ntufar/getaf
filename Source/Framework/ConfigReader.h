#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include "nlohmann/json.hpp"

class ConfigReader {
public:
    ConfigReader(const std::string& filepath);
    bool isValid() const;
    std::string getString(const std::string& key) const;

private:
    nlohmann::json data;
    bool valid;
};

#endif // CONFIG_READER_H
