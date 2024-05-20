#include "commands.hpp"
#include "SumStruct.hpp"

void novokhatskiy::ascending(int& num, std::string& str, Tree<int, std::string>& map)
{
  KeySum res;
  map.traverse_lnr(res);
  num = res.getKey();
  str = res.getStr();
}

void novokhatskiy::descending(int& num, std::string& str, Tree<int, std::string>& map)
{
  KeySum res;
  map.traverse_rnl(res);
  num = res.getKey();
  str = res.getStr();
}

void novokhatskiy::breadth(int& num, std::string& str, Tree<int, std::string>& map)
{
  KeySum res;
  map.traverse_breadth(res);
  num = res.getKey();
  str = res.getStr();
}
