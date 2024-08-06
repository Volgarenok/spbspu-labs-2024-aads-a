#include "datasetSummarizer.hpp"
#include <limits>
#include <ostream>

isaychev::DatasetSummarizer::DatasetSummarizer():
 key_sum(0),
 value_sum()
{}

void check_boundaries(int a, int b) //-> bool(int, int)
{
  int max = std::numeric_limits< int >::max();
  if (b > 0 && max - b < a)
  {
    throw std::overflow_error("final sum is too big");
  }
  int min = std::numeric_limits< int >::min();
  if (a < 0 && b < 0 &&  min - b > a)
  {
    throw std::underflow_error("final sum is too ");
  }
}

void isaychev::DatasetSummarizer::operator()(const std::pair< int, std::string > & elem)
{
  check_boundaries(key_sum, elem.first);
  key_sum += elem.first;
  value_sum += ' ';
  value_sum += elem.second;
}

int isaychev::DatasetSummarizer::get_keysum()
{
  return key_sum;
}
const std::string & isaychev::DatasetSummarizer::get_valsum()
{
  return value_sum;
}
