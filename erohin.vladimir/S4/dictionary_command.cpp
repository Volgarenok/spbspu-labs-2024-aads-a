#include "dictionary_command.hpp"
#include <iostream>
#include <cstring>

void erohin::print(const collection & context, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  input >> dict_name;
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
  input >> dict_name[0] >> dict_name[1] >> dict_name[2];
  dictionary temp_dict;
  const dictionary & source1 = context.at(dict_name[1]);
  const dictionary & source2 = context.at(dict_name[2]);
  auto iter = source1.cbegin();
  auto end_iter = source1.cend();
  while (iter != end_iter)
  {
    if (source2.find(iter->first) == source2.cend())
    {
      temp_dict.insert(*iter);
    }
    ++iter;
  }
  if (context.find(dict_name[0]) != context.end())
  {
    context.at(dict_name[0]).clear();
    context.at(dict_name[0]) = std::move(temp_dict);
  }
  else
  {
    context.insert(std::make_pair(dict_name[0], std::move(temp_dict)));
  }
}

void erohin::intersect(collection & context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  input >> dict_name[0] >> dict_name[1] >> dict_name[2];
  dictionary temp_dict;
  const dictionary & source1 = context.at(dict_name[1]);
  const dictionary & source2 = context.at(dict_name[2]);
  auto iter = source1.cbegin();
  auto end_iter = source1.cend();
  while (iter != end_iter)
  {
    if (source2.find(iter->first) != source2.cend())
    {
      temp_dict.insert(*iter);
    }
    ++iter;
  }
  if (context.find(dict_name[0]) != context.end())
  {
    context.at(dict_name[0]).clear();
    context.at(dict_name[0]) = std::move(temp_dict);
  }
  else
  {
    context.insert(std::make_pair(dict_name[0], std::move(temp_dict)));
  }
}

void erohin::unite(collection & context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  input >> dict_name[0] >> dict_name[1] >> dict_name[2];
  dictionary temp_dict;
  const dictionary & source1 = context.at(dict_name[1]);
  const dictionary & source2 = context.at(dict_name[2]);
  temp_dict.insert(source1.cbegin(), source1.cend());
  temp_dict.insert(source2.cbegin(), source2.cend());
  if (context.find(dict_name[0]) != context.end())
  {
    context.at(dict_name[0]).clear();
    context.at(dict_name[0]) = std::move(temp_dict);
  }
  else
  {
    context.insert(std::make_pair(dict_name[0], std::move(temp_dict)));
  }
}
