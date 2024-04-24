#include <iostream>
#include <fstream>
#include <list.hpp>
#include "tree.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "File entered incorrectly\n";
    return 1;
  }
  using namespace piyavkin;
  List< Tree< int, std::string > > list;
  std::ifstream in(argv[1]);
  // inputFile(in);
}