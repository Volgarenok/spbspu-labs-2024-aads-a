#ifndef IMPLEMENTED_COMMANDS_HPP
#define IMPLEMENTED_COMMANDS_HPP
#include <string>
#include <binarySearchTree.hpp>
#include <list.hpp>

namespace zakozhurnikova
{
  using map = BinarySearchTree< int, std::string >;
  struct ImplementedCommands
  {
    using Command = void (*)(List< std::string >&, std::string&, BinarySearchTree< std::string, map >&);
    using PrintCmd = void(*)(const List< std::string >&, std::string&, const BinarySearchTree< std::string, map >&);
    explicit ImplementedCommands(BinarySearchTree< std::string, map >& maps);
    void executeCommand(std::istream& in, std::string& result);
    void addCommand(const std::string& nameCommand, Command command);
    void addCommand(const std::string& nameCommand, PrintCmd command);

  private:
    BinarySearchTree< std::string, map >& maps_;
    BinarySearchTree< std::string, Command > commands_;
    BinarySearchTree< std::string, PrintCmd > printCmd_;
  };
}

#endif
