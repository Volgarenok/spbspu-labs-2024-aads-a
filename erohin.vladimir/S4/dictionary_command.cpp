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

void erohin::implement(collection & context, std::istream & input, std::ostream & output)
{
  return;
}

void erohin::intersect(collection & context, std::istream & input, std::ostream & output)
{
  return;
}

void erohin::unite(collection & context, std::istream & input, std::ostream & output)
{
  return;
}
