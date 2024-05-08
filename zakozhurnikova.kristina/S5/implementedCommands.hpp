#ifndef IMPLEMENTED_COMMANDS_HPP
#define IMPLEMENTED_COMMANDS_HPP
#include <string>
#include <list.hpp>
#include <binarySearchTree.hpp>

namespace zakozhurnikova
{
  using map = BinarySearchTree< long long, std::string >;
  struct ImplementedCommands
  {
    explicit ImplementedCommands(BinarySearchTree< long long, std::string >& map);
    long long executeCommand(std::string& command, std::string& result);

  private:
    using command = long long(ImplementedCommands::*)(std::string&);
    BinarySearchTree< long long, std::string >& map_;
    BinarySearchTree< std::string, command > commands_;

    long long ascending(std::string& result);
    long long descending(std::string& result);
    long long breadth(std::string& result);
  };
}

#endif
