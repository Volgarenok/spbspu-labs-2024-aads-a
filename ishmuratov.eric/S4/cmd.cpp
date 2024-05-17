#include "cmd.hpp"

void ishmuratov::print(ishmuratov::data_t &data, std::istream &input, std::ostream &output)
{
  std::string dict_name;
  input >> dict_name;
  if (data.find(dict_name) == data.cend())
  {
    throw std::runtime_error("Key not found!");
  }
  output << dict_name << " " << data[dict_name].cbegin()->first << " " << data[dict_name].cbegin()->second;
  for (auto pair = ++data[dict_name].cbegin(); pair != data[dict_name].cend(); pair++)
  {
    output << " " << pair->first << " " << pair->second;
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
  if (data.find(first_name) == data.cend() || data.find(second_name) == data.cend())
  {
    throw std::runtime_error("Key not found!");
  }

  for (auto dict = data[first_name].cbegin(); dict != data[first_name].cend(); ++dict)
  {
    if (data[second_name].find(dict->first) == data[second_name].cend())
    {
      new_dict[dict->first] = data[first_name][dict->first];
    }
  }
  for (auto dict = data[second_name].cbegin(); dict != data[second_name].cend(); ++dict)
  {
    if (data[first_name].find(dict->first) == data[first_name].cend())
    {
      new_dict[dict->first] = data[second_name][dict->first];
    }
  }
  data[new_name] = new_dict;
}

void ishmuratov::intersect(ishmuratov::data_t &data, std::istream &input)
{
  std::string new_name;
  std::string first_name;
  std::string second_name;
  dataset_t new_dict;

  input >> new_name >> first_name >> second_name;
  if (data.find(first_name) == data.cend() || data.find(second_name) == data.cend())
  {
    throw std::runtime_error("Key not found!");
  }
  for (auto dict = data[first_name].cbegin(); dict != data[first_name].cend(); ++dict)
  {
    if (data[second_name].find(dict->first) != data[second_name].cend())
    {
      new_dict[dict->first] = data[first_name][dict->first];
    }
  }
  data[new_name] = new_dict;
}

void ishmuratov::uniond(ishmuratov::data_t &data, std::istream &input)
{
  std::string new_name;
  std::string first_name;
  std::string second_name;
  dataset_t new_dict;

  input >> new_name >> first_name >> second_name;
  if (data.find(first_name) == data.cend() || data.find(second_name) == data.cend())
  {
    throw std::runtime_error("Key not found!");
  }

  for (auto dict = data[first_name].cbegin(); dict != data[first_name].cend(); ++dict)
  {
    new_dict[dict->first] = data[first_name][dict->first];
  }
  for (auto dict = data[second_name].cbegin(); dict != data[second_name].cend(); ++dict)
  {
    if (data[first_name].find(dict->first) == data[first_name].cend())
    {
      new_dict[dict->first] = data[second_name][dict->first];
    }
  }
  data[new_name] = new_dict;
}
