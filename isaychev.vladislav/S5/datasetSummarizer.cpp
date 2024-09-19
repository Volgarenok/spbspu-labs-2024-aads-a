#include "datasetSummarizer.hpp"
#include <limits>
#include <stdexcept>

isaychev::DatasetSummarizer::DatasetSummarizer():
 key_sum(0),
 value_sum()
{}

bool isOverflow(int a, int b)
{
  int max = std::numeric_limits< int >::max();
  return a > 0 && b > 0 && max - a < b;
}

bool isUnderflow(int a, int b)
{
  int min = std::numeric_limits< int >::min();
  return a < 0 && b < 0 && min - a > b;
}

void isaychev::DatasetSummarizer::operator()(const std::pair< int, std::string > & elem)
{
  if (isOverflow(key_sum, elem.first))
  {
    throw std::overflow_error("final sum is too large");
  }
  else if (isUnderflow(key_sum, elem.first))
  {
    throw std::overflow_error("final sum is too small");
  }
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
