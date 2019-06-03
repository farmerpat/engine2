#ifndef DICT_HPP
#define DICT_HPP

#include <string>
#include <iterator>
#include <map>

struct TypeValuePair {
  std::string type;
  std::string val;
};

class Dict {
  public:
    Dict();
    void add(std::string, std::string, std::string);
    void addInt(std::string, int);
    int getInt(std::string);
    std::string getString(std::string);

  protected:
    std::map<std::string, TypeValuePair> _map;
};
#endif
