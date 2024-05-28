#include "input_output_collection.hpp"
#include <iostream>
#include <string>
#include "format.hpp"
#include "dictionary_record.hpp"

void erohin::inputDictionary(dictionary & dict, std::istream & input)
{
  dictionary temp_dict;
  Record record;
  input >> record;
  while (input.good())
  {
    temp_dict.insert(record.data);
    input >> record;
  }
  dict = std::move(temp_dict);
}

void erohin::outputDictionary(const dictionary & dict, std::ostream & output)
{
  auto begin = dict.cbegin();
  auto end = dict.cend();
  while (begin != end)
  {
    output << Record(*(begin++)) << "\n";
  }
}

void erohin::inputCollection(collection & dict_context, std::istream & input)
{
  std::string dict_name;
  input >> StringFormat{ dict_name, ':' };
  while (!input.eof())
  {
    inputDictionary(dict_context[dict_name], input);
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
    outputDictionary(begin->second, output);
    ++begin;
  }
}
