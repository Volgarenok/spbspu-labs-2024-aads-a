#ifndef CONST_HASH_TABLE_ITERATORS_HPP
#define CONST_HASH_TABLE_ITERATORS_HPP

#include <iterator>
#include <list>
#include <utility>
#include "hash_table_node.hpp"

namespace namestnikov
{
  template< class Key, class Value >
  class HashTable;

  template< class Key, class Value >
  class ConstHashTableIterator: public std::iterator< std::forward_iterator_tag, std::pair< const Key, Value > >
  {
    friend class HashTable< Key, Value >;
  public:
    using val_type_t = std::pair< const Key, Value >;
    using node_t = detail::HashTableNode< val_type_t >;
    using list_iterator_t = typename std::list< node_t * >::iterator;
    using const_list_iterator_t = typename std::list< node_t * >::const_iterator;
    using const_hash_table_iterator = ConstHashTableIterator< Key, Value >;
    explicit ConstHashTableIterator(const_list_iterator_t data):
      iter_(data)
    {}
    explicit ConstHashTableIterator(list_iterator_t data):
      iter_(const_list_iterator_t(data))
    {}
    ConstHashTableIterator(const const_hash_table_iterator &) = default;
    const_hash_table_iterator & operator=(const const_hash_table_iterator &) = default;
    bool operator==(const const_hash_table_iterator & other) const
    {
      return (iter_ == other.iter_);
    }
    bool operator!=(const const_hash_table_iterator & other) const
    {
      return !(*this == other);
    }
    const val_type_t & operator*() const
    {
      return (**iter_).data;
    }
    const val_type_t * operator->() const
    {
      return std::addressof(**this);
    }
    const_hash_table_iterator & operator++()
    {
      ++iter_;
      return *this;
    }
    const_hash_table_iterator operator++(int)
    {
      const_hash_table_iterator temp(*this);
      ++(*this);
      return temp;

    }
    ~ConstHashTableIterator() = default;
  private:
    const_list_iterator_t iter_;
  };
}

#endif