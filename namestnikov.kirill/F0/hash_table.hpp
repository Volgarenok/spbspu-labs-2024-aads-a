#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <initializer_list>
#include <stdexcept>
#include "hash_table_node.hpp"
#include "hash_table_iterators.hpp"
#include "const_hash_table_iterators.hpp"

namespace namestnikov
{
  template< class Key, class Value >
  class HashTable
  {
  public:
    using val_type_t = std::pair< const Key, Value >;
    using node_t = HashTableNode< val_type_t >;
    using list_iterator_t = typename std::list< node_t * >::iterator;
    using hash_table_iterator = HashTableIterator< Key, Value >;
    using const_hash_table_iterator = ConstHashTableIterator< Key, Value >;
  };
}

#endif