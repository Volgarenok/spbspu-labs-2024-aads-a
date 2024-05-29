#include "input.hpp"

void ishmuratov::input_dictionary(dict_t & dictionaries, std::istream &input)
{
  std::string name;
  std::getline(input, name);

  unit_t unit;
  std::string key;
  while (input >> key)
  {

    value_t values;
    std::string value;
    while (input >> value)
    {
      values.pushBack(value);
    }
    unit.insert(std::make_pair(key, values));
  }
  dictionaries.insert(std::make_pair(name, unit));
}