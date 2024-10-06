#ifndef DICTIONARY_COLLECTION_HPP
#define DICTIONARY_COLLECTION_HPP

#include "binarySearchTree.hpp"

using Dictionary = belokurskaya::BinarySearchTree< int, std::string >;

namespace belokurskaya
{
  struct DictionaryEntry
  {
    std::string name;
    Dictionary dict;
  };

  class DictionaryCollection
  {
    public:
      DictionaryCollection();
      ~DictionaryCollection();

      void add(const std::string& name, Dictionary dict);
      Dictionary* find(const std::string& name);

    private:
      void resize();

      DictionaryEntry* entries;
      size_t capacity;
      size_t size;
  };
}



#endif
