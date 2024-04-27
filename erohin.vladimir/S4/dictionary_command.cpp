#include "dictionary_command.hpp"
#include <iostream>
#include <cstring>

std::string * erohin::parseStringBySpace(std::string * dest, const std::string & source, size_t size)
{
  return dest;
}

void erohin::print(const collection & context, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  input >> dict_name;
  if (!input.good())
  {
    return;
  }
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
  for (int i = 0; i < 3; ++i)
  {
    input >> dict_name[i];
  }
  if (!input.good())
  {
    return;
  }
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
  for (int i = 0; i < 3; ++i)
  {
    input >> dict_name[i];
  }
  if (!input.good())
  {
    return;
  }
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
  for (int i = 0; i < 3; ++i)
  {
    input >> dict_name[i];
  }
  if (!input.good())
  {
    return;
  }
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
