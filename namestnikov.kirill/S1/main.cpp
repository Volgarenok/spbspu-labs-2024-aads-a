#include <iostream>
#include "forward_list.hpp"
#include "iterators.hpp"
#include "node.hpp"
#include "input_output_lists.hpp"

int main()
{
  using namespace namestnikov;
  ForwardList<pair_t> list;
  inputLists(std::cin, list);
  outputLists(std::cout, list);
}
