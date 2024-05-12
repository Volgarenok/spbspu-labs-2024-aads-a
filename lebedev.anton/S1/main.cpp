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

  std::cout << list_of_pairs.front().first << "\n";
  list_of_pairs.front().second.outputList(std::cout);

  return 0;
}
