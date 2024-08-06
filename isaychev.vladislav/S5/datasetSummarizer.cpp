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
  int min = std::numeric_limits< int >::min();
  return ((b > 0 && max - b < a) || (a < 0 && b < 0 &&  min - b > a));
}

void isaychev::DatasetSummarizer::operator()(const std::pair< int, std::string > & elem)
{
  if (isOverflow(key_sum, elem.first))
  {
    throw std::overflow_error("final sum is out of bounds");
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
