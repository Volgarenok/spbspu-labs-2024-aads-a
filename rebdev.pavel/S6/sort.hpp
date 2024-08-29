#ifndef SORT_HPP
#define SORT_HPP

#include <iostream>
#include <list>
#include <functional>

namespace rebdev
{
  template < class t >
  void shaker(const std::list< t > & nList, std::ostream & out,  std::function< bool(const t &, const t &) > comp)
  {
    std::list< t > listCopy(nList);
    auto begin = listCopy.begin();
    auto end = listCopy.end();
    auto iterNow = begin;
    while (begin != end)
    {
      auto nextIter = iterNow;
      ++nextIter;
      while (nextIter != end)
      {
        if (comp((*iterNow), (*nextIter)))
        {
          std::swap((*iterNow), (*nextIter));
        }
        ++iterNow;
        ++nextIter;
      }
      --end;
      auto lastIter = iterNow;
      --lastIter;
      while (iterNow != begin)
      {
        if (!comp((*iterNow), (*lastIter)))
        {
          std::swap((*iterNow), (*lastIter));
        }
        --iterNow;
        --lastIter;
      }
      ++begin;
    }
    iterNow = listCopy.begin();
    while (iterNow != listCopy.end())
    {
      out << (*iterNow) << ' ';
      ++iterNow;
    }
    out << '\n';
  }
  template < class t >
  void oddEven(const std::list< t > & nList, std::ostream & out,  std::function< bool(const t &, const t &) > comp)
  {
    std::list< t > listCopy(nList);
    bool isOdd = false;
    bool isEven = false;
    auto iterNow = listCopy.begin();
    while (!isOdd || !isEven)
    {
      isOdd = true;
      isEven = true;
      auto end = listCopy.end();
      if ((listCopy.size() % 2) != 0)
      {
        --end;
      }
      iterNow = listCopy.begin();
      auto nextIter = iterNow;
      ++nextIter;
      while (iterNow != end)
      {
        if (comp((*iterNow), (*nextIter)))
        {
          isOdd = false;
          std::swap((*iterNow), (*nextIter));
        }
        ++(++iterNow);
        ++(++nextIter);
      }
      if ((listCopy.size() % 2) == 0)
      {
        --end;
      }
      else
      {
        ++end;
      }
      iterNow = listCopy.begin();
      ++iterNow;
      nextIter = iterNow;
      ++nextIter;
      while (iterNow != end)
      {
        if (comp((*iterNow), (*nextIter)))
        {
          isEven = true;
          std::swap((*iterNow), (*nextIter));
        }
        ++(++iterNow);
        ++(++nextIter);
      }
    }
    iterNow = listCopy.begin();
    while (iterNow != listCopy.end())
    {
      out << (*iterNow) << ' ';
      ++iterNow;
    }
    out << '\n';
  }
}

#endif
