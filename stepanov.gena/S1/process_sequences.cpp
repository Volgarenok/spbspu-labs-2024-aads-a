#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <limits>
#include <cstdlib>

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
    std::string name;

    while (std::cin >> name)
    {
      List<int> numbers;
      unsigned long long num;

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

    for (auto it = sequences.begin(); it != sequences.end(); ++it)
    {
      std::cout << it->first;
      if (std::next(it) != sequences.end())
      {
        std::cout << " ";
      }
    }
    std::cout << std::endl;

    for (auto& seq : sequences)
    {
      if (seq.second.empty())
      {
        std::cout << "0" << std::endl;
      }
    }

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
      for (auto it = iters.begin(); it != iters.end(); ++it)
      {
        size_t idx = std::distance(iters.begin(), it);
        if (*it != sequences[idx].second.end())
        {
          std::cout << **it;
          if (std::next(it) != iters.end())
          {
            std::cout << " ";
          }
          ++(*it);
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
      bool has_values = false;

      for (auto it = iters.begin(); it != iters.end(); ++it)
      {
        size_t idx = std::distance(iters.begin(), it);
        if (*it != sequences[idx].second.end())
        {
          sum += **it;
          ++(*it);
          done = false;
          has_values = true;
        }
      }

      if (has_values)
      {
        std::cout << sum;
        if (!done)
        {
          std::cout << " ";
        }
      }
    }
    std::cout << std::endl;
  }
}
