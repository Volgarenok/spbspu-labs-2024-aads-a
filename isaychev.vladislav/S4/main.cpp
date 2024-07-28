#include <iostream>
#include "tree.hpp"

int main()
{
  using namespace isaychev;
  BSTree< int, std::string > dict;
  std::cout << dict.empty() << "\n";

  dict[1] = "Time";
  dict[5] = "Rebellion";
  dict[3] = "a";
  dict[4] = "little";
  dict[2] = "for";

  std::cout << dict.empty() << " " << dict.size() << "\n";
  auto it = dict.find(5);
  std::cout << (*it).second << "\n";

  std::cout << dict.at(4) << "\n";

  try
  {
    dict.at(8);
  }
  catch (const std::exception & e)
  {
    std::cout << e.what() << "\n";
  }

/*  for (auto i = dict.cbegin(); i != dict.cend(); ++i)
  {
    std::cout << (*i).second << " ";
  }
  std::cout << "\n";*/
}
