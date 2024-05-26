#include "commands.hpp"

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
      out << dictIt->first << ' ' << dictIt->second;
    }
  }
  else
  {
    throw std::out_of_range("");
  }
}

void piyavkin::addDict(std::istream& in, dic_t& dicts)
{
  std::string name = "";
  in >> name;
  if (dicts.find(name) != dicts.end())
  {
    throw std::out_of_range("");
  }
  dicts.insert(std::make_pair(name, Tree< std::string, size_t >()));
}

void piyavkin::changeDict(std::istream& in, dic_t& dicts)
{
  std::string name = "";
  in >> name;
  auto it = dicts.find(name);
  if (it == dicts.end())
  {
    throw std::out_of_range("");
  }
  size_t val = 0;
  std::string key = "";
  in >> key >> val;
  auto dicIt = it->second.find(key);
  if (dicIt != it->second.end())
  {
    it->second.erase(key);
  }
  it->second.insert(std::pair< std::string, size_t >(key, val));
}