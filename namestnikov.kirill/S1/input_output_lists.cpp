#include "input_output_lists.hpp"
#include <string>
#include <limits>
#include <iostream>

void namestnikov::inputLists(std::istream & in, ForwardList<pair_t> & dataList)
{
  std::string line = "";
  in >> line;
  while (in)
  {
    dataList.push_front({line, ForwardList<unsigned long long>{}});
    while ((in >> line) && (std::isdigit(line[0])))
    {
      unsigned long long number = std::stoull(line);
      dataList.front().second.push_front(number);
    }
  }
}

void namestnikov::outputLists(std::ostream & out, ForwardList<pair_t> & dataList)
{
  if (dataList.empty())
  {
    out << "0\n";
  }
  else
  {
    dataList.reverse();
    ForwardIterator<pair_t> fwdIt = dataList.begin();
    size_t maxSize = 0;
    for (; fwdIt != dataList.end(); ++fwdIt)
    {
      maxSize = std::max(maxSize, fwdIt->second.size());
      fwdIt->second.reverse();
      fwdIt != dataList.begin() ? out << " " << fwdIt->first : out << fwdIt->first;
    }
    out << "\n";
    ForwardList<unsigned long long> sumsList;
    unsigned long long sum = 0;
    const unsigned long long maxSum = std::numeric_limits<unsigned long long>::max();
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
          if (maxSum - sum < number)
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
}
