#include "include/dict.hpp"

Dict::Dict() { }

void Dict::add(std::string key, std::string value, std::string type) {
  TypeValuePair pair;
  pair.type = type;
  pair.val = value;

  this->_map[key] = pair;
}

int Dict::getInt(std::string key) {
  std::string val = "0";
  std::map<std::string, TypeValuePair>::iterator itr;

  for (itr = this->_map.begin(); itr != this->_map.end(); itr++) {
    std::string thisKey = itr->first;
    if (thisKey == key) {
      TypeValuePair pair = itr->second;

      if (pair.type == "int") {
        val = pair.val;
        break;
      }
    }
  }

  return std::stoi(val);
}

std::string Dict::getString(std::string key) {
  std::string val = "";
  std::map<std::string, TypeValuePair>::iterator itr;

  for (itr = this->_map.begin(); itr != this->_map.end(); itr++) {
    std::string thisKey = itr->first;
    if (thisKey == key) {
      TypeValuePair pair = itr->second;

      if (pair.type == "string") {
        val = pair.val;
        break;
      }
    }
  }

  return val;
}

void Dict::addInt(std::string key, int value) {
  TypeValuePair pair;
  pair.type = "int";
  pair.val = std::to_string(value);

  this->_map[key] = pair;
}
