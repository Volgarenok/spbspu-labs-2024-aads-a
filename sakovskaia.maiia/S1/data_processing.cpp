#include "data_processing.hpp"
#include <limits.h>
namespace sakovskaia
{
  List< List< unsigned long long int > > processData(const List< std::pair< std::string, List< unsigned long long int > > > & sequences)
  {
    List< std::pair< CFwdIterator< unsigned long long int >, CFwdIterator< unsigned long long int > > > iters;
    for (const auto & seq : sequences)
    {
      iters.push_front(std::make_pair(seq.second.cbegin(), seq.second.cend()));
    }
    List< List< unsigned long long int > > result;
    bool flag = true;
    while (flag)
    {
      flag = false;
      List< unsigned long long int > current;
      for (auto & it : iters)
      {
        if (it.first != it.second)
        {
          current.push_front(*(it.first));
          ++(it.first);
          flag = true;
        }
      }
      if (!current.empty())
      {
        result.push_front(std::move(current));
      }
    }
    return result;
  }
}

sakovskaia::List< unsigned long long int > sakovskaia::calculateSums(const List< ullList > & processedData)
{
  List< unsigned long long int > result;

  for (const auto & list : processedData)
  {
    unsigned long long int sum = 0;
    for (const auto & num : list)
    {
      if (ULLONG_MAX - num < sum)
      {
        throw std::overflow_error("Overflow during summation");
      }
      sum += num;
    }
    result.push_front(sum);
  }
  return result;
}
