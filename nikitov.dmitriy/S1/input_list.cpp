#include "input_list.hpp"
#include <string>
#include <sstream>
#include <fstream>
#include "list"

nikitov::List< std::pair< std::string, nikitov::List< int >* >* > nikitov::inputList(std::istream& input)
{
  List< std::pair< std::string, List< int >* >* > pairsList;
  std::string line = "";
  while (std::getline(input, line))
  {
    if (!input)
    {
      throw std::logic_error("Error: Wrong input");
    }
    std::stringstream streamLine;
    streamLine << line;

    std::string word = "";
    streamLine >> word;

    int number = 0;
    List< int >* numberList = new List< int >;
    while (streamLine >> number)
    {
      numberList->push_back(number);
    }

    std::pair< std::string, nikitov::List< int >* >* pairPtr = nullptr;
    pairPtr = new std::pair< std::string, nikitov::List< int >* >{ word, numberList };
    pairsList.push_back(pairPtr);
  }
  return pairsList;
}

void nikitov::clearPairs(nikitov::List< std::pair< std::string, nikitov::List< int >* >* >& pairsList)
{
  ListIterator< std::pair< std::string, nikitov::List< int >* >* > pairsIterator = pairsList.begin();
  size_t sizeOfPairs = pairsList.size();
  for (size_t i = 0; i != sizeOfPairs; ++i)
  {
    delete *pairsIterator;
    pairsIterator++;
  }
}
