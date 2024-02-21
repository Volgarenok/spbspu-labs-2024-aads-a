#include "readSequences.hpp"
#include <iostream>

SequenceVector readSequences()
{
  SequenceVector sequences;
  std::string name;
  int number;

  while (std::cin >> name)
  {
    List< int > sequence;
    while (std::cin >> number)
    {
      sequence.push_back(number);
      if (std::cin.peek() == '\n' || std::cin.peek() == EOF)
      {
        break;
      }
    }
    sequences.push_back({ name, sequence });
  }
  return sequences;
}
