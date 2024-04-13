#include <iostream>
#include "forward_list.hpp"
#include "iterators.hpp"
#include "const_iterators.hpp"
#include "node.hpp"
#include "input_output_lists.hpp"

int main()
{
  using namespace namestnikov;
  using namedLists = std::pair< std::string, ForwardList< unsigned long long > >;
  ForwardList< namedLists > dataList;
  inputLists(std::cin, dataList);
  if (dataList.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  size_t maxSize = 0;
  outputNames(std::cout, dataList, maxSize);
  if (!haveNumbers(dataList))
  {
    std::cout << "0\n";
    return 0;
  }
  try
  {
    outputNumsAndSums(std::cout, dataList, maxSize);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
