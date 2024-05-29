#include "input.hpp"

void ishmuratov::input_dictionary(dict_t & dictionaries, std::istream &input)
{
  std::string name;
  while (std::getline(input, name))
  {
    unit_t unit;
    std::string key;
    while (input >> key)
    {
      value_t values;
      std::string value;
      while (input >> value)
      {
        values.pushBack(value);
        if (input.get() == '\n')
        {
          break;
        }
      }
      unit.insert(std::make_pair(key, values));
      if (input.get() == '\n')
      {
        break;
      }
    }
    dictionaries.insert(std::make_pair(name, unit));
  }
}
