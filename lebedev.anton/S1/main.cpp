#include <iostream>
#include "io_datastruct.hpp"
#include "list.hpp"

int main()
{
  using namespace lebedev;
  listOfPairs list_of_pairs;
  inputDS(std::cin, list_of_pairs);
  if (list_of_pairs.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  outputPairsNames(std::cout, list_of_pairs);
  std::cout << '\n';

  return 0;
}
