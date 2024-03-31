#include "pairsFunction.hpp"

size_t rebdev::inputNumbersList(std::istream & in, BiList< size_t >& numList)
{
  size_t num = 0, lenght = 0;

  while (in >> num)
  {
    std::cout << "num: " << num;
    numList.push_back(num);
    std::cout << " listNum: " << numList.back() << '\n';
    ++lenght;
  }
  in.clear();

  return lenght;
}
