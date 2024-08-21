#ifndef COMMAND_COLLECTION_HPP
#define COMMAND_COLLECTION_HPP

#include <string>
#include <functional>

#include "binarySearchTree.hpp"
#include "dictionaryCollection.hpp"

using fnc = std::function< void(belokurskaya::DictionaryCollection&, std::istream&, std::ostream&) >;

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

    private:
      void resize();

      CommandEntry* entries;
      size_t capacity;
      size_t size;
  };
}


#endif
