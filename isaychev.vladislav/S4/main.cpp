#include <iostream>
#include <fstream>
#include "commands.hpp"
#include "inputDictionaries.hpp"

/*struct DelimeterIO
{
  char expected;
}

std::istream & operator>>(std::istream & in, DelimeterIO && del)
{
  std::istream::sentry guard(in);
  char c = 0;
  in >> c;
  if (in || c != del.expected)
  {
    in.setstate(std::ios::failbit)
  }
  return in;
}*/


int main(int argc, char * argv[])
{
  using namespace isaychev;
  BSTree< std::string, BSTree< int, std::string > > dictionaries;
  if (argc != 2)
  {
    std::cerr << "troubles with filename\n";
    return 1;
  }
  else
  {
    std::ifstream in(argv[1]);
    inputDictionaries(in, dictionaries);
  }

  complement(std::string("third"), std::string("second"), std::string("first"), dictionaries);
  print(std::cout, std::string("third"), dictionaries);

  intersect(std::string("fourth"), std::string("first"), std::string("second"), dictionaries);
  print(std::cout, std::string("fourth"), dictionaries);
  intersect(std::string("yafourth"), std::string("second"), std::string("first"), dictionaries);
  print(std::cout, std::string("yafourth"), dictionaries);

  unite(std::string("fifth"), std::string("first"), std::string("second"), dictionaries);
  print(std::cout, std::string("fifth"), dictionaries);
  unite(std::string("yafifth"), std::string("second"), std::string("first"), dictionaries);
  print(std::cout, std::string("yafifth"), dictionaries);
}
