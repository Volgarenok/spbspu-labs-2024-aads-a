#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <tree.hpp>

namespace sakovskaia
{
  void print(const Tree< std::string, Tree< size_t, std::string > > & dictionaries, std::istream & input, std::ostream & output);
  void complement(Tree< std::string, Tree< size_t, std::string > > & dictionaries, std::istream & input);
  void intersect(Tree< std::string, Tree< size_t, std::string > > & dictionaries, std::istream & input);
  void unionCMD(Tree< std::string, Tree< size_t, std::string > > & dictionaries, std::istream & input);
}

#endif
