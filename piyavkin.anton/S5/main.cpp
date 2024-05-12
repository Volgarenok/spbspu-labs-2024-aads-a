#include <iostream>
#include <fstream>
#include <tree.hpp>
#include "keysum.hpp"

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "File entered incorrectly\n";
    return 1;
  }
  using namespace piyavkin;
  std::ifstream in(argv[2]);
  if (!in.is_open())
  {
    std::cerr << "The file is not open\n";
    return 2;
  }
  Tree< int, std::string > tree;
  int key = 0;
  std::string val = "";
  while (in >> key >> val)
  {
    tree.insert(std::pair< int, std::string >(key, val));
  }
  if (!in.eof())
  {
    std::cerr << "Bad input\n";
    return 3;
  }
  try
  {
    std::string name(argv[1]);
    if (name == "ascending")
    {
      std::cout << tree.traverse_lnr(KeySum()).getKey() << tree.traverse_lnr(KeySum()).getVal();
    }
    else if (name == "descending")
    {
      std::cout << tree.traverse_rnl(KeySum()).getKey() << tree.traverse_rnl(KeySum()).getVal();
    }
    else if (name == "breadth")
    {
      std::cout << tree.traverse_breadth(KeySum()).getKey() << tree.traverse_breadth(KeySum()).getVal();
    }
    else
    {
      std::cerr << "Incorrect traversal order";
      return 1;
    }
    std::cout << '\n';
  }
  catch (const std::logic_error& e)
  {
    std::cout << e.what() << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 4;
  }
}
