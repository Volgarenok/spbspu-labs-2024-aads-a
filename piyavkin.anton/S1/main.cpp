#include <iostream>
#include "list.hpp"
#include "inputlist.hpp"
#include "output.hpp"

int main()
{
  using namespace piyavkin;
  list_t list;
  try
  {
    inputList(std::cin, list);
    output(std::cout, list);
  }
  catch (const std::invalid_argument& e)
  {
    std::cout << 0 << '\n';
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  std::cout << '\n';
}
