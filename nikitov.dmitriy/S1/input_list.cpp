#include "input_list.hpp"
#include <string>
#include <sstream>
#include <fstream>
#include "list"

void nikitov::inputList(List< std::pair< std::string, List< int > > >& pairsList, std::istream& input)
{
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
    pairsList.push_back({ word, List< int >() });

    int number = 0;
    while (streamLine >> number)
    {
      pairsList.back().second.push_back(number);
    }
  }
}
