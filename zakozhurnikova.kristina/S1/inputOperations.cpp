#ifndef INPUT_OPERATIONS_HPP
#define INPUT_OPERATIONS_HPP

namespace zakozhurnikova
{
  using pair = std::pair<std::string, List<size_t>>;
  template <typename T>
  void readList(List<pair>& list, std::istream& in)
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
      List<T> numbers;
      while (*str)
      {
        int k = std::stoll(str, &pos);
        numbers.push(k);
        str += pos;
      }
      auto pair = std::make_pair(stringName, numbers);
      list.push(pair);
    }
  };
}

