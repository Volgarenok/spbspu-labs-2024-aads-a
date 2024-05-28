#include "input.hpp"

void ishmuratov::input_dictionary(dict_t & dictionaries, std::istream &input)
{
  std::string name;
  std::getline(input, name);

  unit_t unit;
  std::string key;
  while (std::getline(input, key) && !key.empty())
  {
    if (key == "lol")
    {
      break;
    }
    value_t values;
    std::string value;
    while (std::getline(input, value) && !value.empty())
    {
      values.pushBack(value);
    }
    unit.insert(std::make_pair(key, values));
  }
  dictionaries.insert(std::make_pair(name, unit));
}