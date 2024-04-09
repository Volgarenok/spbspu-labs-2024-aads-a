#include "inputOperations.hpp"

void zakozhurnikova::readList(List< pair >& list, std::istream& in)
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
      numbers.push_back(k);
      str += pos;
    }
    auto pair = std::make_pair(stringName, numbers);
    list.push_back(pair);
  }
}
