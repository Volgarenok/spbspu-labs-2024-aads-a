#include <iostream>
#include "lists_i_o.hpp"

int main()
{
  using namespace zaitsev;

  ForwardList< named_ullList > list;
  try
  {
    input_lists(list);
  }
  catch (const std::underflow_error&)
  {
    return 0;
  }
  list.reverse();

  ullList sums(print_lists(list));
  if (sums.empty())
  {
    std::cerr << "Sequence sum cannot be calculated due to variable overflow\n";
    return 1;
  }
  print_sums(std::cout, sums) << '\n';
  return 0;
}
