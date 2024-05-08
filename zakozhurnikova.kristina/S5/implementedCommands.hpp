#ifndef IMPLEMENTED_COMMANDS_HPP
#define IMPLEMENTED_COMMANDS_HPP
#include <string>
#include <list.hpp>
#include <binarySearchTree.hpp>

namespace zakozhurnikova
{
  using map = BinarySearchTree< int, std::string >;
  struct ImplementedCommands
  {
    explicit ImplementedCommands(BinarySearchTree< int, std::string >& map);
    int executeCommand(std::string& command, std::string& result);

  private:
    using command = int (ImplementedCommands::*)(std::string&);
    BinarySearchTree< int, std::string >& map_;
    BinarySearchTree< std::string, command > commands_;

    int ascending(std::string& result);
    int descending(std::string& result);
    int breadth(std::string& result);
  };
}

#endif
