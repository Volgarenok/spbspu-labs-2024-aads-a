#include "readSequences.hpp"

#include <iostream>

belokurskaya::SequenceVector belokurskaya::readSequences()
{
  SequenceVector sequences;
  std::string name = "";

  while (std::cin >> name)
  {
    List< int > sequence;
    int number = 0;
    while (std::cin >> number)
    {
      sequence.push_back(number);
      if (std::cin.peek() == '\n')
      {
        break;
      }
    }
    if (!std::cin.eof())
    {
      std::cin.clear();
    }
    sequences.push_back({ name, sequence });
  }
  return sequences;
}
