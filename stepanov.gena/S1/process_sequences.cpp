#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include "process_sequences.hpp"
#include "node.hpp"
#include "list.hpp"
#include "iterator.hpp"
#include "constiterator.hpp"

namespace stepanov
{
  void process_sequences()
  {
    std::vector<std::pair<std::string, List<int>>> sequences;
    std::string line;

    while (true)
    {
      std::string name;
      std::cin >> name;  // Чтение названия последовательности

      if (std::cin.fail()) {
          break;  // Прекращаем чтение, если ввод завершен
      }

      List<int> numbers;
      int num;
      // Считываем числа, пока не встретим конец строки
      while (std::cin.peek() != '\n' && std::cin >> num)
      {
        numbers.push_back(num);
      }
      std::cin.ignore();  // Игнорируем символ новой строки

      sequences.push_back({ name, std::move(numbers) });
    }

    if (sequences.empty())
    {
        std::cout << "0" << std::endl;
        return;
    }

    // Вывод названий последовательностей
    for (const auto& seq : sequences)
    {
        std::cout << seq.first << " ";
    }
    std::cout << std::endl;

    // Инициализируем итераторы для каждой последовательности
    std::vector<List<int>::iterator> iters;
    for (auto& seq : sequences)
    {
        iters.push_back(seq.second.begin());
    }

    bool done = false;
    while (!done)
    {
      done = true;
      for (size_t i = 0; i < sequences.size(); ++i)
      {
        if (iters[i] != sequences[i].second.end())
        {
          std::cout << *iters[i] << " ";
          ++iters[i];
          done = false;
        }
      }
      std::cout << std::endl;
    }

    // Возвращаем итераторы в начало для суммы
    iters.clear();
    for (auto& seq : sequences)
    {
        iters.push_back(seq.second.begin());
    }

    // Цикл для подсчета суммы
    done = false;
    while (!done)
    {
      int sum = 0;
      done = true;
      for (size_t i = 0; i < sequences.size(); ++i)
      {
        if (iters[i] != sequences[i].second.end())
        {
          sum += *iters[i];
          ++iters[i];
          done = false;
        }
      }
      if (!done)
      {
        std::cout << sum << " ";
      }
    }
    std::cout << std::endl;
  }
}
