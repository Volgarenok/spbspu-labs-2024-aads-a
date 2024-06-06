#include "commands.hpp"
#include <stdexcept>
#include "SumStruct.hpp"

void novokhatskiy::ascending(int& num, std::string& str, Tree< int, std::string >& map)
{
  if (map.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  KeySum res;
  res = map.traverse_lnr(res);
  num = res.getKey();
  StrSum resStr;
  resStr = map.traverse_lnr(resStr);
  str = resStr.getStr();
}

void novokhatskiy::descending(int& num, std::string& str, Tree< int, std::string >& map)
{
  if (map.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  KeySum res;
  res = map.traverse_rnl(res);
  num = res.getKey();
  StrSum resStr;
  resStr = map.traverse_rnl(resStr);
  str = resStr.getStr();
}

void novokhatskiy::breadth(int& num, std::string& str, Tree< int, std::string >& map)
{
  if (map.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  KeySum res;
  res = map.traverse_breadth(res);
  num = res.getKey();
  StrSum resStr;
  resStr = map.traverse_breadth(resStr);
  str = resStr.getStr();
}
