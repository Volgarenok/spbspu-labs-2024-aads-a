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
    using Command = void (*)(List< std::string >&, std::string&, BinarySearchTree< std::string, map >&);
    explicit ImplementedCommands(BinarySearchTree< std::string, map >& maps);
    void executeCommand(std::istream& in, std::string& result);
    void addCommand(const std::string& nameCommand, Command command);

  private:
    BinarySearchTree< std::string, map >& maps_;
    BinarySearchTree< std::string, Command > commands_;

  };
}

#endif
