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
    using Command = int(*)(std::string&, map&);
    explicit ImplementedCommands(BinarySearchTree< int, std::string >& map);
    int executeCommand(std::string& command, std::string& result);
    void addCommand(const std::string& nameCommand, Command command);

  private:
    BinarySearchTree< int, std::string >& map_;
    BinarySearchTree< std::string, Command > commands_;
  };
}

#endif
