#include <iostream>
#include <tree.hpp>

int main()
{
  using namespace piyavkin;
  Tree< int, int > tree({{1,1}, {2,2}, {3,3}});
  for (auto i = tree.clbegin(); i != tree.clend(); ++i)
  {
    std::cout << (*i).second << ' ';
  }
}
