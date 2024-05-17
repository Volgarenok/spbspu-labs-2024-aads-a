#include <iostream>
#include <fstream>
#include <tree.hpp>
#include "keysum.hpp"
#include "commands.hpp"

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
    tree.unsplay_insert(std::pair< int, std::string >(key, val));
  }
  if (!in.eof())
  {
    std::cerr << "Bad input\n";
    return 3;
  }
  Tree< std::string, std::function< void(std::ostream&, const Tree< int, std::string >&, KeySum& f) > > cmds;
  cmds["ascending"] = traverse_ascending;
  cmds["descending"] = traverse_descending;
  cmds["breadth"] = traverse_breadth;
  try
  {
    std::string name(argv[1]);
    KeySum f;
    cmds.at(name)(std::cout, tree, f);
    std::cout << '\n';
  }
  catch (const std::out_of_range&)
  {
    std::cerr << "Incorrect traversal order";
    return 1;
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
