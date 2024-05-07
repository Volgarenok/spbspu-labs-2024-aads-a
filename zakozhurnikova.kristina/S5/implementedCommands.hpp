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
    explicit ImplementedCommands(BinarySearchTree< int, std::string > map);
    void executeCommand(std::string& command, std::string& result);

  private:
//параметры    
    using command = void (ImplementedCommands::*)(std::string&);
    BinarySearchTree< int, std::string >& map_;
    BinarySearchTree< std::string, command > commands_;

    void ascending(std::string& result);
    void descending(std::string& result);
    void breadth(std::string& result);
  };
}

#endif
