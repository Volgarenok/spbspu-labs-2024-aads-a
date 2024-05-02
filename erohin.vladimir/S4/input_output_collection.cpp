#include "input_output_collection.hpp"
#include <iostream>
#include <string>

void erohin::inputCollection(std::istream & input, collection & dest)
{
  std::string dict_name;
  input >> dict_name;
  while (!input.eof())
  {
    size_t key;
    std::string value;
    dest.insert(std::make_pair(dict_name,  dictionary()));
    while (input >> key >> value)
    {
      dest.at(dict_name).insert(std::make_pair(key, value));
    }
    input.clear();
    input >> dict_name;
    if (!dict_name.size())
    {
      continue;
    }
  }
}

void erohin::outputCollection(std::ostream & output, const collection & source)
{
  auto iter = source.cbegin();
  auto end_iter = source.cend();
  while (iter != end_iter)
  {
    output << iter->first;
    const dictionary & cur_dict = iter->second;
    auto dict_iter = cur_dict.cbegin();
    auto dict_end_iter = cur_dict.cbegin();
    while (dict_iter != dict_end_iter)
    {
      output << " " << dict_iter->first << " " << dict_iter->second;
      ++dict_iter;
    }
    output << "\n";
    ++iter;
  }
}
