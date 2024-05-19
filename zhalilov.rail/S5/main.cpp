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
  std::cout << summator.result_;
  auto itCurr = summator.values_.cbegin();
  auto itEnd = summator.values_.cend();
  while (itCurr != itEnd)
  {
    std::cout << ' ' << *itCurr;
    itCurr++;
  }
}
