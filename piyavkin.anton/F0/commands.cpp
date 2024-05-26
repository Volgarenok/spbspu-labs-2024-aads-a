#include "commands.hpp"
#include <fstream>

piyavkin::iterator getDict(std::istream& in, piyavkin::dic_t dicts)
{
  std::string name = "";
  in >> name;
  piyavkin::iterator it = dicts.find(name);
  if (it == dicts.end())
  {
    throw std::out_of_range("");
  }
  return it;
}

void change(std::istream& in, piyavkin::Tree< std::string, size_t >& dic)
{
  size_t val = 0;
  std::string key = "";
  in >> key >> val;
  auto dicIt = dic.find(key);
  if (dicIt != dic.end())
  {
    dic.erase(key);
  }
  dic.insert(std::pair< std::string, size_t >(key, val));
}

void piyavkin::print(std::istream& in, std::ostream& out, const dic_t& dicts)
{
  std::string nameDict = "";
  in >> nameDict;
  auto it = dicts.find(nameDict);
  if (it != dicts.cend())
  {
    out << nameDict << '\n';
    Tree< std::string, size_t > dict = it->second;
    for (auto dictIt = dict.cbegin(); dictIt != dict.cend(); ++dictIt)
    {
      out << dictIt->first << ' ' << dictIt->second << '\n';
    }
  }
  else
  {
    throw std::out_of_range("");
  }
}

piyavkin::iterator piyavkin::addDict(std::istream& in, dic_t& dicts)
{
  std::string name = "";
  in >> name;
  if (dicts.find(name) != dicts.end())
  {
    throw std::out_of_range("");
  }
  return dicts.insert(std::make_pair(name, Tree< std::string, size_t >())).first;
}

piyavkin::iterator piyavkin::cmdChange(std::istream& in, dic_t& dicts)
{
  auto it = getDict(in, dicts);
  change(in, it->second);
  return it;
}

piyavkin::iterator piyavkin::makeDict(std::istream& in, dic_t& dicts)
{
  auto it = addDict(in, dicts);
  std::string nameFile = "";
  in >> nameFile;
  std::ifstream file(nameFile);
  while (file)
  {
    change(file, it->second);
  }
  return it;
}