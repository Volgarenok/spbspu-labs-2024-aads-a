#include <iostream>
#include <fstream>
#include <functional>
#include "red_black_tree.hpp"
#include "const_lnr_iterator.hpp"
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
  using traversal_func = std::function< ComplementFunctor(tree_t *, ComplementFunctor) >;
  RedBlackTree< std::string, traversal_func > traversal;

  traversal.insert(std::make_pair("ascending", &tree_t::traverse_lnr< ComplementFunctor >));
  traversal.insert(std::make_pair("descending", &tree_t::traverse_rnl< ComplementFunctor >));
  traversal.insert(std::make_pair("breadth", &tree_t::traverse_breadth< ComplementFunctor >));

  ComplementFunctor functor;
  traversal.at("ascending")(std::addressof(collection), functor);
  std::cout << functor.sum;
  return 0;
}
