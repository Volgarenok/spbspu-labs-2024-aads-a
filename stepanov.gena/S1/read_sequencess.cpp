#include "read_sequencess.hpp"

namespace stepanov
{
  void read_sequences(List<std::pair<std::string, List<size_t>>>& sequences)
  {
    std::string name = "";

    while (std::cin >> name)
    {
      if (name.empty())
      {
        break;
      }
      List<size_t> numbers;
      size_t num;

      while (std::cin.peek() != '\n' && std::cin >> num)
      {
        numbers.push_back(num);
      }
      std::cin.ignore();
      sequences.push_back({ name, std::move(numbers) });
    }
  }
}
