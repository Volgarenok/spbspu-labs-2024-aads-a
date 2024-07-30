#include <iostream>
#include <fstream>
#include <string>
#include "commands.hpp"

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

/*void inputDictionaries(std::istream & in, isaychev::BSTree< std::string, isaychev::dataset > & dicts)
{
  std::string name;
  int key = 0;
  std::string value;

  while (!in.eof())
  {
    in >> name;
//    if (name.empty())
    {
      continue;
    }
  //  dicts[name] = isaychev::dataset();  insert
    while (in >> key >> value);
    {
   //   dicts.at(name)[key] = value;
    }
    in.clear();
  }
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
  //  inputDictionaries(in, dictionaries);
    in.close();
  }
  std::cout << dictionaries.size() << "\n";
}
