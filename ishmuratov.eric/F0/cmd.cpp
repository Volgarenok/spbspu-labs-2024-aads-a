#include "cmd.hpp"

void ishmuratov::create_dict(dict_t & dictionaries, std::istream & input)
{
  unit_t content;
  std::string name;
  std::cin >> name;
  dictionaries.insert(std::make_pair(name, content));
}

void ishmuratov::delete_dict(ishmuratov::dict_t & dictionaries, std::istream & input)
{
  std::string name;
  std::cin >> name;
  dictionaries.erase(name);
}