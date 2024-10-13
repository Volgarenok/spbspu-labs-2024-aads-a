#include "read_sequencess.hpp"

namespace stepanov
{
  std::vector<std::pair<std::string, List<size_t>>> read_sequences()
  {
    std::vector<std::pair<std::string, List<size_t>>> sequences;
    std::string name;

    while (std::cin >> name)
    {
      List<size_t> numbers;
      size_t num;

      while (std::cin.peek() != '\n' && std::cin >> num)
      {
        numbers.push_back(num);
      }
      std::cin.ignore();
      sequences.push_back({ name, std::move(numbers) });
    }
    return sequences;
  }
}
