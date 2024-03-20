#include <iostream>
#include "list.hpp"
#include "inputlist.hpp"
#include "output.hpp"

int main()
{
  using namespace piyavkin;
  List< std::pair< std::string, List< unsigned long long > > > list;
  try
  {
    inputList(std::cin, list);
    output(std::cout, pairs, size, max_size_list);
  }
  catch (const std::invalid_argument& e)
  {
    std::cout << 0 << '\n';
    return 0;
  }
  catch (const std::logic_error& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  std::cout << '\n';
}
