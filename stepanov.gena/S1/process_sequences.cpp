#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>

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

    while (std::getline(std::cin, line))
    {
      std::istringstream iss(line);
      std::string name;
      iss >> name;
      List<int> numbers;
      int num;
      while (iss >> num)
      {
        numbers.push_back(num);
      }
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
