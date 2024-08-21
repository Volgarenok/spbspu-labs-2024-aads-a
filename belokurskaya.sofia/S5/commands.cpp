#include "commands.hpp"

#include <stdexcept>

#include "getSum.hpp"

void belokurskaya::ascending(int& num, std::string& str, BinarySearchTree< int, std::string >& tree)
{
  if (tree.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  KeySum res;
  res = tree.traverse_lnr(res);
  num = res.getResultKey();
  KeySum resStr;
  resStr = tree.traverse_lnr(resStr);
  str = resStr.getResultValue();
}

void belokurskaya::descending(int& num, std::string& str, BinarySearchTree< int, std::string >& tree)
{
  if (tree.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  KeySum res;
  res = tree.traverse_rnl(res);
  num = res.getResultKey();
  KeySum resStr;
  resStr = tree.traverse_rnl(resStr);
  str = resStr.getResultValue();
}

void belokurskaya::breadth(int& num, std::string& str, BinarySearchTree< int, std::string >& tree)
{
  if (tree.empty()) {
    throw std::logic_error("<EMPTY>");
  }
  KeySum res;
  res = tree.traverse_breadth(res);
  num = res.getResultKey();
  KeySum resStr;
  resStr = tree.traverse_breadth(resStr);
  str = resStr.getResultValue();
}