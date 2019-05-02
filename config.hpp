#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>
#include <fstream>

class Config {
  public:
    Config(std::string);
    std::string query(std::string);

  protected:
    void parseConfigFile(std::string);
    int getIndexOfKey(std::string);
    std::vector<std::string> _keys;
    std::vector<std::string> _values;
};

#endif
