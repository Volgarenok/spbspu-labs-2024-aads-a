#include "inputList.hpp"

grechishnikov::namedList grechishnikov::inputList(std::istream& in)
{
  std::string listName = "";
  in >> listName;
  List< size_t > inputList;
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
  while (!in.eof())
  {
    inputedLists.push_back(inputList(in));
  }
  return inputedLists;
}

