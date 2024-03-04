#include <limits>
#include "inputOutput.hpp"
#include "list.hpp"
int main()
{
  List<std::pair<std::string, List<size_t>>> list;
  input(std::cin, list);
  list.reverse();
  outputNames(list);

  bool allData = true;
  bool flag = false;
  size_t sum = 0;
  size_t counter = 0;
  List<size_t> numbers;
  while (allData)
  {
    allData = false;
    for (auto iteratorForPair = list.cbegin(); iteratorForPair != list.cend(); ++iteratorForPair)
    {
      auto iteratorForNums = iteratorForPair->second.cbegin();
      for (size_t i = 0; i < counter; ++i)
      {
        if (iteratorForNums != iteratorForPair->second.cend())
        {
          ++iteratorForNums;
        }
      }
      if (iteratorForNums != iteratorForPair->second.cend())
      {
        if (allData)
        {
          std::cout << " ";
        }
        if (std::numeric_limits<size_t>::max() - sum >= *iteratorForNums)
        {
          sum += *iteratorForNums;
        }
        else
        {
          flag = true;

        }
        std::cout << *iteratorForNums;
        allData = true;
      }
    }
    if (allData)
    {
      std::cout << "\n";
      numbers.push_front(sum);
      sum = 0;
    }
    ++counter;
  }

  if (flag == true)
  {
    std::cerr << "OverFlow\n";
    return 1;
  }

  if (numbers.empty())
  {
    std::cout << 0 << "\n";
    return 0;
  }
  numbers.reverse();
  outputSums(numbers);
  return 0;
}
