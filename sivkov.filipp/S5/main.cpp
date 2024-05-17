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
  if (argc != 3)
  {
    std::cerr << "Error CMD line\n";
    return 1;
  }
  else
  {
    std::ifstream file(argv[2]);
    inputDictionary(tree, file);
    command = argv[1];
  }
  using func = std::function< void(avlTree&, KeySum&)>;
  AVLTree< std::string, func > cmd;
  cmd.push("ascending", ascending);
  cmd.push("descending", descending);
  cmd.push("breadth", breadth);
  KeySum f;
  try
  {
    auto it = cmd.find(command);
    if (it != cmd.cend())
    {
      it->second(tree, f);
    }
    else
    {
      throw std::out_of_range("error comand");
    }
  }
  catch (const std::logic_error& e)
  {
    std::cout << e.what() << "\n";
  }
  catch (const std::out_of_range&)
  {
    std::cerr << e.what() << "\n"
    return 2;
  }

  int a = f.key_;
  std::string str = f.string_;

  std::cout << a << str << "\n";

  return 0;
}
