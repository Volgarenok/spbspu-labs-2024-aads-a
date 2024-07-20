#include "commands.hpp"
#include <string>
#include "key_summ.hpp"

std::pair< int, std::string > ishmuratov::ascend(AVLTree< int, std::string > & data)
{
  Key_summ sum;
  sum = data.traverse_lnr(sum);
  return std::make_pair(sum.get_int(), sum.get_str());
}

std::pair< int, std::string > ishmuratov::descend(AVLTree< int, std::string > & data)
{
  Key_summ sum;
  sum = data.traverse_rnl(sum);
  return std::make_pair(sum.get_int(), sum.get_str());
}

std::pair< int, std::string > ishmuratov::breadth(AVLTree< int, std::string > &data)
{
  Key_summ sum;
  sum = data.traverse_breadth(sum);
  return std::make_pair(sum.get_int(), sum.get_str());
}
