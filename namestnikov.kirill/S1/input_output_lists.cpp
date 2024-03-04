#include "input_output_lists.hpp"
#include <string>
#include <limits>
#include <iostream>

void namestnikov::inputLists(std::istream & in, ForwardList<pair_t> & dataList)
{
  std::string listParameters = "";
  in >> listParameters;
  while (in)
  {
    dataList.push_front({listParameters, ForwardList<unsigned long long>{}});
    while ((in >> listParameters) && (std::isdigit(listParameters[0])))
    {
      unsigned long long number = std::stoull(listParameters);
      dataList.front().second.push_front(number);
    }
  }
}

void namestnikov::outputNames(std::ostream & out, ForwardList<pair_t> & dataList, size_t & maxSize)
{
  dataList.reverse();
  for (ForwardIterator<pair_t> fwdIt = dataList.begin(); fwdIt != dataList.end(); ++fwdIt)
  {
    maxSize = std::max(maxSize, fwdIt->second.size());
    fwdIt->second.reverse();
    fwdIt != dataList.begin() ? out << " " << fwdIt->first : out << fwdIt->first;
  }
  out << "\n";
}

void namestnikov::outputNumsAndSums(std::ostream & out, ForwardList<pair_t> & dataList, size_t maxSize)
{
  ForwardList<unsigned long long> sumsList;
  unsigned long long sum = 0;
  const unsigned long long MAX_SUM = std::numeric_limits<unsigned long long>::max();
  for (size_t i = 0; i < maxSize; ++i)
  {
    for (auto it = dataList.begin(); it != dataList.end(); ++it)
    {
      ForwardIterator<unsigned long long> numIt = it->second.begin();
      size_t currentListSize = it->second.size();
      if (i < currentListSize)
      {
        unsigned long long number = *(numIt.advance(i));
        sum != 0 ? out << " " << number : out << number;
        if (MAX_SUM - sum < number)
        {
          throw std::logic_error("Can not find a sum");
        }
        sum += number;
      }
    }
    if (sum != 0)
    {
      out << "\n";
    }
    sumsList.push_front(sum);
    sum = 0;
  }
  sumsList.reverse();
  for (ForwardIterator<unsigned long long> sumIt = sumsList.begin(); sumIt != sumsList.end(); ++sumIt)
  {
    sumIt != sumsList.begin() ? out << " " << *sumIt : out << *sumIt;
  }
  out << "\n";
}

void namestnikov::outputLists(std::ostream & out, ForwardList<pair_t> & dataList)
{
  if (dataList.empty())
  {
    out << "0\n";
  }
  else
  {
    size_t maxSize = 0;
    outputNames(out, dataList, maxSize);
    outputNumsAndSums(out, dataList, maxSize);
  }
}
