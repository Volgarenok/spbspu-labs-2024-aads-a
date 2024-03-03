#include <iostream>
#include <string>
#include <stdexcept>
#include "forward_list.hpp"
#include "forward_list_iterators.hpp"
#include "inputForwardList.hpp"
#include "outputForwardList.hpp"

int main()
{
  using namespace novokhatskiy;
  try
  {
    ForwardList< std::pair< std::string, ForwardList< size_t > > > pairsOfForwardList;
    inputForwardList(pairsOfForwardList, std::cin);
    outputForwardList(std::cout, pairsOfForwardList);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
