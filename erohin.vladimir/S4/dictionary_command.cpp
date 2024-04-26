#include "dictionary_command.hpp"
#include <iostream>

void erohin::print(const collection & context, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  input >> dict_name;
  const dictionary & dict = context.at(dict_name);
  if (dict.empty())
  {
    throw std::logic_error("Dictionary is empty");
  }
  output << dict_name;
  auto iter = dict.cbegin();
  auto end_iter = dict.cend();
  output << iter->first << " " << iter->second;
  ++iter;
  if (iter != end_iter)
  {
    output << " ";
  }
  while (iter != end_iter)
  {
    output << iter->first << " " << iter->second;
    ++iter;
  }
  output << "\n";
}

void erohin::implement(collection & context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  for (int i = 0; i < 3; ++i)
  {
    input >> dict_name[i];
    if (input.peek() == '\n')
    {
      throw std::runtime_error("End of line was found");
    }
  }
  context[dict_name[0]] = dictionary();
  dictionary & dict = context.at(dict_name[0]);
  const dictionary & source1 = context.at(dict_name[1]);
  const dictionary & source2 = context.at(dict_name[2]);
  auto iter = source1.cbegin();
  auto end_iter = source1.cend();
  while (iter != end_iter)
  {
    if (source2.find(iter->first) == source2.end())
    {
      dict[iter->first] = iter->second;
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
    if (input.peek() == '\n')
    {
      throw std::runtime_error("End of line was found");
    }
  }
  context[dict_name[0]] = dictionary();
  dictionary & dict = context.at(dict_name[0]);
  const dictionary & source1 = context.at(dict_name[1]);
  const dictionary & source2 = context.at(dict_name[2]);
  auto iter = source1.cbegin();
  auto end_iter = source1.cend();
  try
  {
    while (iter != end_iter)
    {
      if (source2.find(iter->first) != source2.end())
      {
        dict[iter->first] = iter->second;
      }
      ++iter;
    }
  }
  catch (...)
  {
    context.erase(std::move(dict_name[0]));
    throw;
  }
}

void erohin::unite(collection & context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  for (int i = 0; i < 3; ++i)
  {
    input >> dict_name[i];
    if (input.peek() == '\n')
    {
      throw std::runtime_error("End of line was found");
    }
  }
  context[dict_name[0]] = dictionary();
  dictionary & dict = context.at(dict_name[0]);
  const dictionary & source1 = context.at(dict_name[1]);
  const dictionary & source2 = context.at(dict_name[2]);
  try
  {
    dict.insert(source1.cbegin(), source1.cend());
    dict.insert(source2.cbegin(), source2.cend());
  }
  catch (...)
  {
    context.erase(std::move(dict_name[0]));
    throw;
  }
}
