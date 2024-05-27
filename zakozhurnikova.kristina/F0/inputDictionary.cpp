#include "inputDictionary.hpp"
#include <iostream>
#include <limits>
#include <scopeGuard.hpp>

void zakozhurnikova::inputArgs(std::istream& in, List< std::string >& args)
{
  ScopeGuard guard(in);
  in >> std::noskipws;
  std::string tmp;
  char delim = 0;
  in >> delim;
  while (in && delim != '\n')
  {
    in >> tmp;
    if (in)
    {
      args.push_back(tmp);
    }
    in >> delim;
  }
}

bool isEnglish(const std::string& temp)
{
  if ((temp[0] >= 'a' && temp[0] <= 'z') || (temp[0] >= 'A' && temp[0] <= 'Z'))
  {
    return true;
  }
  return false;
}

void zakozhurnikova::inputDictionary(
  std::istream& in, BinarySearchTree< std::string, BinarySearchTree< std::string, List< std::string > > >& maps
)
{
  ScopeGuard guard(in);
  std::string nameDictionary;
  while (in)
  {
    std::string temp;
    in >> nameDictionary;
    std::string word;
    List< std::string > translate;
    BinarySearchTree< std::string, List< std::string > > translation;
    in >> std::noskipws;
    char space;
    in >> space;
    while (in && space != '\n')
    {
      in >> temp;
      if (isEnglish(temp) && word.empty())
      {
        word = temp;
      }
      else if (!isEnglish(temp) && !word.empty())
      {
        bool exists = false;
        for (auto it = translate.cbegin(); it != translate.cend(); ++it)
        {
          if (temp == *it)
          {
            exists = true;
            break;
          }
        }
        if (!exists)
        {
          translate.push_back(temp);
        }
      }
      else if (!word.empty() && !translate.empty())
      {
        if (translation.find(word) == translation.cend())
        {
          translation.push(word, translate);
        }
        word.clear();
        translate.clear();
        word = temp;
      }
      else
      {
        std::cout << "incorret(empty) input translate word: " << temp << " - the word is not written in the dictionary\n";
      }
      in >> space;
    }
    if (!word.empty() && !translate.empty())
    {
      if (translation.find(word) == translation.cend())
      {
        translation.push(word, translate);
      }
    }
    if (!in.eof())
    {
      in.clear();
    }
    if (!translation.empty() && !nameDictionary.empty())
    {
      maps.push(nameDictionary, translation);
    }
    else if (!nameDictionary.empty())
    {
      std::cout << "The dictionary is empty:" << nameDictionary << '\n';
    }
  }
}
