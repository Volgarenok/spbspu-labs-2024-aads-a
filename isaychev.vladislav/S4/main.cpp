#include <iostream>
#include <fstream>
#include <string>
#include "tree.hpp"

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

using subDict = isaychev::BSTree< int, std::string >;

void inputDictionaries(std::istream & in, isaychev::BSTree< std::string, subDict > & dicts)
{
  //subDict dictionary;
  std::string name;
  int key = 0;
  std::string value;

  in >> std::noskipws;
  while (!in.eof())
  {
    in >> name;
    char c = 0;
    in >> c;
    do
    {
      in >> key >> c >> value >> c;
      dicts[name][key] = value;
    }
    while (c != '\n');
  }
}

int main(int argc, char * argv[])
{
  using namespace isaychev;
  BSTree< int, std::string > dict;
  std::ifstream in;
  if (argc != 2)
  {
    std::cerr << "troubles with filename\n";
    return 1;
  }
  else
  {
    in.open((argv[1]));
  }
  BSTree< std::string, BSTree< int, std::string > > dictionaries;
}
