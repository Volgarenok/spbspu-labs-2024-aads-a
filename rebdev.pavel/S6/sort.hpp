#ifndef SORT_HPP
#define SORT_HPP

#include <iostream>
#include <list>
#include <functional>

namespace rebdev
{
  template < class t >
  using comparison =  std::function< bool(const t &, const t &) >;
  template < class numStruct >
  void listOut(const numStruct & nStruct, std::ostream & out)
  {
    auto now = nStruct.begin();
    auto end = nStruct.end();
    out << (*now);
    ++now;
    while (now != end)
    {
      out << ' ' << (*now);
      ++now;
    }
    out << '\n';
  }
  template < class numStruct, class t >
  void shaker(const numStruct & nStruct, std::ostream & out, comparison< t > comp)
  {
    numStruct structCopy(nStruct);
    auto begin = structCopy.begin();
    auto end = structCopy.end();
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
    listOut(structCopy, out);
  }
  template < class iter, class t >
  void sortForEvenOdd(iter & iterNow, iter & end, comparison< t > comp, bool & isOddOrEven)
  {
    auto nextIter = iterNow;
    ++nextIter;
    while (iterNow != end)
    {
      if (comp((*iterNow), (*nextIter)))
      {
        isOddOrEven = false;
        std::swap((*iterNow), (*nextIter));
      }
      ++(++iterNow);
      ++(++nextIter);
    }
  }
  template < class numStruct, class t >
  void oddEven(const numStruct & nStruct, std::ostream & out, comparison< t > comp)
  {
    numStruct structCopy(nStruct);
    bool isOdd = false;
    bool isEven = false;
    auto iterNow = structCopy.begin();
    while (!isOdd || !isEven)
    {
      isOdd = true;
      isEven = true;
      auto end = structCopy.end();
      if ((structCopy.size() % 2) != 0)
      {
        --end;
      }
      iterNow = structCopy.begin();
      sortForEvenOdd(iterNow, end, comp, isOdd);
      if ((structCopy.size() % 2) == 0)
      {
        --end;
      }
      else
      {
        ++end;
      }
      iterNow = structCopy.begin();
      ++iterNow;
      sortForEvenOdd(iterNow, end, comp, isEven);
    }
    listOut(structCopy, out);
  }
}

#endif
