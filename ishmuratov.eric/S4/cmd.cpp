#include "cmd.hpp"

void ishmuratov::print(ishmuratov::data_t &data, std::istream &input, std::ostream &output)
{
  std::string dict_name;
  input >> dict_name;
  if (data.find(dict_name) == data.end())
  {
    throw std::out_of_range("Non existent dictionary!");
  }
  if (data[dict_name].empty())
  {
    throw std::underflow_error("Dictionary is empty!");
  }
//  AVLTree< int, std::string > to_print = data[dict_name];
  output << dict_name << " " << data[dict_name].cbegin()->first << " " << data[dict_name].cbegin()->second;
//  for (auto pair = ++to_print.cbegin(); pair != to_print.cend(); ++pair)
//  {
//    output << " " << pair->first << " " << pair->second;
//  }
  for (const auto& pair: data[dict_name])
  {
    output << " " << pair.first << " " << pair.second;
  }
  output << "\n";
}

void ishmuratov::complement(ishmuratov::data_t &data, std::istream &input)
{
  std::string new_name;
  std::string first_name;
  std::string second_name;
  dataset_t new_dict;

  input >> new_name >> first_name >> second_name;
  if (data.find(first_name) == data.end() || data.find(second_name) == data.end())
  {
    throw std::out_of_range("Non existent dictionary!");
  }

  for (auto dict = data[first_name].cbegin(); dict != data[first_name].cend(); ++dict)
  {
    if (data[second_name].find(dict->first) == data[second_name].end())
    {
      new_dict.push(dict->first, data[first_name][dict->first]);
    }
  }
  for (auto dict = data[second_name].cbegin(); dict != data[second_name].cend(); ++dict)
  {
    if (data[first_name].find(dict->first) == data[first_name].end())
    {
      new_dict.push(dict->first, data[second_name][dict->first]);
    }
  }
  data.push(new_name, new_dict);
}

void ishmuratov::intersect(ishmuratov::data_t &data, std::istream &input)
{
  std::string new_name;
  std::string first_name;
  std::string second_name;
  dataset_t new_dict;

  input >> new_name >> first_name >> second_name;
  if (data.find(first_name) == data.end() || data.find(second_name) == data.end())
  {
    throw std::out_of_range("Non existent dictionary!");
  }
  for (auto dict = data[first_name].cbegin(); dict != data[first_name].cend(); ++dict)
  {
    if (data[second_name].find(dict->first) != data[second_name].end())
    {
      new_dict.push(dict->first, data[first_name][dict->first]);
    }
  }
  data.push(new_name, new_dict);
}

void ishmuratov::uniond(ishmuratov::data_t &data, std::istream &input)
{
  std::string new_name;
  std::string first_name;
  std::string second_name;
  dataset_t new_dict;

  input >> new_name >> first_name >> second_name;
  if (data.find(first_name) == data.end() || data.find(second_name) == data.end())
  {
    throw std::out_of_range("Non existent dictionary!");
  }

  for (auto dict = data[first_name].cbegin(); dict != data[first_name].cend(); ++dict)
  {
    new_dict.push(dict->first, data[first_name][dict->first]);
  }
  for (auto dict = data[second_name].cbegin(); dict != data[second_name].cend(); ++dict)
  {
    if (data[first_name].find(dict->first) == data[first_name].end())
    {
      new_dict.push(dict->first, data[second_name][dict->first]);
    }
  }
  data.push(new_name, new_dict);
}
