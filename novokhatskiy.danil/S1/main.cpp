#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include "forward_list.hpp"
#include "forward_list_iterators.hpp"

using pairsOfList = novokhatskiy::ForwardList< std::pair< std::string, novokhatskiy::ForwardList< size_t > > >;

void inputForwardList(pairsOfList& pairsList, std::istream& input)
{
  while (!input.eof())
  {
    input.clear();
    std::pair< std::string, novokhatskiy::ForwardList< size_t > > pair{};
    input >> pair.first;
    if (pair.first.empty())
    {
      break;
    }
    size_t num = {};
    while (input >> num)
    {
      pair.second.push_front(num);
    }
    pair.second.reverse();
    pairsList.push_front(pair);
  }
  pairsList.reverse();
}

void outputForwardList(std::ostream& out, pairsOfList& pairs)
{
  if (pairs.empty())
  {
    throw std::invalid_argument("ForwardList is empty");
  }
  novokhatskiy::ForwardIterator< std::pair< std::string, novokhatskiy::ForwardList< size_t > > > iter = pairs.begin();
  size_t maxSize{};
  for (; iter != pairs.end(); iter++)
  {
    if (std::isalpha(iter->first[0]))
    {
      if (iter != pairs.begin())
      {
        out << ' ';
      }
      out << iter->first;
    }
    else
    {
      std::cout << ' ';
    }
    maxSize = std::max(maxSize, iter->second.size());
  }
  std::cout << '\n';
  novokhatskiy::ForwardList< size_t > listOfSums;
  size_t sum{};
  bool overFlow = false;
  for (size_t i = 0; i < maxSize; i++)
  {
    for (auto j = pairs.begin(); j != pairs.end(); ++j)
    {
      novokhatskiy::ForwardIterator< size_t > numberIter = j->second.begin();
      if (j->second.size() <= i)
      {
        continue;
      }
      std::advance(numberIter, i);
      if (sum != 0)
      {
        out << ' ';
      }
      out << *numberIter;
      if (std::numeric_limits< size_t >::max() - *numberIter < sum)
      {
        overFlow = true;
      }
      else
      {
        sum += *numberIter;
      }
    }
    if (sum == 0)
    {
      continue;
    }
    else
    {
      out << '\n';
      listOfSums.push_front(sum);
      sum = 0;
    }
  }
  if (overFlow)
  {
    throw std::out_of_range("Overflow");
  }
  listOfSums.reverse();
  if (listOfSums.empty())
  {
    std::cout << "0\n";
  }
  else
  {
    for (auto i = listOfSums.begin(); i != listOfSums.end(); ++i)
    {
      if (i != listOfSums.begin())
      {
        out << ' ';
      }
      out << *i;
    }
    out << '\n';
  }
}

int main()
{
  using namespace novokhatskiy;
  try
  {
    ForwardList< std::pair< std::string, ForwardList< size_t > > > pairsOfForwardList;
    inputForwardList(pairsOfForwardList, std::cin);
    outputForwardList(std::cout, pairsOfForwardList);
  }
  catch (const std::invalid_argument&)
  {
    std::cout << 0 << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
