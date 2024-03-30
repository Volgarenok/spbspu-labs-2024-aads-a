#ifndef INPUT_OPERATIONS_HPP
#define INPUT_OPERATIONS_HPP
#include <iostream>
#include <iosfwd>
#include <utility>
#include <list.hpp>

namespace zakozhurnikova
{
  using pair = std::pair< std::string, List< size_t > >;
  void readList(List< pair >& list, std::istream& in)
  {
    while (!in.eof())
    {
      std::string stringName;
      std::cin >> stringName;
      if (!std::cin)
      {
        return;
      }
      std::string input;
      std::getline(std::cin, input);

      size_t pos = 0;
      const char* str = input.c_str();
      List< size_t > numbers;
      while (*str)
      {
        size_t k = std::stoull(str, &pos);
        numbers.push(k);
        str += pos;
      }
      auto pair = std::make_pair(stringName, numbers);
      list.push(pair);
    }
  };
}

#endif
