#include <iostream>
#include <fstream>
#include <string>
#include "SumStruct.hpp"
#include <algorithm>
#include "AVLtree.hpp"
#include "AVLtreeNode.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "forward_list.hpp"

template< class Key, class Value, class Compare = std::less< Key > >
using node_t = novokhatskiy::detail::NodeTree< Key, Value >;

void inputMaps(std::istream& in, novokhatskiy::Tree< int, std::string >& map)
{
  while (!in.eof())
  {
    in.clear();
    int key{};
    std::string val;
    while (in >> key >> val)
    {
      map.insert(std::make_pair(key, val));
    }
  }
}


int main(int argc, char** argv)
{
  using namespace novokhatskiy;
  Tree< int, std::string > map;
  if (argc != 3)
  {
    std::cerr << "Wrong input parameters\n";
    return 1;
  }
  else
  {
    std::ifstream inFile(argv[2]);
    inputMaps(inFile, map);
  }

  try
  {

  }
  catch (const std::logic_error& e)
  {
    std::cout << e.what() << '\n';
  }
}
