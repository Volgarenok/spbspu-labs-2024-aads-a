#include <iostream>
#include <fstream>
#include <functional>
#include <stdexcept>
#include "red_black_tree.hpp"
#include "complement_functor.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  if (argc != 3)
  {
    std::cerr << "Wrong CLA number";
    return 1;
  }
  std::ifstream file(argv[2]);
  if (!file)
  {
    std::cerr << "Error in file opening";
    return 2;
  }
  using tree_t = RedBlackTree< int, std::string >;
  tree_t collection;
  int key = 0;
  std::string name;
  while (file >> key >> name)
  {
    collection.insert(std::make_pair(key, name));
  }
  if (!file.eof())
  {
    std::cerr << "Input error\n";
    return 3;
  }
  using traversal_func = std::function< ComplementFunctor(ComplementFunctor) >;
  RedBlackTree< std::string, traversal_func > traversal;
  {
    using namespace std::placeholders;
    const tree_t * collect_ptr = std::addressof(collection);
    traversal.insert(std::make_pair("ascending", std::bind(&tree_t::traverse_lnr< ComplementFunctor >, collect_ptr, _1)));
    traversal.insert(std::make_pair("descending", std::bind(&tree_t::traverse_rnl< ComplementFunctor >, collect_ptr, _1)));
    traversal.insert(std::make_pair("breadth", std::bind(&tree_t::traverse_breadth< ComplementFunctor >, collect_ptr, _1)));
  }
  if (collection.empty())
  {
    std::cout << "<EMPTY>\n";
  }
  else
  {
    try
    {
      ComplementFunctor functor;
      functor = traversal.at(argv[1])(functor);
      std::cout << functor.sum << functor.names << "\n";
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << "\n";
      return 4;
    }
  }
  return 0;
}
