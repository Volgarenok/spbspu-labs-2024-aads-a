#include "commands.hpp"

void belokurskaya::cmds::complement(DictCol& dictionaries, std::istream& in, std::ostream& out)
{
  std::string new_name, first_name, second_name;
  in >> new_name >> first_name >> second_name;

  subcmds::validateDictionaries(dictionaries, first_name, second_name);

  Dictionary* first_dict = dictionaries.find(first_name);
  Dictionary* second_dict = dictionaries.find(second_name);

  Dictionary temp_dict;
  for (auto it = first_dict->begin(); it != first_dict->end(); ++it)
  {
    if (!second_dict->exists((*it).first))
    {
      temp_dict.push((*it).first, (*it).second);
    }
  }

  if (new_name == first_name)
  {
    *first_dict = std::move(temp_dict);
  }
  else
  {
    dictionaries.add(new_name, std::move(temp_dict));
  }
}

void belokurskaya::cmds::intersect(DictCol& dictionaries, std::istream& in, std::ostream& out)
{
  std::string new_name, first_name, second_name;
  in >> new_name >> first_name >> second_name;

  subcmds::validateDictionaries(dictionaries, first_name, second_name);

  Dictionary* first_dict = dictionaries.find(first_name);
  Dictionary* second_dict = dictionaries.find(second_name);

  Dictionary temp_dict;
  for (auto it = first_dict->begin(); it != first_dict->end(); ++it)
  {
    if (second_dict->exists((*it).first))
    {
      temp_dict.push((*it).first, (*it).second);
    }
  }
  dictionaries.add(new_name, std::move(temp_dict));
}

void belokurskaya::cmds::unionDicts(DictCol& dictionaries, std::istream& in, std::ostream& out)
{
  std::string new_name, first_name, second_name;
  in >> new_name >> first_name >> second_name;

  subcmds::validateDictionaries(dictionaries, first_name, second_name);

  Dictionary* first_dict = dictionaries.find(first_name);
  Dictionary* second_dict = dictionaries.find(second_name);

  Dictionary temp_dict = *first_dict;
  for (auto it = second_dict->begin(); it != second_dict->end(); ++it)
  {
    if (!temp_dict.exists((*it).first))
    {
      temp_dict.push((*it).first, (*it).second);
    }
  }
  dictionaries.add(new_name, std::move(temp_dict));
}

void belokurskaya::cmds::printCommand(DictCol& dictionaries, std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;

  Dictionary* dict = dictionaries.find(name);
  if (dict)
  {
    subcmds::printDictionary(*dict, name);
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}

void belokurskaya::cmds::subcmds::printDictionary(const Dictionary& dict, Str& name)
{
  if (dict.empty())
  {
    std::cout << "<EMPTY>\n";
  }
  else
  {
    std::cout << name;
    for (auto it = dict.begin(); it != dict.end(); ++it)
    {
      std::cout << " " << (*it).first << " " << (*it).second;
    }
    std::cout << std::endl;
  }
}

void belokurskaya::cmds::subcmds::validateDictionaries(DictCol& dictionaries, Str name1, Str name2)
{
  Dictionary* dict1 = dictionaries.find(name1);
  Dictionary* dict2 = dictionaries.find(name2);

  if (!dict1 || !dict2)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
}