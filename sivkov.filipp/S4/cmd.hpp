#ifndef CMD_HPP
#define CMD_HPP

#include <map>
#include <string>

namespace sivkov
{
  void print(std::map< std::string, std::map< size_t, std::string > >& treeOfdic, std::istream& in, std::ostream& out);
  void complement(std::map<std::string, std::map<size_t, std::string>>& treeOfdic, std::istream& in);
  void intersect(std::map<std::string, std::map<size_t, std::string>>& treeOfdic, std::istream& in);
  void uni(std::map<std::string, std::map<size_t, std::string>>& treeOfdic, std::istream& in);
}
#endif
