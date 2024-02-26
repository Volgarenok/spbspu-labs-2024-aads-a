#include "input_list.hpp"
#include <string>
#include <fstream>
#include "list"

nikitov::List< std::pair< std::string, nikitov::List< int >* >* > nikitov::inputList(std::istream& input)
{
  List< std::pair< std::string, List< int >* >* > pairsList;
  std::string line = "";
  while (input >> line)
  {
    List< int >* numberList = new List< int >;
    std::string numbers = "";
    std::getline(input, numbers);
    const char* cNumbers = numbers.substr(1).c_str();

    size_t coordinatePointer = 0;
    while (cNumbers[0] != '\0')
    {
      numberList->push_back(std::stod(cNumbers, std::addressof(coordinatePointer)));
      cNumbers += coordinatePointer;
    }

    std::pair< std::string, List< int >* >* element = new std::pair< std::string, List< int >* >{line, numberList};
    pairsList.push_back(element);
  }
  return pairsList;
}
