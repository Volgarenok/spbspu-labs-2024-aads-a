#include "data_processing.hpp"
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

sakovskaia::List< unsigned long long int > sakovskaia::calculateSums(const sakovskaia::List< sakovskaia::List< unsigned long long int > > & data)
{
  sakovskaia::List< unsigned long long int > sums;
  try
  {
    for (const auto & list : data)
    {
      unsigned long long sum = 0;
      for (const auto & value : list)
      {
        if (sum + value < sum)
        {
          throw std::overflow_error("Overflow during summation");
        }
        sum += value;
      }
      sums.push_front(sum);
    }
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    throw;
  }
    return sums;
}
