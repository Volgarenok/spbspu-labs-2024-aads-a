#ifndef LISTFUNCTION_HPP
#define LISTFUNCTION_HPP

#include <iostream>
#include <utility>
#include <string>

//include "BiList"
#include <list> //del

namespace rebdev
{
  using numList = std::list< size_t >;
  using nameAndNum = std::pair< std::string, numList >;
  using pairList = std::list< nameAndNum >;
  using nameList = std::list< std::string >;
  using listOfNumList = std::list< numList >;
  using nameAndListOfNumList = std::pair< nameList, listOfNumList >;

  void inputList(std::istream & in, pairList & pList);
  void inputNumList(std::istream & in, numList & nList);
  nameList createNameList(pairList & pList);
  listOfNumList createListOfNumList(pairList & pList);
  void outputList(std::ostream & out, nameAndListOfNumList & pair);

  bool plus(size_t & f, size_t s);
}

#endif
