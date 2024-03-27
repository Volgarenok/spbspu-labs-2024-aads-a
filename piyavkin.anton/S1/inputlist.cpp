#include "inputlist.hpp"

void piyavkin::inputList(std::istream& in, list_t& list)
{
  std::string name = "";
  char symbol = 0;
  unsigned long long val = 0;
  while (in >> name)
  {
    List< unsigned long long > numbers;
    in >> std::noskipws;
    in >> symbol;
    while (symbol != '\n')
    {
      if (symbol == ' ')
      {
        in >> std::skipws;
        in >> val;
        if (!in)
        {
          throw std::logic_error("Incorrect number input");
        }
        in >> std::noskipws;
        numbers.push_back(val);
      }
      in >> symbol;
    }
    in >> std::skipws;
    auto pair = std::make_pair(name, numbers);
    list.push_back(pair);
  }
  if (name == "")
  {
    throw std::invalid_argument("Input not processed");
  }
}
