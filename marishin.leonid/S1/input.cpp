#include "input.hpp"
#include <limits>

void marishin::inputList(LinkedList< std::pair< std::string, LinkedList< size_t > > > & pairs, std::istream & input)
{
  std::string str;
  size_t num = 0;
  while (input)
  {
    input >> str;
<<<<<<< HEAD
    if (str.empty())
=======
    while (input && std::isdigit(str[0]))
    {
      pairs.back().second.push_back(std::stoull(str));
     input >> str;
    }
  }
}

void marishin::printPairs(const LinkedList< std::pair< std::string, LinkedList< size_t >>>& pairs)
{
  auto iter = pairs.begin();
  auto end = pairs.end();

  while (iter != end)
  {
    std::cout << (*iter).first;
    if (++iter != end)
    {
      std::cout << " ";
    }
  }

  if (!pairs.empty())
  {
    std::cout << "\n";
  }
}

void marishin::calculateSums(
  const LinkedList< std::pair< std::string, LinkedList< size_t >>>& pairs,
  bool& overflow,
  LinkedList< size_t >& lst
)
{
  while (!pairs.empty())
  {
    size_t sum = 0;
    bool emptyList = false;

    for (auto it = pairs.begin(); it != pairs.end(); ++it)
    {
      auto& pair = *it;
      if (!pair.second.empty())
      {
        if (emptyList)
        {
          std::cout << " ";
        }
        emptyList = true;
        auto frontValue = pair.second.front();
        std::cout << frontValue;
        constexpr size_t maxvalue = std::numeric_limits< size_t >::max();
        if (maxvalue - sum > frontValue)
        {
          sum += frontValue;
          pair.second.pop_front();
        }
        else
        {
          overflow = true;
          sum = std::numeric_limits< size_t >::max();
          pair.second.pop_front();
        }
      }
    }

    if (!emptyList)
>>>>>>> 8ef7cafad088b2e9a6df6e0037f6365c7c6d5722
    {
      break;
    }
    pairs.push_back({ str, LinkedList< size_t >() });
    while (input >> num)
    {
      pairs.back().second.push_back(num);
    }
    if (!input.eof())
    {
      input.clear();
    }
  }
<<<<<<< HEAD
=======
  if (lst.empty())
  {
    std::cout << '0';
  }
>>>>>>> 8ef7cafad088b2e9a6df6e0037f6365c7c6d5722
}
