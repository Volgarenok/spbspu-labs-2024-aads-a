#include <iostream>
#include "list.hpp"
#include "inputlist.hpp"
#include "output.hpp"

int main()
{
  using namespace piyavkin;
  size_t size = 0;
  size_t max_size_list = 0;
  std::pair< std::string, piyavkin::List< unsigned int >* >* pairs = nullptr;
  try
  {
    pairs = inputList(std::cin, size, max_size_list);
    output(std::cout, pairs, size, max_size_list);
  }
  catch (const std::logic_error& e)
  {
    std::cout << 0 << '\n';
    delete[] pairs;
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  std::cout << '\n';
  for (size_t i = 0; i < size; ++i)
  {
    delete pairs[i].second;
  }
  delete[] pairs;
}
