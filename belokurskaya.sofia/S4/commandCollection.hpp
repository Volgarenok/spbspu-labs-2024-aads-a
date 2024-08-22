#ifndef COMMAND_COLLECTION_HPP
#define COMMAND_COLLECTION_HPP

#include <string>
#include <functional>

#include "binarySearchTree.hpp"
#include "dictionaryCollection.hpp"

using DictCol = belokurskaya::DictionaryCollection&;
using fnc = std::function< void(DictCol, std::istream& in) >;

namespace belokurskaya
{
  struct CommandEntry
  {
    std::string name;
    fnc func;
  };

  class CommandCollection
  {
    public:
      CommandCollection();
      ~CommandCollection();

      void add(const std::string& name, fnc func);
      fnc* find(const std::string& name);
      fnc at(const std::string& name);

    private:
      void resize();

      CommandEntry* entries;
      size_t capacity;
      size_t size;
      BinarySearchTree< std::string, fnc > commands_;
  };
}


#endif
