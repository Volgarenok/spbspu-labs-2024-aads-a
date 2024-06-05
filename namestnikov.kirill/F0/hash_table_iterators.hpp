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
    friend class HashTable< Key, Value >;
  public:
    using val_type_t = std::pair< const Key, Value >;
    using node_t = HashTableNode< Value >;
    using list_iterator_t = typename std::list< node_t * >::iterator;
    using hash_table_iterator = HashTableIterator< Key, Value >;
    explicit HashTableIterator(list_iterator_t data):
      iter_(data)
    {}
    HashTableIterator(const hash_table_iterator &) = default;
    hash_table_iterator & operator=(const hash_table_iterator &) = default;
    bool operator==(const hash_table_iterator & other) const
    {
      return (iter_ == other.iter_);
    }
    bool operator!=(const hash_table_iterator & other) const
    {
      return !(*this == other);
    }
    val_type_t & operator*()
    {
      return (**iter_).data;
    }
    const val_type_t & operator*() const
    {
      return (**iter_).data;
    }
    val_type_t * operator->()
    {
      return std::addressof(**this);
    }
    const val_type_t * operator->() const
    {
      return std::addressof(**this);
    }
    hash_table_iterator & operator++()
    {
      ++iter_;
      return *this;
    }
    hash_table_iterator & operator++(int)
    {
      hash_table_iterator temp(*this);
      ++(*this);
      return temp;
    }
    ~HashTableIterator() = default;
  private:
    list_iterator_t iter_;
  };
}

#endif