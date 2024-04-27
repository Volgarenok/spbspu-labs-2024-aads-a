#include "dictionary_command.hpp"
#include <iostream>
#include <cstring>

std::string * erohin::parseStringBySpace(std::string * dest, size_t size, const std::string & source)
{
  char * string_token = std::strtok(const_cast< char * >(source.c_str()), " ");
  size_t index = 0;
  while (string_token)
  {
    if (index == size)
    {
      throw std::invalid_argument("Wrong arguments number");
    }
    dest[index++] = std::string(string_token);
    string_token = std::strtok(nullptr, " ");
  }
  if (index < size)
  {
    throw std::invalid_argument("Wrong arguments number");
  }
  return dest;
}

void erohin::print(const collection & context, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  std::string input_string;
  if (!(input >> input_string))
  {
    return;
  }
  parseStringBySpace(std::addressof(dict_name), 1, input_string);
  const dictionary & dict = context.at(dict_name);
  if (dict.empty())
  {
    throw std::underflow_error("Dictionary is empty");
  }
  output << dict_name;
  auto iter = dict.cbegin();
  auto end_iter = dict.cend();
  while (iter != end_iter)
  {
    output << " " << iter->first << " " << iter->second;
    ++iter;
  }
  output << "\n";
}

void erohin::complement(collection & context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  std::string input_string;
  if (!std::getline(input, input_string))
  {
    return;
  }
  parseStringBySpace(dict_name, 3, input_string);
  auto iter_pair = context.insert(make_pair(dict_name[0], dictionary()));
  if (!iter_pair.second)
  {
    throw std::invalid_argument("Dictionary just exists");
  }
  dictionary & dict = context[dict_name[0]];
  const dictionary & source1 = context.at(dict_name[1]);
  const dictionary & source2 = context.at(dict_name[2]);
  auto iter = source1.cbegin();
  auto end_iter = source1.cend();
  while (iter != end_iter)
  {
    if (source2.find(iter->first) == source2.end())
    {
      dict.insert(*iter);
    }
    ++iter;
  }
}

void erohin::intersect(collection & context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  std::string input_string;
  if (!std::getline(input, input_string))
  {
    return;
  }
  parseStringBySpace(dict_name, 3, input_string);
  auto iter_pair = context.insert(make_pair(dict_name[0], dictionary()));
  if (!iter_pair.second)
  {
    throw std::invalid_argument("Dictionary just exists");
  }
  dictionary & dict = context[dict_name[0]];
  const dictionary & source1 = context.at(dict_name[1]);
  const dictionary & source2 = context.at(dict_name[2]);
  auto iter = source1.cbegin();
  auto end_iter = source1.cend();
  while (iter != end_iter)
  {
    if (source2.find(iter->first) != source2.end())
    {
      dict.insert(*iter);
    }
    ++iter;
  }
}

void erohin::unite(collection & context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  std::string input_string;
  std::getline(input, input_string);
  parseStringBySpace(dict_name, 3, input_string);
  auto iter_pair = context.insert(make_pair(dict_name[0], dictionary()));
  if (!iter_pair.second)
  {
    throw std::invalid_argument("Dictionary just exists");
  }
  dictionary & dict = context[dict_name[0]];
  const dictionary & source1 = context.at(dict_name[1]);
  const dictionary & source2 = context.at(dict_name[2]);
  try
  {
    dict.insert(source1.cbegin(), source1.cend());
    dict.insert(source2.cbegin(), source2.cend());
  }
  catch (...)
  {
    context.erase(dict_name[0]);
    throw;
  }
}
