#ifndef COMMANDS_PROCESSING_HPP
#define COMMANDS_PROCESSING_HPP
#include <iostream>
#include <string>
#include <map.hpp>

namespace zaitsev
{
  using dictionary = zaitsev::Map< int, std::string >;
  using ds_it = zaitsev::Map< int, std::string >::const_iterator;
  using library = zaitsev::Map< std::string, dictionary >;

  void initLib(int argc, char** argv, library& dest);
  void readDs(std::istream& in, library& dest);
  void printDs(std::istream& in, library& lib);
  void complementDs(std::istream& in, library& lib);
  void intersectDs(std::istream& in, library& lib);
  void uniteDs(std::istream& in, library& lib);
}
#endif
