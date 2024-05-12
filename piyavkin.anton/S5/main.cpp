#include <iostream>
#include <tree.hpp>

struct Sumkey
{
  void operator()(const std::pair< int, std::string >& val)
  {
    str += val.second;
    key += val.first;
  }
  std::string str;
  long long int key;
};


int main()
{
  using namespace piyavkin;
  Tree< int, std::string > tree({{1,"a"}, {2,"b"}, {3,"c"}, {4, "d"}, {-3, "e"}, {0, "f"}, {6, "g"}, {5, "h"}, {-10, "i"}});
  for (auto i = tree.clrbegin(); i != tree.clrend(); ++i)
  {
    std::cout << (*i).second << ' ';
  }
  std::cout << '\n';
  std::cout << tree.traverse_lnr(Sumkey()).key << ' ' << tree.traverse_lnr(Sumkey()).str;
  std::cout << '\n';
  std::cout << tree.traverse_rnl(Sumkey()).key << ' ' << tree.traverse_rnl(Sumkey()).str;
  std::cout << '\n';
  std::cout << tree.traverse_breadth(Sumkey()).key << ' ' << tree.traverse_breadth(Sumkey()).str;
  std::cout << '\n';
}
