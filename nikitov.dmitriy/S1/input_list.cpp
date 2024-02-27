#include "input_list.hpp"
#include <string>
#include <fstream>
#include "list"

void nikitov::inputList(List< std::pair< std::string, List< int > > >& pairsList, std::istream& input)
{
  std::string line = "";
  input >> line;
  while (input)
  {
    if (!input)
    {
      throw std::logic_error("Error: Wrong input");
    }

    pairsList.push_back({ line, List< int >() });

    while (input >> line && !std::isalpha(line[0]))
    {
      pairsList.back().second.push_back(std::stoi(line));
      if (line.find('\n') != std::string::npos)
      {
        break;
      }
    }
  }
}
