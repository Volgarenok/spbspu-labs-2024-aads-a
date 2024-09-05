#include <iostream>
#include <string>
#include <list.hpp>
#include "input_list.hpp"
#include "output_list.hpp"

int main()
{
  using namespace nikitov;
  try
  {
    List< std::pair< std::string, List< size_t > > > pairsList;
    inputList(pairsList, std::cin);
    if (pairsList.empty())
    {
      throw std::invalid_argument("Error: Empty list");
    }

    size_t maxSize = 1;
    outputSequenceNames(pairsList, maxSize, std::cout);
    std::cout << '\n';

    List< size_t > sumsList;
    bool isOverflow = outputSequences(pairsList, sumsList, maxSize, std::cout);
    if (isOverflow)
    {
      throw std::out_of_range("Error: Sum is out of range");
    }

    outputSums(sumsList, std::cout);
    std::cout << '\n';
  }
  catch (const std::invalid_argument& e)
  {
    std::cout << 0 << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}
