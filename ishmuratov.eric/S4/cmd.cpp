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

  AVLTree< int, std::string > to_print = data[dict_name];
  output << dict_name << " " << data[dict_name].cbegin()->first << " " << data[dict_name].cbegin()->second;
  for (auto pair = ++to_print.cbegin(); pair != to_print.cend(); ++pair)
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
  if (data.find(first_name) == data.end() || data.find(second_name) == data.end())
  {
    throw std::out_of_range("Non existent dictionary!");
  }

  AVLTree< int, std::string > first_dict = data[first_name];
  AVLTree< int, std::string > second_dict = data[second_name];

  for (auto dict = first_dict.cbegin(); dict != first_dict.cend(); ++dict)
  {
    if (second_dict.find(dict->first) == second_dict.end())
    {
      new_dict.push(dict->first, first_dict[dict->first]);
    }
  }
  for (auto dict = second_dict.cbegin(); dict != second_dict.cend(); ++dict)
  {
    if (first_dict.find(dict->first) == first_dict.end())
    {
      new_dict.push(dict->first, second_dict[dict->first]);
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

  AVLTree< int, std::string > first_dict = data[first_name];
  AVLTree< int, std::string > second_dict = data[second_name];

  for (auto dict = first_dict.cbegin(); dict != first_dict.cend(); ++dict)
  {
    if (second_dict.find(dict->first) != second_dict.end())
    {
      new_dict.push(dict->first, first_dict[dict->first]);
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

  AVLTree< int, std::string > first_dict = data[first_name];
  AVLTree< int, std::string > second_dict = data[second_name];

  for (auto dict = first_dict.cbegin(); dict != first_dict.cend(); ++dict)
  {
    new_dict.push(dict->first, first_dict[dict->first]);
  }
  for (auto dict = second_dict.cbegin(); dict != second_dict.cend(); ++dict)
  {
    if (first_dict.find(dict->first) == first_dict.end())
    {
      new_dict.push(dict->first, second_dict[dict->first]);
    }
  }

  data.push(new_name, new_dict);
}
