#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>

int main(int argc, char ** argv)
{
  std::vector<int> ints;
  if (argc == 1)
  {
    std::copy(
        std::istream_iterator<int>{std::cin},
        std::istream_iterator<int>{},
        std::back_inserter(ints)
      );
      if (!std::cin && !std::cin.eof())
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
  }
  else if (argc == 2)
  {
    std::ifstream input(argv[1]);
    while (!input.eof())
    {
      std::copy(
        std::istream_iterator<int>{input},
        std::istream_iterator<int>{},
        std::back_inserter(ints)
      );
      if (!input && !input.eof())
      {
        input.clear();
        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
  }
  for (auto i = ints.begin(); i != ints.end(); ++i)
  {
    std::cout << *i << '\n';
  }
}
