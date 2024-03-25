#include "pairsFunction.hpp"

rebdev::pairs * rebdev::expandPairArr(pairs * pairsArr, size_t numOfPairs)
{
  pairs * newPairsArr = new pairs[numOfPairs + 1];

  for (size_t i = 0; i < numOfPairs; ++i)
  {
    newPairsArr[i] = pairsArr[i];
  }

  delete[] pairsArr;
  pairsArr = newPairsArr;
  newPairsArr = nullptr;
  return pairsArr;
}

size_t rebdev::inputNumbersList(std::istream & in, BiList< size_t >* numList)
{
  size_t num = 0, lenght = 0;

  while (in >> num)
  {
    numList -> push_back(num);
    ++lenght;
  }
  in.clear();

  return lenght;
}
