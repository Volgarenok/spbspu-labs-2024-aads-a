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
    explicit ImplementedCommands(BinarySearchTree< std::string, map >& maps);
    void executeCommand(std::istream& in, std::string& result);

  private:
    using command = void (ImplementedCommands::*)(List< std::string >&, std::string&);
    BinarySearchTree< std::string, map >& maps_;
    BinarySearchTree< std::string, command > commands_;

    void print(List< std::string >& args, std::string& result);
    void complement(List< std::string >& args, std::string& result);
    void intersect(List< std::string >& args, std::string& result);
    void doUnion(List< std::string >& args, std::string& result);

    void addMap(std::string& mapName, map& toAdd);
  };
}

#endif
