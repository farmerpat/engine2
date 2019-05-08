#include "include/config.hpp"

Config::Config (std::string file="config.ini") {
  this->parseConfigFile(file);
}

std::string Config::query(std::string key) {
  std::string val = "";
  int idx = this->getIndexOfKey(key);

  if (idx != -1) {
    val = this->_values[idx];
  }

  return val;
}

int Config::getIndexOfKey(std::string key) {
  int idx = -1;
  for (std::vector<std::string>::size_type i = 0; i < this->_keys.size(); i++) {
    if (this->_keys[i] == key) {
      idx = i;
      break;
    }
  }

  return idx;
}

void Config::parseConfigFile(std::string fileName) {
  std::ifstream file(fileName);
  std::string line;

  while (std::getline(file, line)) {
    // ignore comments and empty lines
    if ((line.compare("") == 0) || line.at(0) == '#' || line.at(0) == '\n') {
      continue;
    }

    size_t equalIndex = line.find("=");
    std::string key = line.substr(0, equalIndex);
    std::string val = line.substr(equalIndex+1);

    this->_keys.push_back(key);
    this->_values.push_back(val);
  }
}
