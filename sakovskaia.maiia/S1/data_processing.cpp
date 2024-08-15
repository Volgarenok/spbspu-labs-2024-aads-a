#include "data_processing.hpp"

sakovskaia::List< sakovskaia::ullList > sakovskaia::processData(const List< std::pair< std::string, ullList > > & sequences)
{
  List< ullList > result;
  if (sequences.empty())
  {
    return result;
  }

  bool finish = false;
  auto iters = List< List< unsigned long long int >::iterator >();

  for (const auto & seq : sequences)
  {
    if (!seq.second.empty())
    {
      iters.push_front(seq.second.begin());
    }
    else
    {
      iters.push_front(seq.second.end());
    }
  }

  while (!finish)
  {
    finish = true;
    ullList currentList;

    for (auto & it : iters)
    {
      if (it != sequences.front().second.end())
      {
        currentList.push_front(* it);
        ++it;
        finish = false;
      }
    }

    if (!currentList.empty())
    {
      result.push_front(currentList);
    }
  }

  return result;
}

sakovskaia::List< unsigned long long int > sakovskaia::calculateSums(const List< ullList > & processedData)
{
  List< unsigned long long int > result;

  for (const auto & list : processedData)
  {
    unsigned long long int sum = 0;
    for (const auto & num : list)
    {
      sum += num;
    }
    result.push_front(sum);
  }

  return result;
}
