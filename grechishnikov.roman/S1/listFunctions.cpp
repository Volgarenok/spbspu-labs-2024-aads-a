#include "listFunctions.hpp"
#include <stdexcept>
#include <limits>

size_t safeSum(const size_t& first, const size_t& second);

grechishnikov::namedList grechishnikov::inputList(std::istream& in)
{
  std::string listName = "";
  in >> listName;
  List< size_t > inputList;
  if (listName == "")
  {
    throw std::logic_error("Nothing was entered");
  }
  size_t inNum = 0;
  while (in >> inNum)
  {
    inputList.push_back(inNum);
  }
  return std::make_pair(listName, inputList);
}

grechishnikov::List< grechishnikov::namedList > grechishnikov::inputLists(std::istream& in)
{
  List< namedList > inputedLists;
  while (in)
  {
    inputedLists.push_back(inputList(in));
    if (!in.eof())
    {
      in.clear();
    }
  }
  return inputedLists;
}

size_t grechishnikov::countSum(const List< size_t >& list)
{
  if (list.empty())
  {
    return 0;
  }
  size_t sum = 0;
  auto iter = list.cbegin();
  while (iter != list.cend())
  {
    sum = safeSum(sum, *iter);
    iter++;
  }
  return sum;
}

void grechishnikov::outputList(const List< size_t >& list, std::ostream& out)
{
  if (list.empty())
  {
    return;
  }
  auto iter = list.cbegin();
  out << *iter;
  iter++;
  while (iter != list.cend())
  {
    out << ' ' << *iter;
    iter++;
  }
}

size_t safeSum(const size_t& first, const size_t& second)
{
  size_t max = std::numeric_limits< size_t >::max();
  if (max - first >= second)
  {
    return first + second;
  }
  else
  {
    throw std::overflow_error("Sum is too big");
  }
}
