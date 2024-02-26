#include "input_list.hpp"
#include <string>
#include <sstream>
#include <fstream>
#include "list"

nikitov::List< std::pair< std::string, nikitov::List< int >* >* > nikitov::inputList(std::istream& input)
{
  List< std::pair< std::string, List< int >* >* > pairsList;
  std::string line = "";
  while (input >> line)
  {
    std::string numbers = "";
    std::getline(input, numbers);
    std::stringstream numbersStream;
    numbersStream << numbers;

    List< int >* numberList = new List< int >;
    int number = 0;
    while (numbersStream >> number)
    {
      numberList->push_back(number);
    }

    std::pair< std::string, List< int >* >* element = new std::pair< std::string, List< int >* >{line, numberList};
    pairsList.push_back(element);
  }
  return pairsList;
}
