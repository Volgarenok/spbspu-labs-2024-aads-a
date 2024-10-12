#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <limits>

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
      std::cin >> name;
      if (std::cin.fail())
      {
        break;
      }

      List<int> numbers;
      int num;
      while (std::cin.peek() != '\n' && std::cin >> num)
      {
        if (num > std::numeric_limits<int>::max())
        {
          std::cerr << "Error: Overflow occurred" << std::endl;
          exit(1);
        }
        numbers.push_back(static_cast<int>(num));
      }
      std::cin.ignore();
      sequences.push_back({ name, std::move(numbers) });
    }

    if (sequences.empty())
    {
      std::cout << "0" << std::endl;
      return;
    }

    for (const auto& seq : sequences)
    {
      std::cout << seq.first << " ";
    }
    std::cout << std::endl;

    std::vector<List<int>::iterator> iters;
    for (auto& seq : sequences)
    {
      iters.push_back(seq.second.begin());
    }

    bool done = false;
    while (!done)
    {
      done = true;
      bool has_output = false;
      for (size_t i = 0; i < sequences.size(); ++i)
      {
        if (iters[i] != sequences[i].second.end())
        {
          std::cout << *iters[i] << " ";
          ++iters[i];
          done = false;
          has_output = true;
        }
      }
      if (has_output)
      {
        std::cout << std::endl;
      }
    }
    iters.clear();
    for (auto& seq : sequences)
    {
      iters.push_back(seq.second.begin());
    }

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
