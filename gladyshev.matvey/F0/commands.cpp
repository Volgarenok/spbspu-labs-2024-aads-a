#include "commands.hpp"

#include <iostream>

namespace gladyshev
{
  template< typename Function >
  void unionCmds(mainDic& dictionaries, std::istream& in, Function func)
   {
    dic result;
    std::string s = "";
    in >> s;
    std::string name1 = "";
    std::string name2 = "";
    in >> name1 >> name2;
    result = func(dictionaries.at(name1), dictionaries.at(name2));
    while (in)
    {
      if (in.get() == '\n')
      {
        break;
      }
      in >> name1;
      result = func(result, dictionaries.at(name1));
    }
    if (result.empty())
    {
      throw std::logic_error("RESULT OF OPERATION IS EMPTY");
    }
    dictionaries.insert(s, result);
  }
}
void gladyshev::print_dictionary(const dic& dictionary, std::ostream& out)
{
  for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
  {
    out << " " << it->second << " " << it->first;
  }
  out << "\n";
}
void gladyshev::print_dictionaryL(const dic& dictionary, int n, std::ostream& out)
{
  for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
  {
    if (it->second > n)
    {
      out << " " << it->second << " " << it->first;
    }
  }
  out << "\n";
}
void gladyshev::addelem(mainDic& dictionaries, std::istream& in)
{
  std::string datasetName = "";
  std::string key = "";
  size_t value = 0;
  in >> datasetName >> key >> value;
  auto it = dictionaries.find(datasetName);
  if (it == dictionaries.end())
  {
    throw std::logic_error("NO MATCHES");
  }
  it->second.insert(key, value);
}
void gladyshev::save(const mainDic& dictionaries, std::istream& in)
{
  std::string datasetName = "";
  std::string fileName = "";
  in >> datasetName >> fileName;
  std::ofstream outFile(fileName, std::ios::trunc);
  auto it = dictionaries.find(datasetName);
  outFile << datasetName;
  for (auto itr = it->second.cbegin(); itr != it->second.cend(); ++itr)
  {
    outFile << " " << itr->first << " " << itr->second;
  }
  outFile << "\n";
}
void gladyshev::intersect(mainDic& dictionaries, std::istream& in)
{
  unionCmds(dictionaries, in, intersectImpl);
}
void gladyshev::addition(mainDic& dictionaries, std::istream& in)
{
  unionCmds(dictionaries, in, additionImpl);
}
void gladyshev::complement(mainDic& dictionaries, std::istream& in)
{
  unionCmds(dictionaries, in, complementImpl);
}
gladyshev::dic gladyshev::intersectImpl(const dic& dict1, const dic& dict2)
{
  dic result;
  for (auto it1 = dict1.cbegin(); it1 != dict1.cend(); ++it1)
  {
    for (auto it2 = dict2.cbegin(); it2 != dict2.cend(); ++it2)
    {
      if (it1->first == it2->first)
      {
        result.insert(it1->first, std::min(it1->second, it2->second));
      }
    }
  }
  return result;
}
void gladyshev::printInfo(std::ostream& out)
{
  out << "printdict <dataset> - display a dictionary with the corresponding name\n";
  out << "makedict <newdataset> <text> create a dictionary based on text from a file\n";
  out << "makedict <newdataset> <text> <number> create a dictionary based on text from a file with length number\n";
  out << "printgreater <dataset> <number> display all dictionary words that appear more than number times\n";
  out << "save <newdataset> <filename> save the dictionary to a file\n";
  out << "addelem <dataset> <key> <value> add an element to the specified dictionary\n";
  out << "delete <newdataset> delete dictionary with the corresponding name\n";
  out << "delete <newdataset> <key> delete an element with the corresponding key\n";
  out << "addition <newdataset> <dataset1> <dataset2> … <datasetn> combine an unlimited number of dictionaries\n";
  out << "intersect <newdataset> <dataset1> <dataset2> … <datasetn> intersect unlimited number of dictionaries\n";
  out << "complement <newdataset> <dataset1> <dataset2> … <datasetn> subtracts all dictionaries from the first one\n";
}
gladyshev::dic gladyshev::additionImpl(const dic& dict1, const dic& dict2)
{
  dic result = dict1;
  for (auto it2 = dict2.cbegin(); it2 != dict2.cend(); ++it2)
  {
    result.insert(it2->first, it2->second);
  }
  for (auto it1 = dict1.cbegin(); it1 != dict1.cend(); ++it1)
  {
    for (auto it2 = dict2.cbegin(); it2 != dict2.cend(); ++it2)
    {
      if (it1->first == it2->first)
      {
        result.erase(it1->first);
        result.insert(it1->first, it1->second + it2->second);
      }
    }
  }
  return result;
}

gladyshev::dic gladyshev::complementImpl(const dic& dict1, const dic& dict2)
{
  dic result = dict1;
  for (auto it1 = dict1.cbegin(); it1 != dict1.cend(); ++it1)
  {
    for (auto it2 = dict2.cbegin(); it2 != dict2.cend(); ++it2)
    {
      if (it1->first == it2->first)
      {
        if (it1->second - it2->second > 0)
        {
          result.insert(it1->first, it1->second - it2->second);
        }
        else
        {
          result.erase(it1->first);
        }
      }
    }
  }
  return result;
}

void gladyshev::deleteDict(mainDic& dictionaries, std::istream& in)
{
  std::string datasetName = "";
  in >> datasetName;
  auto it = dictionaries.find(datasetName);
  if (it == dictionaries.end())
  {
    throw std::logic_error("NO MATCHES");
  }
  dictionaries.erase(datasetName);
}
void gladyshev::deleteName(mainDic& dictionaries, std::istream& in)
{
  std::string datasetName = "";
  std::string name = "";
  in >> datasetName >> name;
  auto it = dictionaries.find(datasetName);
  if (it == dictionaries.end())
  {
    throw std::logic_error("NO MATCHES");
  }
  it->second.erase(name);
}
void gladyshev::print_dictionaries(const mainDic& dictionaries, std::istream& in, std::ostream& out)
{
  std::string s = "";
  in >> s;
  for (auto it = dictionaries.cbegin(); it != dictionaries.cend(); ++it)
  {
    if (s == it->first)
    {
      if (it->second.empty())
      {
        throw std::overflow_error("<EMPTY>");
      }
      out << it->first;
      print_dictionary(it->second, out);
    }
  }
}
void gladyshev::print_dictionariesL(const mainDic& dictionaries, std::istream& in, std::ostream& out)
{
  size_t n = 0;
  std::string s = "";
  in >> s >> n;
  for (auto it = dictionaries.cbegin(); it != dictionaries.cend(); ++it)
  {
    if (s == it->first)
    {
      if (it->second.empty())
      {
        throw std::overflow_error("<NO MATCHES>");
      }
      out << it->first;
      print_dictionaryL(it->second, n, out);
    }
  }
}
