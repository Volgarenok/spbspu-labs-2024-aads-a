#ifndef CLA_HPP
#define CLA_HPP
#include <iostream>
#include <tree/tree.hpp>
#include <string>

namespace baranov
{
  using dict_t = Tree< std::string, size_t >;
  void printHelp(std::ostream & out);
  void checkDictFile(char * argv[], std::ostream & out);
  void loadDict(const std::string & fileName, Tree< std::string, dict_t > & dicts);
  void createDict(char * argv[], std::ostream &);
  void readDict(const std::string & fileName, std::string & dictName, dict_t & dict);
}

#endif

