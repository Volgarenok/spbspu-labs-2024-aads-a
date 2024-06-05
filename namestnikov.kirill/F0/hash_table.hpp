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
    HashTable():
      capacity_(5),
      count_(0),
      buckets_(new list_iterator_t[5]),
      elements_()
    {
      for (size_t i = 0; i < 5; ++i)
      {
        buckets_[i] = elements_.end();
      }
    }
    HashTable(std::initializer_list< val_type_t > initList):
      capacity_(initList.size() / 0.75 + 1),
      count_(0),
      buckets_(new list_iterator_t[initList.size() / 0.75 + 1]),
      elements_()
    {
      for (size_t i = 0; i < capacity_; ++i)
      {
        buckets_[i] = elements_.end();
      }
      auto it = initList.begin();
      for (; it != initList.end(); ++it)
      {
        insert((*it).first, (*it).second);
      }
    }
  private:
    size_t count_;
    size_t capacity_;
    std::list< node_t * > elements_;
    list_iterator_t * buckets_;
  };
}

#endif