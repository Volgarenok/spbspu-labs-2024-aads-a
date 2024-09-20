#ifndef CMDS_HPP
#define CMDS_HPP

#include <string>
#include <iostream>
#include <UBST.hpp>

namespace skuratov
{
  void isPrint(std::istream& in, UBST< std::string, UBST< int, std::string > >& dictionary, std::ostream& out);
  void isComplement(std::istream& in, UBST< std::string, UBST< int, std::string > >& dictionary);
  void isIntersect(std::istream& in, UBST< std::string, UBST< int, std::string > >& dictionary);
  void isUnion(std::istream& in, UBST< std::string, UBST< int, std::string > >& dictionary);
}

#endif
