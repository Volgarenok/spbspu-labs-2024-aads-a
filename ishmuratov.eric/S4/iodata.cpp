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
      dict[key] = value;
    }
    if (!input.eof())
    {
      input.clear();
    }
    data[name] = dict;
  }
}

void ishmuratov::output_dict(ishmuratov::data_t & data, std::ostream &output)
{
  for (auto dict : data)
  {
    output << dict.first << " ";
    for (auto key : dict.second)
    {
      output << key.first << " " << key.second << " ";
    }
    output << "\n";
  }
}