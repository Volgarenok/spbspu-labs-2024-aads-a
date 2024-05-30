#include "input_output_collection.hpp"
#include <iostream>
#include <string>
#include "string_format.hpp"
#include "dictionary_record.hpp"

void erohin::inputCollection(collection & dict_context, std::istream & input)
{
  std::string dict_name;
  input >> StringFormat{ dict_name, ':' };
  while (input.good())
  {
    input >> dict_context[dict_name];
    if (!input)
    {
      input.clear();
    }
    input >> StringFormat{ dict_name, ':' };
  }
}

void erohin::outputCollection(const collection & dict_context, std::ostream & output)
{
  auto begin = dict_context.cbegin();
  auto end = dict_context.cend();
  while (begin != end)
  {
    output << ":" << begin->first << ":" << "\n";
    output << begin->second;
    ++begin;
  }
}
