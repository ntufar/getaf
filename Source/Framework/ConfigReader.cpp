#include "ConfigReader.h"
#include <fstream>

ConfigReader::ConfigReader(const std::string& filepath) {
    std::ifstream file(filepath);
    if (file.is_open()) {
        try {
            file >> data;
            valid = true;
        } catch (const nlohmann::json::parse_error& e) {
            valid = false;
        }
    } else {
        valid = false;
    }
}

bool ConfigReader::isValid() const {
    return valid;
}

std::string ConfigReader::getString(const std::string& key) const {
    if (valid && data.contains(key) && data[key].is_string()) {
        return data[key];
    }
    return "";
}
