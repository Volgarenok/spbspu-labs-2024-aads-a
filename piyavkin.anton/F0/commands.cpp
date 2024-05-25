#include "commands.hpp"

void piyavkin::print(std::ostream& out, const std::string& nameDict, const dic_t& dicts)
{
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