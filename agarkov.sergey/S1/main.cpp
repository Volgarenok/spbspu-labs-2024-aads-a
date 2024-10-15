#include <iostream>
#include <string>
#include <stdexcept>
#include "inputfunc.hpp"
#include "forwardlist.hpp"

#include "inputfunc.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

template<typename Iterator>
void advance(Iterator& iter, size_t n)
{
  for (size_t i = 0; i < n && iter != Iterator(); ++i)
  {
    ++iter;
  }
}

int main()
{
  try
  {
    agarkov::ForwardList<std::pair<std::string, agarkov::ForwardList<size_t>>> lists = agarkov::inputLists(std::cin);

    std::cout << "Список названий введённых списков:\n";
    for (auto iter = lists.begin(); iter != lists.end(); ++iter)
    {
      std::cout << (*iter).first << ' ';
    }
    std::cout << '\n';

    std::cout << "\nПоследовательности чисел:\n";
    size_t max_length = 0;
    for (const auto& pair : lists)
    {
      max_length = std::max(max_length, pair.second.max_size());
    }

    for (size_t i = 0; i < max_length; ++i)
    {
      bool has_elements = false;
      for (auto iter = lists.begin(); iter != lists.end(); ++iter)
      {
        const auto& pair = *iter;
        if (!pair.second.empty() && i < pair.second.max_size())
        {
          auto inner_iter = pair.second.begin();
          advance(inner_iter, i);
          std::cout << *inner_iter << ' ';
          has_elements = true;
        }
      }
      if (has_elements)
      {
        std::cout << '\n';
      }
    }

    std::cout << "\nСуммы значений составленных списков:\n";
    for (size_t i = 0; i < max_length; ++i)
    {
      size_t sum = 0;
      bool has_elements = false;
      for (auto iter = lists.begin(); iter != lists.end(); ++iter)
      {
        const auto& pair = *iter;
        if (!pair.second.empty() && i < pair.second.max_size())
        {
          auto inner_iter = pair.second.begin();
          advance(inner_iter, i);
          sum += *inner_iter;
          has_elements = true;
        }
      }
      if (has_elements)
      {
        std::cout << sum << '\n';
      }
    }

    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
}