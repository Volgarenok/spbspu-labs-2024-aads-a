#include "data_processing.hpp"
namespace sakovskaia
{
  List< List< unsigned long long int > > processData(const List< std::pair< std::string, List< unsigned long long int > > > & sequences)
  {
    List< std::pair< CFwdIterator< unsigned long long int >, CFwdIterator< unsigned long long int > > > iters;
    for (const auto & seq : sequences)
    {
      iters.push_back(std::make_pair(seq.second.cbegin(), seq.second.cend()));
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
          current.push_back(*(it.first));
          ++(it.first);
          flag = true;
        }
      }
      if (!current.empty())
      {
        result.push_back(std::move(current));
      }
    }
    return result;
  }
}

sakovskaia::List< unsigned long long int > sakovskaia::calculateSums
(const sakovskaia::List< sakovskaia::List< unsigned long long int > > & data)
{
  List< unsigned long long > sums;
  size_t sum = 0;
  for (const auto & list : data)
  {
    for (auto it = list.begin(); it != list.end(); ++it)
    {
      if (std::numeric_limits< unsigned long long >::max() - sum < * it)
      {
        throw std::overflow_error("Can't calculate sum");
      }
      sum += * it;
    }
    sums.push_back(sum);
    sum = 0;
  }
  return sums;
}

namespace sakovskaia
{
  bool isEmpty(List< std::pair< std::string, ullList > >& sequences)
  {
    int check = 0;
    int size = 0;
    for (auto it = sequences.begin(); it != sequences.end(); ++it)
    {
      if(it->second.empty())
      {
        check++;
      }
      size++;
    }
    return size == check;
  }
}
