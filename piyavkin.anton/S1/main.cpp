#include <iostream>
#include "list.hpp"
#include "inputlist.hpp"
#include "output.hpp"

void output(std::ostream& out, const piyavkin::list_t& list)
{
  auto start = list.cbegin();
  auto finish = list.cend();
  while (start != finish)
  {
    if (start != list.cbegin())
    {
      out << ' ';
    }
    out << start->first;
    ++start;
  }
  out << '\n';
  outputValue(out, list);
  auto sums = countSum(list);
  if (sums.empty())
  {
    out << 0;
    return;
  }
  auto iterator = sums.cbegin();
  for (size_t i = 0; i < sums.size(); ++i)
  {
    if (i != 0)
    {
      out << ' ';
    }
    out << *iterator++;
  }
}

int main()
{
  using namespace piyavkin;
  list_t list;
  try
  {
    inputList(std::cin, list);
    output(std::cout, list);
  }
  catch (const std::invalid_argument& e)
  {
    std::cout << 0 << '\n';
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  std::cout << '\n';
}
