#ifndef HASH_TABLE_ITERATORS_HPP
#define HASH_TABLE_ITERATORS_HPP

#include <iterator>
#include <list>
#include <utility>
#include "hash_table_node.hpp"

namespace namestnikov
{
  template< class Key, class Value >
  class HashTable;

  template< class Key, class Value >
  class HashTableIterator: public std::iterator< std::forward_iterator_tag, std::pair< const Key, Value > > 
  {
    
  };
}

#endif