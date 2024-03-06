#include "input.hpp"

void readInput(LinkedList< std::pair< std::string, LinkedList< size_t >>>& pairs)
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

void printPairs(const LinkedList< std::pair< std::string, LinkedList< size_t >>>& pairs)
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

void calculateSums(const LinkedList< std::pair< std::string, LinkedList< size_t >>>& pairs, bool& overflow, LinkedList< size_t >& lst)
{
  constexpr size_t maxvalue = std::numeric_limits< size_t >::max();
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
        if (maxvalue > frontValue + sum)
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

void printResults(const LinkedList< size_t >& lst, bool overflow)
{
  if (overflow)
  {
    std::cerr << "Overflow!\n";
    return;
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

  if (lst.empty())
  {
    std::cout << "0\n";
  }
}
