#include <iostream>
#include "lists_i_o.hpp"

int main()
{
  using namespace zaitsev;

  ForwardList< named_ullList > list;
  input_lists(list);
  list.reverse();

  ullList sums(print_lists(std::cout, list));
  if (sums.empty())
  {
    std::cerr << "Sequence sum cannot be calculated due to variable overflow\n";
    return 1;
  }
  print_sums(std::cout, sums) << '\n';
  return 0;
}
