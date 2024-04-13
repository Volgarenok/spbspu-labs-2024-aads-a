#include <iostream>
#include "forward_list.hpp"
#include "iterators.hpp"
#include "const_iterators.hpp"
#include "node.hpp"
#include "input_output_lists.hpp"

int main()
{
  using namespace namestnikov;
  using pair_t = std::pair< std::string, ForwardList< unsigned long long > >;
  ForwardList< int > temp1({1, 2, 3});
  ForwardList< int > temp2({100, 200, 300});
  auto it = temp1.cbegin();
  ++it;
  temp1.splice_after(it, temp2);
  auto p = temp1.begin();
  auto q = temp2.begin();
  std::cout << temp1.max_size();
  for (; p != q; ++p)
  {
    std::cout << *p;
  }
  ForwardList< pair_t > dataList;
  try
  {
    inputLists(std::cin, dataList);
    outputLists(std::cout, dataList);
  }
  catch (const std::invalid_argument &)
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
