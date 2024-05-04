#include <fstream>
#include <iosfwd>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <string>

using mainMap = std::map< std::string, std::map< size_t, std::string > >;
using map = std::map< size_t, std::string >;

void unionCmd(mainMap& dict, std::istream& in, std::ostream&)
{
  std::string resName = {};
  std::string first = {};
  std::string second = {};
  in >> resName >> first >> second;
  map resDict;
  map& dict1 = dict.at(first);
  map& dict2 = dict.at(second);
  auto begin1 = dict1.cbegin();
  auto end1 = dict1.cend();

  while (begin1 != end1)
  {
    resDict.insert({ begin1->first, begin1->second });
    begin1++;
  }

  auto begin2 = dict2.cbegin();
  auto end2 = dict2.cend();
  while (begin2 != end2)
  {
    resDict.insert({ begin2->first, begin2->second });
    begin2++;
  }
  dict.insert({ resName, resDict });
}

void intersectCmd(mainMap& dict, std::istream& in, std::ostream&)
{
  std::string resName = {};
  std::string first = {};
  std::string second = {};
  in >> resName >> first >> second;
  map resDict;
  map& dict1 = dict.at(first);
  map& dict2 = dict.at(second);
  auto begin = dict1.cbegin();
  auto end = dict1.cend();
  while (begin != end)
  {
    if (dict2.find(begin->first) != dict2.cend())
    {
      resDict.insert(*begin);
    }
    begin++;
  }
  if (dict.find(resName) != dict.cend())
  {
    dict.at(resName).clear();
    dict.at(resName) = std::move(resDict);
  }
  else
  {
    dict.insert({ resName, resDict });
  }
}

void complement(mainMap& dict, std::istream& in, std::ostream&)
{
  std::string resName = {};
  std::string first = {};
  std::string second = {};
  in >> resName >> first >> second;
  map resDict;
  map& dict1 = dict.at(first);
  map& dict2 = dict.at(second);

  auto begin = dict1.cbegin();
  auto end = dict1.cend();
  while (begin != end)
  {
    if (dict2.find(begin->first) == dict2.cend())
    {
      resDict.insert(*begin);
    }
    begin++;
  }
  begin = dict2.cbegin();
  end = dict2.cend();
  while (begin != end)
  {
    if (dict1.find(begin->first) == dict1.cend())
    {
      resDict.insert(*begin);
    }
    begin++;
  }
  if (dict.find(resName) != dict.cend())
  {
    dict.at(resName).clear();
    dict.at(resName) = std::move(resDict);
  }
  else
  {
    dict.insert({ resName, resDict });
  }
}
/*auto dict2Iter = dict2.cbegin();
for (auto i = dict1.cbegin(); i != dict1.cend(); i++)
{
  for (auto j = dict2.cbegin(); j != dict2.cend(); j++)
  {
    if (i->first != j->first)
    {
      resDict.insert({ i->first, i->second });
    }
  }
}
dict.insert({ resName, resDict });*/


void print(mainMap& dict, std::istream& in, std::ostream& out)
{
  std::string nameOfDict = {};
  in >> nameOfDict;
  std::map< size_t, std::string > tmp = dict.at(nameOfDict);
  if (tmp.empty())
  {
    throw std::invalid_argument("<EMPTY>");
  }
  //std::sort(tmp.cbegin(), tmp.cend());
  /*for (const auto& val: dict)
  {
    for (const auto& val2 : val.second)
    {
      out << val2.first << ' ' << val2.second;
    }
    out << '\n';
  }
  out << "DIFFERENT LOPES\n";*/
  out << nameOfDict;
  for (auto i = tmp.cbegin(); i != tmp.cend(); i++)
  {
    out << ' ' << (*i).first << ' ' << (*i).second;
  }
  out << '\n';
}

void inputDict(mainMap& dict, std::istream& in)
{
  while (!in.eof())
  {
    in.clear();
    std::string name = {};
    in >> name;
    std::map< size_t, std::string> tmp;
    size_t key = {};
    while (in >> key)
    {
      std::string val = {};
      in >> val;
      tmp.insert({ key, val });
    }
    dict.insert({ name, tmp });
  }
  in.clear();
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Wrong input file\n";
    return 1;
  }
  std::fstream fileinp(argv[1]);
  std::map< std::string, std::map< size_t, std::string > > maps;
  inputDict(maps, fileinp);
  //unionCmd(maps, std::cin, std::cout);
  complement(maps, std::cin, std::cout);
  print(maps, std::cin, std::cout);
  //print(maps, std::cin, std::cout);
}
