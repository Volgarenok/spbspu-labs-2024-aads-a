#include "pairsFunction.hpp"

void rebdev::expandPairArr(std::pair < std::string, BiList < size_t > > * pairsArr, size_t numOfPairs)
{
  using pairs = std::pair < std::string, rebdev::BiList< size_t > >;
  pairs * newPairsArr = new pairs[numOfPairs + 1];

  for (size_t i = 0; i < numOfPairs; ++i)
  {
    newPairsArr[i] = pairsArr[i];
  }

  delete[] pairsArr;
  pairsArr = newPairsArr;
  newPairsArr = nullptr;
}

size_t rebdev::inputNumbersList(std::istream & in, BiList < size_t > & numList)
{
  size_t num = 0, lenght = 0;

  while (in >> num)
  {
    numList.push(num);
    ++lenght;
  }

  in.clear();

  return lenght;
}
