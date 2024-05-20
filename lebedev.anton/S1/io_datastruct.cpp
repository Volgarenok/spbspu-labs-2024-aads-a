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
  output << pairs.cbegin()->first;
  for (auto pairs_iter = ++pairs.cbegin(); pairs_iter != pairs.cend(); pairs_iter++)
  {
    output << ' ' << pairs_iter->first;
  }
}

void lebedev::outputSequences(std::ostream & output, listOfPairs & pairs, size_t max_pair_size)
{
  List< List< size_t > > output_order;
  for (size_t i = 0; i < max_pair_size; i++)
  {
    List< size_t > output_order_i;
    for (auto pairs_iter = pairs.cbegin(); pairs_iter != pairs.cend(); pairs_iter++)
    {
      auto list_iter = pairs_iter->second.cbegin();
      if (i < pairs_iter->second.capacity())
      {
        std::advance(list_iter, i);
        output_order_i.push_back(*list_iter);
      }
    }
    output_order.push_back(output_order_i);
  }

  output << *(output_order.cbegin()->cbegin());
  for (auto ooi_iter = ++(output_order.cbegin()->cbegin()); ooi_iter != output_order.cbegin()->cend(); ooi_iter++)
  {
    output << ' ' << *ooi_iter;
  }
  for (auto oo_iter = ++(output_order.cbegin()); oo_iter != output_order.cend(); oo_iter++)
  {
    output << '\n' << *(oo_iter->cbegin());
    for (auto ooi_iter = ++(oo_iter->cbegin()); ooi_iter != oo_iter->cend(); ooi_iter++)
    {
      output << ' ' << *ooi_iter;
    }
  }
}

void lebedev::outputSums(std::ostream & output, List< size_t > sums)
{
  output << *sums.cbegin();
  for (auto sums_iter = ++sums.cbegin(); sums_iter != sums.cend(); sums_iter++)
  {
    output << ' ' << *sums_iter;
  }
}
