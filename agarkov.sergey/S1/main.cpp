#include <iostream>
#include <string>
#include <stdexcept>
#include "inputfunc.hpp"
#include "outputfunc.hpp"
#include "forwardlist.hpp"


int main()
{
  try
  {
    agarkov::ForwardList<std::pair<std::string, agarkov::ForwardList<size_t>>> lists = agarkov::inputLists(std::cin);
    agarkov::outputName(std::cout, lists);
    agarkov::outputNum(std::cout, lists);
    agarkov::outputSum(std::cout, lists);

    return 0;
  }
  catch (const std::logic_error& e)
  {
    std::cout << 0 << '\n';
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 0;
  }
}