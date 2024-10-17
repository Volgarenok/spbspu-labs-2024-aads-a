#include "commands.hpp"
#include <fstream>
#include <algorithm>
#include "commandsImpl.hpp"

void baranov::createCmd(Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  if (dicts.find(dictName) != dicts.end())
  {
    throw std::logic_error("Already exists\n");
  }
  dicts[dictName];
  if (in.peek() != '\n')
  {
    std::string fileName;
    in >> fileName;
    std::ifstream file(fileName);
    if (!file.is_open())
    {
      throw std::logic_error("Invalid file name\n");
    }
    extendDict(dicts[dictName], file);
  }
}

void baranov::clearCmd(Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  dicts.at(dictName).clear();
}

void baranov::deleteCmd(Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  auto it = dicts.find(dictName);
  if (it == dicts.end())
  {
    throw std::logic_error("Invalid dictionary name\n");
  }
  dicts.erase(it);
}

void baranov::addWordsCmd(Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  std::string fileName;
  in >> fileName;
  std::ifstream file(fileName);
  if (!file.is_open())
  {
    throw std::logic_error("Invalid file name\n");
  }
  extendDict(dicts[dictName], file);
}

void baranov::printCountCmd(const Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream & out)
{
  std::string word;
  in >> word;
  if (in.peek() != '\n')
  {
    std::string dictName;
    in >> dictName;
    out << getWordCount(dicts.at(dictName), word) << '\n';
  }
  else
  {
    if (dicts.empty())
    {
      throw std::logic_error("There are no dictionaries\n");
    }
    for (auto it = dicts.cbegin(); it != dicts.cend(); ++it)
    {
      size_t count = getWordCount(it->second, word);
      out << it->first << ' ' << count << '\n';
    }
  }
}

void baranov::printDictCmd(const Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream & out)
{
  std::string dictName;
  in >> dictName;
  const dict_t & dict = dicts.at(dictName);
  for (auto it = dict.cbegin(); it != dict.cend(); ++it)
  {
    printElement(*it, out);
  }
}

void baranov::printTopCmd(const Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream & out)
{
  std::string dictName;
  in >> dictName;
  dict_t tempdict = dicts.at(dictName);
  size_t tmp = 0;
  if (in.peek() != '\n')
  {
    in >> tmp;
    if (tmp == 0)
    {
      throw std::logic_error("Invalid command\n");
    }
  }
  size_t count = tmp == 0 ? tempdict.size() : std::min(tmp, tempdict.size());
  if (count == 0)
  {
    return;
  }
  for (size_t i = 0; i < count; ++i)
  {
    auto max = std::max_element(tempdict.cbegin(), tempdict.cend(), countComparator);
    printElement(*max, out);
    tempdict.erase(max);
  }
}

void baranov::joinCmd(Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dict1Name;
  in >> dict1Name;
  const dict_t & dict1 = dicts.at(dict1Name);
  std::string dict2Name;
  in >> dict2Name;
  const dict_t & dict2 = dicts.at(dict2Name);
  dict_t result = dict1;
  for (auto it = dict2.cbegin(); it != dict2.cend(); ++it)
  {
    result[it->first] += it->second;
  }
  std::string resultDictName;
  in >> resultDictName;
  dicts[resultDictName] = result;
}

void baranov::intersectCmd(Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dict1Name;
  in >> dict1Name;
  const dict_t & dict1 = dicts.at(dict1Name);
  std::string dict2Name;
  in >> dict2Name;
  const dict_t & dict2 = dicts.at(dict2Name);
  dict_t result;
  for (auto it = dict1.cbegin(); it != dict1.cend(); ++it)
  {
    if (dict2.find(it->first) != dict2.cend())
    {
      result[it->first] = it->second;
      result[it->first] += getWordCount(dict2, it->first);
    }
  }
  std::string resultDictName;
  in >> resultDictName;
  dicts[resultDictName] = result;
}

void baranov::saveCmd(const Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  std::string fileName;
  in >> fileName;
  std::ofstream file(fileName);
  file << dictName << '\n';
  const dict_t & dict = dicts.at(dictName);
  for (auto it = dict.cbegin(); it != dict.cend(); ++it)
  {
    printElement(*it, file);
  }
}

void baranov::lsDictsCmd(const Tree< std::string, dict_t > & dicts, std::istream &, std::ostream & out)
{
  using namespace std::placeholders;
  for (auto it = dicts.cbegin(); it != dicts.cend(); ++it)
  {
    out << it->first << '\n';
  }
}

