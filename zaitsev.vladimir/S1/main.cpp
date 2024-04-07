#include <iostream>
#include "forward_list.hpp"
#include "lists_i_o.hpp"

int main()
{
  using namespace zaitsev;

  named_ullList list;
  try
  {
    input_lists(list);
  }
  catch (const std::underflow_error&)
  {
    return 0;
  }
  list.reverse();

  ullList* sums = nullptr;
  sums = print_lists(list);

  if (!sums)
  {
    std::cerr << "Sequence sum cannot be calculated due to variable overflow\n";
    return 1;
  }
  print_sums(*sums);
  delete sums;
  return 0;
}
