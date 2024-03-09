#include <iostream>
#include <stdexcept>
#include "outputResults.hpp"
#include "inputList.hpp"

int main()
{
  using namespace isaychev;
  using myPair = std::pair< std::string, List< unsigned long long int > >;
  List< myPair > mainList;
  try
  {
    inputList(std::cin, mainList);
    outputResults(std::cout, mainList);
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::out_of_range & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << "\n";
    return 0;
  }
}
