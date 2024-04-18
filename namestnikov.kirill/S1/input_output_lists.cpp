#include "input_output_lists.hpp"
#include <string>
#include <limits>
#include <iostream>

void namestnikov::inputLists(std::istream & in, ForwardList< namedLists > & dataList)
{
  std::string listParameters = "";
  in >> listParameters;
  while (in)
  {
    dataList.push_front({listParameters, ForwardList< unsigned long long >{}});
    while (in >> listParameters)
    {
      try
      {
        unsigned long long number = std::stoull(listParameters);
        dataList.front().second.push_front(number);
      }
      catch (const std::invalid_argument &)
      {
        dataList.push_front({listParameters, ForwardList< unsigned long long >{}});
      }
    }
  }
}

void namestnikov::outputNames(std::ostream & out, ForwardList< namedLists > & dataList, size_t & maxSize)
{
  dataList.reverse();
  for (ForwardIterator< namedLists > fwdIt = dataList.begin(); fwdIt != dataList.end(); ++fwdIt)
  {
    maxSize = std::max(maxSize, fwdIt->second.get_size());
    fwdIt->second.reverse();
    fwdIt != dataList.begin() ? out << " " << fwdIt->first : out << fwdIt->first;
  }
  out << "\n";
}

void namestnikov::outputNumsAndSums(std::ostream & out, const ForwardList< namedLists > & dataList, size_t maxSize)
{
  ForwardList< unsigned long long > sumsList;
  unsigned long long sum = 0;
  bool gotOverflow = false;
  const unsigned long long MAX_SUM = std::numeric_limits< unsigned long long >::max();
  for (size_t i = 0; i < maxSize; ++i)
  {
    for (auto it = dataList.begin(); it != dataList.end(); ++it)
    {
      ConstForwardIterator< unsigned long long > numIt = it->second.cbegin();
      size_t currentListSize = it->second.get_size();
      if (i < currentListSize)
      {
        std::advance(numIt, i);
        unsigned long long number = *numIt;
        sum != 0 ? out << " " << number : out << number;
        if (MAX_SUM - sum < number)
        {
          gotOverflow = true;
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
  if (gotOverflow)
  {
    throw std::overflow_error("The number is too big");
  }
  sumsList.reverse();
  for (ConstForwardIterator< unsigned long long > sumIt = sumsList.cbegin(); sumIt != sumsList.cend(); ++sumIt)
  {
    sumIt != sumsList.cbegin() ? out << " " << *sumIt : out << *sumIt;
  }
  out << "\n";
}

bool namestnikov::haveNumbers(const ForwardList< namedLists > & dataList)
{
  bool gotNumbers = false;
  for (auto it = dataList.cbegin(); it != dataList.cend(); ++it)
  {
    gotNumbers = gotNumbers || !(it->second.empty());
  }
  return gotNumbers;
}
