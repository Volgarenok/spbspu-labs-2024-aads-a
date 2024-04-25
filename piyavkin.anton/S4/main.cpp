#include <iostream>
#include <fstream>
#include "inputfile.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "File entered incorrectly\n";
    return 1;
  }
  using namespace piyavkin;
  map_t map;
  std::ifstream in(argv[1]);
  inputFile(in, map);
}