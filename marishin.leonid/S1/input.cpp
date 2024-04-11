#include "input.hpp"

void marishin::readInput(LinkedList< std::pair< std::string, LinkedList< size_t >>>& pairs)
{
  std::string str;
  std::istream& input = std::cin;
  input >> str;
  while (input)
  {
    pairs.push_back({ str, LinkedList< size_t >() });
    input >> str;
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
    {
      break;
    }

    lst.push_back(sum);
    std::cout << "\n";
  }
}

void marishin::printResults(const LinkedList< size_t >& lst, bool overflow)
{
  if (overflow)
  {
    throw std::overflow_error("Overflow!");
  }
  else
  {
    for (auto& sum : lst)
    {
      std::cout << sum;
      if (&sum != &lst.back())
      {
        std::cout << " ";
      }
      if (&sum == &lst.back())
      {
        std::cout << "\n";
      }
    }
  }
}
