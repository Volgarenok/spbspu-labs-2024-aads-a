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
    return 1;
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
  try
  {
    if (std::strcmp(argv[1], "ascending") == 0)
    {
      summator = map.traverse_lnr(summator);
    }
    else if (std::strcmp(argv[1], "descending") == 0)
    {
      summator = map.traverse_rnl(summator);
    }
    else if (std::strcmp(argv[1], "breadth") == 0)
    {
      summator = map.traverse_breadth(summator);
    }
    else
    {
      std::cerr << "Incorrect traverse arg";
      return 1;
    }
  }
  catch (const std::logic_error &e)
  {
    std::cerr << "<EMPTY>";
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what();
    return 1;
  }
  std::cout << summator.result_;
  std::cout << summator.values_;
  std::cout << '\n';
}
