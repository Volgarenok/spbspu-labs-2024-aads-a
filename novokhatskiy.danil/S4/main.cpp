#include <fstream>
#include <iosfwd>
#include <iostream>
#include <list>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <string>

using mainMap = std::map< std::string, std::map< size_t, std::string > >;
using map = std::map< size_t, std::string >;

void complement(mainMap dict, std::istream& in)
{
  std::string resName = {};
  std::string first = {};
  std::string second = {};
  in >> resName >> first >> second;
  map resDict;
  map dict1 = dict.at(first);
  map dict2 = dict.at(second);
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
  for (const auto& val: dict)
  {
    for (const auto& val2 : val.second)
    {
      out << val2.first << ' ' << val2.second << '\n';
    }
  }
  out << "DIFFERENT LOPES\n";
  out << nameOfDict;
  for (auto i = tmp.cbegin(); i != tmp.cend(); i++)
  {
    out << (*i).first << ' ' << (*i).second << '\n';
  }
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
}

int main(int argc, char** argv)
{
  /*if (argc != 2)
  {
    std::cerr << "Wrong input file\n";
    return 1;
  }*/
  //std::fstream fileinp(argv[1]);
  std::map< std::string, std::map< size_t, std::string > > maps;
  inputDict(maps, std::cin);
  print(maps, std::cin, std::cout);
}
