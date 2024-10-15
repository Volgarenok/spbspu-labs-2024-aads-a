#include <iostream>
#include <string>
#include <stdexcept>
#include "inputfunc.hpp"
#include "forwardlist.hpp"

int main()
{
  try
  {
    agarkov::ForwardList<std::pair<std::string, agarkov::ForwardList<size_t>>> lists = agarkov::inputLists(std::cin);
    std::cout << "final\n";
    for (auto iter = lists.cbegin(); iter != lists.cend(); ++iter)
    {
      std::cout << (*iter).first << ' ';
      
      for (auto num_iter = (*iter).second.cbegin(); num_iter != (*iter).second.cend(); ++num_iter)
      {
        std::cout << *num_iter << ' ';
      }     
      std::cout << '\n';
    }
  return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
}
