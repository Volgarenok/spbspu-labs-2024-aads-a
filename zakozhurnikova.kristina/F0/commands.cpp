#include <iostream>
#include "commands.hpp"

void addDictionary(std::string& dictionaryName, dictionaryOne& toAdd, dict& dictionary)
{
  if (toAdd.empty())
  {
    std::cout << "<EMPTY>\n";
    return;
  }
  if (dictionary.find(dictionaryName) != dictionary.cend())
  {
    dictionary[dictionaryName] = std::move(toAdd);
  }
  else
  {
    dictionary.push(dictionaryName, toAdd);
  }
}

void zakozhurnikova::print(const List< std::string >& args, const dict& dictionary)
{
  if (args.size() != 1)
  {
    throw std::invalid_argument("incorrect command source");
  }
  std::string result;
  std::string mapName = args.back();
  if (!dictionary.at(mapName).empty())
  {
    result = mapName + ' ';
    for (auto it = dictionary[mapName].cbegin(); it != dictionary[mapName].cend(); ++it)
    {
      result += it->first + ' ';
      for (auto itList = (it->second).begin(); itList != (it->second).end(); ++itList)
      {
        result += *itList + ' ';
      }
    }
    result.pop_back();
  }
  else
  {
    result = "<EMPTY>";
  }
  std::cout << result << '\n';
}

void zakozhurnikova::complement(List< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  dictionaryOne& secondMap = dictionary.at(args.back());
  args.pop_back();
  dictionaryOne& firstMap = dictionary.at(args.back());
  dictionaryOne resultDictionary;

  for (auto it = firstMap.cbegin(); it != firstMap.cend(); ++it)
  {
    if (secondMap.find(it->first) == secondMap.cend())
    {
      resultDictionary.push(it->first, it->second);
    }
  }
  addDictionary(args.front(), resultDictionary, dictionary);
}

void zakozhurnikova::intersect(List< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  dictionaryOne& secondMap = dictionary.at(args.back());
  args.pop_back();
  dictionaryOne& firstMap = dictionary.at(args.back());
  dictionaryOne resultDictionary;

  for (auto it = firstMap.cbegin(); it != firstMap.cend(); ++it)
  {
    if (secondMap.find(it->first) != secondMap.cend())
    {
      resultDictionary.push(it->first, it->second);
    }
  }
  addDictionary(args.front(), resultDictionary, dictionary);
}

void zakozhurnikova::doUnion(List< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  dictionaryOne& secondMap = dictionary.at(args.back());
  args.pop_back();
  dictionaryOne& firstMap = dictionary.at(args.back());
  dictionaryOne resultDictionary;

  for (auto it = firstMap.cbegin(); it != firstMap.cend(); ++it)
  {
    resultDictionary.push(it->first, it->second);
  }

  for (auto it = secondMap.cbegin(); it != secondMap.cend(); ++it)
  {
    if (resultDictionary.find(it->first) == resultDictionary.cend())
    {
      resultDictionary.push(it->first, it->second);
    }
  }

  addDictionary(args.front(), resultDictionary, dictionary);
}

bool checkSymbol(const std::string& temp)
{
  if (temp.size() != 1 || !((temp[0] >= 'a' && temp[0] <= 'z') || (temp[0] >= 'A' && temp[0] <= 'Z')))
  {
    return false;
  }
  return true;
}

void zakozhurnikova::specificLetter(List< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("Incorrect command source");
  }
  dictionaryOne& current = dictionary.at(args.back());
  args.pop_back();
  std::string symbol = args.back();
  if (!checkSymbol(symbol))
  {
    throw std::invalid_argument("Incorrect symbol");
  }
  dictionaryOne resultDictionary;
  for (auto it = current.cbegin(); it != current.cend(); ++it)
  {
    std::string temp = it->first;
    if (temp[0] == symbol[0])
    {
      resultDictionary.push(it->first, it->second);
    }
  }
  addDictionary(args.front(), resultDictionary, dictionary);
}

void zakozhurnikova::elimination(List< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }
  dictionaryOne& current = dictionary.at(args.front());
  args.pop_front();
  std::string word = args.front();
  args.pop_front();
  std::string translate = args.front();
  List< std::string >& temp = current[word];
  if (!temp.empty())
  {
    temp.clear();
  }
  temp.push_back(translate);
  current[word] = temp;
}

void zakozhurnikova::destruction(List< std::string >& args, dict& dictionary)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("incorrect command source");
  }
  try
  {
    dictionaryOne& current = dictionary.at(args.front());
    std::string word = args.back();
    current.del(word);
  }
  catch (const std::out_of_range& e)
  {
    std::cout << "The word was not found\n";
  }
}

void zakozhurnikova::addition(List< std::string >& args, dict& dictionary)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("incorrect command source");
  }

  dictionaryOne& secondMap = dictionary.at(args.back());
  args.pop_back();
  dictionaryOne& firstMap = dictionary.at(args.back());

  for (auto it = secondMap.cbegin(); it != secondMap.cend(); ++it)
  {
    if (firstMap.find(it->first) != firstMap.cend())
    {
      (firstMap[it->first]).clear();
      firstMap[it->first] = it->second;
    }
  }
}

bool isPalindrome(const std::string& word)
{
  size_t len = word.length();
  for (size_t i = 0; i < len / 2; ++i)
  {
    if (word[i] != word[len - i - 1])
    {
      return false;
    }
  }
  return true;
}

void zakozhurnikova::palindrome(List< std::string >& args, dict& dictionary)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("incorrect command source");
  }
  dictionaryOne& current = dictionary.at(args.back());
  dictionaryOne resultDictionary;
  std::string nameDictionary = args.front();
  for (auto it = current.cbegin(); it != current.cend(); ++it)
  {
    if (isPalindrome(it->first))
    {
      resultDictionary.push(it->first, it->second);
    }
  }
  addDictionary(nameDictionary, resultDictionary, dictionary);
}

void zakozhurnikova::rider(List< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("Incorrect command source");
  }
  dictionaryOne& current = dictionary.at(args.front());
  args.pop_front();
  std::string word = args.front();
  std::string translate = args.back();
  try
  {
    List< std::string >& temp = current.at(word);
    for (auto it = temp.begin(); it != temp.end(); ++it)
    {
      if (translate == *it)
      {
        std::cout << "there is already a translation of word";
        return;
      }
    }
    temp.push_back(translate);
  }
  catch(const std::out_of_range &e)
  {
    List< std::string > currentTranslate;
    currentTranslate.push_back(translate);
    current.push(word, currentTranslate);
  }
}

void zakozhurnikova::interpreter(List< std::string >& args, dict& dictionary)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("incorrect command source");
  }
  std::string result;
  dictionaryOne& current = dictionary.at(args.front());
  args.pop_front();
  std::string word = args.front();
  if (current.find(word) != current.cend())
  {
    result += *current[word].cbegin();
    for (auto it = ++current[word].cbegin(); it != current[word].cend(); ++it)
    {
      result += ' ' + *it;
    }
  }
  else
  {
    result = "<EMPTY>";
  }
  std::cout << result << '\n';
}
