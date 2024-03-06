#include "input.hpp"

int main()
{
  using namespace marishin;
  LinkedList< std::pair< std::string, LinkedList< size_t >>> pairs;
  LinkedList< size_t > lst;
  bool overflow = false;

  try
  {
    readInput(pairs);
    printPairs(pairs);
    calculateSums(pairs, overflow, lst);
    printResults(lst, overflow);
  }
  catch (std::bad_alloc& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
}
