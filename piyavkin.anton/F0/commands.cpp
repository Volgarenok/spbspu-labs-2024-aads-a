#include "commands.hpp"

void piyavkin::print(std::istream& in, std::ostream& out, const dic_t& dicts)
{
  std::string nameDict = "";
  in >> nameDict;
  auto it = dicts.find(nameDict);
  if (it != dicts.cend())
  {
    out << nameDict << '\n';
    if (!dicts.empty())
    {
      Tree< std::string, size_t > dict = it->second;
      for (auto dictIt = dict.cbegin(); dictIt != dict.cend(); ++dictIt)
      {
        out << dictIt->first << ' ' << dictIt->second;
      }
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