#include "cmd.hpp"

void ishmuratov::print(const data_t &data, std::istream &input, std::ostream &output)
{
  std::string dict_name;
  input >> dict_name;
  if (data.find(dict_name) == data.cend())
  {
    throw std::out_of_range("Non existent dictionary!");
  }
  if (data.at(dict_name).empty())
  {
    throw std::underflow_error("Dictionary is empty!");
  }

  output << dict_name << " " << data.at(dict_name).cbegin()->first << " " << data.at(dict_name).cbegin()->second;
  for (auto pair = ++data.at(dict_name).cbegin(); pair != data.at(dict_name).cend(); ++pair)
  {
    output << " " << pair->first << " " << pair->second;
  }
  output << "\n";
}

void ishmuratov::complement(data_t &data, std::istream &input)
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

  for (auto dict = data.at(first_name).cbegin(); dict != data.at(first_name).cend(); ++dict)
  {
    if (data.at(second_name).find(dict->first) == data.at(second_name).end())
    {
      new_dict.insert(std::make_pair(dict->first, data.at(first_name).at(dict->first)));
    }
  }
  for (auto dict = data.at(second_name).cbegin(); dict != data.at(second_name).cend(); ++dict)
  {
    if (data.at(first_name).find(dict->first) == data.at(first_name).end())
    {
      new_dict.insert(std::make_pair(dict->first, data.at(second_name).at(dict->first)));
    }
  }

  data.insert(std::make_pair(new_name, new_dict));
}

void ishmuratov::intersect(data_t &data, std::istream &input)
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

  for (auto dict = data.at(first_name).cbegin(); dict != data.at(first_name).cend(); ++dict)
  {
    if (data.at(second_name).find(dict->first) != data.at(second_name).end())
    {
      new_dict.insert(std::make_pair(dict->first, data.at(first_name).at(dict->first)));
    }
  }

  data.insert(std::make_pair(new_name, new_dict));
}

void ishmuratov::uniond(data_t &data, std::istream &input)
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

  for (auto dict = data.at(first_name).cbegin(); dict != data.at(first_name).cend(); ++dict)
  {
    new_dict.insert(std::make_pair(dict->first, data.at(first_name).at(dict->first)));
  }
  for (auto dict = data.at(second_name).cbegin(); dict != data.at(second_name).cend(); ++dict)
  {
    if (new_dict.find(dict->first) == new_dict.end())
    {
      new_dict.insert(std::make_pair(dict->first, data.at(second_name).at(dict->first)));
    }
  }

  data.insert(std::make_pair(new_name, new_dict));
}
