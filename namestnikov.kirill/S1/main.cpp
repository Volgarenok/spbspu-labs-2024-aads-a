#include <iostream>
#include "forward_list.hpp"
#include "iterators.hpp"
#include "const_iterators.hpp"
#include "node.hpp"
#include "input_output_lists.hpp"

int main()
{
  using namespace namestnikov;
  using pair_t = std::pair<std::string, ForwardList<unsigned long long>>;
  ForwardList<pair_t> dataList;
  try
  {
    inputLists(std::cin, dataList);
    outputLists(std::cout, dataList);
  }
  catch (std::invalid_argument &)
  {
    std::cout << "0\n";
    return 0;
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
