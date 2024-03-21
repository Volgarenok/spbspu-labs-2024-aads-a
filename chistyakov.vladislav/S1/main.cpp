#include <iostream>
#include <limits>
#include "list.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"
#include "inputList.hpp"

int main()
{
  using namespace chistyakov;
  List< std::pair< std::string, List< int > > > list;

  try
  {
    inputList(std::cin, list);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
  }

  if (list.empty())
  {
    return 0;
  }

  for (auto element = list.begin(); element != list.end(); ++element)
  {
    std::cout << element->first;
    auto next = element;
    if (++next != list.end())
    {
      std::cout << " ";
    }
  }

}
