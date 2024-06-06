#include <iostream>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <AVLTree.hpp>
#include "cmd.hpp"
#include "input.hpp"
#include "key_summ.hpp"

int main(int argc, char* argv[])
{
  using namespace sivkov;
  using avlTree = AVLTree< int, std::string >;
  avlTree tree;
  std::string command = "";
  std::string filename = "";
  if (argc != 3)
  {
    std::cerr << "Error CMD line\n";
    return 1;
  }
  else
  {
    command = argv[1];
    filename = argv[2];
  }

  using func = std::function< void(avlTree&, KeySum&, std::ostream&)>;
  AVLTree< std::string, func > cmd;
  cmd.push("ascending", ascending);
  cmd.push("descending", descending);
  cmd.push("breadth", breadth);
  KeySum f;

  try
  {
    std::fstream file(filename);
    inputDictionary(tree, file);
    auto it = cmd.find(command);
    if (it != cmd.cend())
    {
      it->second(tree, f, std::cout);
    }
    else
    {
      throw std::out_of_range("error commnd");
    }
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::logic_error& e)
  {
    std::cout << e.what() << "\n";
  }
  return 0;
}

