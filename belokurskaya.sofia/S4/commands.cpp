#include "commands.hpp"

void belokurskaya::cmds::complement(DictCol dictionaries, std::istream& in)
{
  std::string new_name = "", first_name = "", second_name = "";
  in >> new_name >> first_name >> second_name;
  subcmds::complementDicts(dictionaries, new_name, first_name, second_name);
}

void belokurskaya::cmds::intersect(DictCol dictionaries, std::istream& in)
{
  std::string new_name = "", first_name = "", second_name = "";
  in >> new_name >> first_name >> second_name;
  subcmds::intersectDicts(dictionaries, new_name, first_name, second_name);
}

void belokurskaya::cmds::unionD(DictCol dictionaries, std::istream& in)
{
  std::string new_name = "", first_name = "", second_name = "";
  in >> new_name >> first_name >> second_name;
  subcmds::unionDicts(dictionaries, new_name, first_name, second_name);
}

void belokurskaya::cmds::print(DictCol dictionaries, std::istream& in)
{
  std::string name = "";
  in >> name;
  subcmds::printCommand(dictionaries, name);
}

void belokurskaya::cmds::subcmds::complementDicts(DictCol dictionaries, Str new_name, Str first_name, Str second_name)
{
  subcmds::validateDictionaries(dictionaries, first_name, second_name);

  Dictionary* source_dict = dictionaries.find(first_name);
  Dictionary* subtract_dict = dictionaries.find(second_name);

  if (source_dict->empty() || subtract_dict->empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  Dictionary temp_dict;
  for (auto it = source_dict->begin(); it != source_dict->end(); ++it)
  {
    if (!subtract_dict->exists((*it).first))
    {
      temp_dict.push((*it).first, (*it).second);
    }
  }

  if (new_name == first_name)
  {
    *source_dict = std::move(temp_dict);
  }
  else
  {
    dictionaries.add(new_name, std::move(temp_dict));
  }
}

void belokurskaya::cmds::subcmds::intersectDicts(DictCol dictionaries, Str new_name, Str first_name, Str second_name)
{
  subcmds::validateDictionaries(dictionaries, first_name, second_name);

  Dictionary* first_dict = dictionaries.find(first_name);
  Dictionary* second_dict = dictionaries.find(second_name);

  if (first_dict->empty() || second_dict->empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

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

void belokurskaya::cmds::subcmds::unionDicts(DictCol dictionaries, Str new_name, Str first_name, Str second_name)
{
  subcmds::validateDictionaries(dictionaries, first_name, second_name);

  Dictionary* first_dict = dictionaries.find(first_name);
  Dictionary* second_dict = dictionaries.find(second_name);

  if (first_dict->empty() || second_dict->empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

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

void belokurskaya::cmds::subcmds::printCommand(DictCol dictionaries, Str name)
{
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

void belokurskaya::cmds::subcmds::validateDictionaries(DictCol dictionaries, Str name1, Str name2)
{
  Dictionary* dict1 = dictionaries.find(name1);
  Dictionary* dict2 = dictionaries.find(name2);

  if (!dict1 || !dict2)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
}

void belokurskaya::cmds::subcmds::printDictionary(const Dictionary& dict, Str name)
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
    std::cout << "\n";
  }
}
