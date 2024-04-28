#include "dictionary_command.hpp"
#include <iostream>
#include <cstring>

void erohin::inputArguments(std::istream & input, std::string * dest, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    if (input.peek() == '\n')
    {
      throw std::invalid_argument("Need more argument to command");
    }
    input >> dest[i];
  }
  if (input.peek() != '\n')
  {
    throw std::invalid_argument("Need less argument to comman");
  }
}

void erohin::print(const collection & context, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  inputArguments(input, std::addressof(dict_name), 1);
  if (!input)
  {
    throw std::runtime_error("Not goodbit was found");
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
  inputArguments(input, dict_name, 3);
  dictionary temp_dict;
  const dictionary & source1 = context.at(dict_name[1]);
  const dictionary & source2 = context.at(dict_name[2]);
  auto iter = source1.cbegin();
  auto end_iter = source1.cend();
  while (iter != end_iter)
  {
    if (source2.find(iter->first) == source2.end())
    {
      temp_dict.insert(*iter);
    }
    ++iter;
  }
  if (context.find(dict_name[0]) != context.end())
  {
    context[dict_name[0]].clear();
  }
  context[dict_name[0]] = std::move(temp_dict);
}

void erohin::intersect(collection & context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  inputArguments(input, dict_name, 3);
  dictionary temp_dict;
  const dictionary & source1 = context.at(dict_name[1]);
  const dictionary & source2 = context.at(dict_name[2]);
  auto iter = source1.cbegin();
  auto end_iter = source1.cend();
  while (iter != end_iter)
  {
    if (source2.find(iter->first) != source2.end())
    {
      temp_dict.insert(*iter);
    }
    ++iter;
  }
  if (context.find(dict_name[0]) != context.end())
  {
    context[dict_name[0]].clear();
  }
  context[dict_name[0]] = std::move(temp_dict);
}

void erohin::unite(collection & context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  inputArguments(input, dict_name, 3);
  dictionary temp_dict;
  const dictionary & source1 = context.at(dict_name[1]);
  const dictionary & source2 = context.at(dict_name[2]);
  temp_dict.insert(source1.cbegin(), source1.cend());
  temp_dict.insert(source2.cbegin(), source2.cend());
  if (context.find(dict_name[0]) != context.end())
  {
    context[dict_name[0]].clear();
  }
  context[dict_name[0]] = std::move(temp_dict);
}
