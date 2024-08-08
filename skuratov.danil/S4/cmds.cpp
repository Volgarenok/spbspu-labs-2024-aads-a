#include "cmds.hpp"

void skuratov::isPrint(std::istream& in, UBST< std::string, UBST< int, std::string > >& dictionary, std::ostream& out)
{
  std::string name = {};
  in >> name;
  try
  {
    UBST< int, std::string > dic = dictionary.at(name);
    if (dic.empty())
    {
      out << "<EMPTY>" << '\n';
    }
    else
    {
      out << name;
      for (auto key = dic.cbegin(); key != dic.cend(); ++key)
      {
        out << " " << key->first << " " << key->second;
      }
      out << "\n";
    }
  }
  catch (std::out_of_range&)
  {
    out << "<DICTIONARY NOT FOUND>" << '\n';
  }
}

void skuratov::isComplement(std::istream& in, UBST< std::string, UBST< int, std::string > >& dictionary)
{
  std::string newDataset, dataset1, dataset2;
  in >> newDataset >> dataset1 >> dataset2;

  try
  {
    UBST< int, std::string > dict1 = dictionary.at(dataset1);
    UBST< int, std::string > dict2 = dictionary.at(dataset2);

    UBST< int, std::string > complementDict;
    for (auto it = dict1.cbegin(); it != dict1.cend(); ++it)
    {
      if (dict2.find(it->first) == dict2.cend())
      {
        complementDict.insert(it->first, it->second);
      }
    }
    dictionary.insert(newDataset, complementDict);
  }
  catch (std::out_of_range&)
  {
    std::cerr << "<DICTIONARY NOT FOUND>" << '\n';
  }
}

void skuratov::isIntersect(std::istream& in, UBST< std::string, UBST< int, std::string > >& dictionary)
{
  std::string newDataset, dataset1, dataset2;
  in >> newDataset >> dataset1 >> dataset2;

  try
  {
    UBST< int, std::string > dict1 = dictionary.at(dataset1);
    UBST< int, std::string > dict2 = dictionary.at(dataset2);

    UBST< int, std::string > intersectDict;
    for (auto it = dict1.cbegin(); it != dict1.cend(); ++it)
    {
      if (dict2.find(it->first) != dict2.cend())
      {
        intersectDict.insert(it->first, it->second);
      }
    }
    dictionary.insert(newDataset, intersectDict);
  }
  catch (std::out_of_range&)
  {
    std::cerr << "<DICTIONARY NOT FOUND>" << '\n';
  }
}

void skuratov::isUnion(std::istream& in, UBST< std::string, UBST< int, std::string > >& dictionary)
{
  std::string newDataset, dataset1, dataset2;
  in >> newDataset >> dataset1 >> dataset2;

  try
  {
    UBST< int, std::string > dict1 = dictionary.at(dataset1);
    UBST< int, std::string > dict2 = dictionary.at(dataset2);

    UBST< int, std::string > unionDict = dict1;

    for (auto it = dict2.cbegin(); it != dict2.cend(); ++it)
    {
      if (unionDict.find(it->first) == unionDict.cend())
      {
        unionDict.insert(it->first, it->second);
      }
    }
    dictionary.insert(newDataset, unionDict);
  }
  catch (std::out_of_range&)
  {
    std::cerr << "<DICTIONARY NOT FOUND>" << '\n';
  }
}
