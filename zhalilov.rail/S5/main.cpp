#include <fstream>
#include <iostream>
#include <cstring>

#include <tree/twoThreeTree.hpp>

#include "summator.hpp"

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Incorrect args";
  }

  using namespace zhalilov;
  int key = 0;
  std::string value;
  TwoThree < int, std::string > map;
  std::ifstream file(argv[2]);
  while (file >> key >> value)
  {
    map[key] = value;
  }

  Summator summator;
  if (std::strcmp(argv[1], "ascending") == 0)
  {
    summator = map.traverse_lnr(summator);
  }
  else if (std::strcmp(argv[1], "descending") == 0)
  {
    summator = map.traverse_rnl(summator);
  }
  else if (std::strcmp(argv[1], "breadth"))
  {
    summator = map.traverse_breadth(summator);
  }
  std::cout << summator.result_;
  std::cout << summator.values_;
}
