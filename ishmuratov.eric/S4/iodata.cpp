#include "iodata.hpp"

void ishmuratov::input_dict(ishmuratov::data_t & data, std::istream &input)
{
  std::string name;
  while (input >> name)
  {
    dataset_t dict;
    int key = 0;
    std::string value;

    while (input >> key >> value)
    {
      dict.insert(std::make_pair(key, value));
    }
    if (!input.eof())
    {
      input.clear();
    }
    data.insert(std::make_pair(name, dict));
  }
}
