#include "io_datastruct.hpp"
#include <iterator>
#include <limits>

size_t lebedev::inputDS(std::istream & input, listOfPairs & pairs)
{
  std::string seq_name = "";
  size_t curr_num = 0;
  size_t max_pair_size = 0;
  while (!input.eof())
  {
    size_t pair_size = 0;
    input.clear();
    List< size_t > numbers;
    input >> seq_name;
    if (seq_name.empty())
    {
      break;
    }
    while (input >> curr_num)
    {
      numbers.push_back(curr_num);
      pair_size++;
    }
    max_pair_size = std::max(max_pair_size, pair_size);
    auto pair = std::make_pair(seq_name, numbers);
    pairs.push_back(pair);
  }
  return max_pair_size;
}

void lebedev::countSums(listOfPairs & pairs, List< size_t > & sums, size_t max_pair_size)
{
  if (max_pair_size == 0)
  {
    sums.push_back(0);
  }
  size_t max = std::numeric_limits< size_t >::max();
  for (size_t i = 0; i < max_pair_size; i++)
  {
    size_t sum = 0;
    for (auto pairs_iter = pairs.cbegin(); pairs_iter != pairs.cend(); pairs_iter++)
    {
      auto list_iter = pairs_iter->second.cbegin();
      if (i < pairs_iter->second.capacity())
      {
        std::advance(list_iter, i);
        size_t num = *list_iter;
        if (max - num < sum)
        {
          throw std::overflow_error("Size_t overflow!");
        }
        else
        {
          sum += num;
        }
      }
    }
    sums.push_back(sum);
  }
}

void lebedev::outputPairsNames(std::ostream & output, listOfPairs & pairs)
{
  bool is_first_name = true;
  for (auto pairs_iter = pairs.cbegin(); pairs_iter != pairs.cend(); ++pairs_iter)
  {
    if (is_first_name)
    {
      is_first_name = false;
    }
    else
    {
      output << ' ';
    }
    output << pairs_iter->first;
  }
}

void lebedev::outputSequences(std::ostream & output, listOfPairs & pairs, size_t max_pair_size)
{
  for (size_t i = 0; i < max_pair_size; i++)
  {
    bool is_first_num = true;
    for (auto pairs_iter = pairs.cbegin(); pairs_iter != pairs.cend(); pairs_iter++)
    {
      auto list_iter = pairs_iter->second.cbegin();
      if (i < pairs_iter->second.capacity())
      {
        std::advance(list_iter, i);
        size_t num = *list_iter;
        if (is_first_num)
        {
          is_first_num = false;
        }
        else
        {
          output << ' ';
        }
        output << num;
      }
    }
    if ((i + 1) != max_pair_size)
    {
      output << '\n';
    }
  }
}

void lebedev::outputSums(std::ostream & output, List< size_t > sums)
{
  bool is_first_sum = true;
  for (auto sums_iter = sums.cbegin(); sums_iter != sums.cend(); sums_iter++)
  {
    if (is_first_sum)
    {
      is_first_sum = false;
    }
    else
    {
      output << ' ';
    }
    output << *sums_iter;
  }
}
