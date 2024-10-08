#include <iostream>
#include <list>
#include <functional>
#include <ctime>
#include <deque>
#include <string>

#include "sort.hpp"

template < class t >
using comparison =  std::function< bool(const t &, const t &) >;
template < class t >
void sorts(const std::deque< t > & newDeque, const std::list< t > & newList, comparison< t > comp)
{
  rebdev::shaker< std::deque< t >, t >(newDeque, std::cout, comp);
  rebdev::oddEven< std::deque< t >, t >(newDeque, std::cout, comp);
  rebdev::shaker< std::list< t >, t >(newList, std::cout, comp);
  rebdev::oddEven< std::list< t >, t >(newList, std::cout, comp);
}
template < class t >
void mainOfMain(int numOfElements, bool greater)
{
  std::deque< t > newDeque;
  std::list< t > newList;
  for (int i = 0; i < numOfElements; ++i)
  {
    t a = std::rand();
    newList.push_back(a);
    a = std::rand();
    newDeque.push_back(a);
  }
  rebdev::listOut(newList, std::cout);
  rebdev::listOut(newDeque, std::cout);
  if (greater)
  {
    sorts< t >(newDeque, newList, std::greater< t >());
  }
  else
  {
    sorts< t >(newDeque, newList, std::less< t >());
  }
}

int main(int argv, char ** argc)
{
  if (argv != 4)
  {
    std::cerr << "Bad input agument number!\n";
    return 1;
  }
  int numOfElements;
  try
  {
    numOfElements = std::stoi(argc[3]);
  }
  catch (const std::exception & e)
  {
    std::cerr << "Bad number of elements!\n";
    return 1;
  }
  srand(time(0));
  bool greater;
  std::string comparisonParam(argc[1]);
  if (comparisonParam == "ascending")
  {
    greater = true;
  }
  else if (comparisonParam == "descending")
  {
    greater = false;
  }
  else
  {
    std::cerr << "Bad input sort argument!\n";
    return 1;
  }
  std::string numParam(argc[2]);
  if (numParam == "ints")
  {
    mainOfMain< int >(numOfElements, greater);
  }
  else if (numParam == "floats")
  {
    mainOfMain< float >(numOfElements, greater);
  }
  else
  {
    std::cerr << "Bad input number type argument!\n";
    return 1;
  }
  return 0;
}
