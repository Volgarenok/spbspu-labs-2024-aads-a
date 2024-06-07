#ifndef CONST_HASH_TABLE_ITERATORS_HPP
#define CONST_HASH_TABLE_ITERATORS_HPP

#include <iterator>
#include <utility>
#include <bidirectional_list.hpp>
#include <hash_table_node.hpp>
#include <hash_table_iterators.hpp>

namespace namestnikov
{
  template< class Key, class Value >
  class HashTable;

  template< class Key, class Value >
  class HashTableIterator;

  template< class Key, class Value >
  class ConstHashTableIterator: public std::iterator< std::forward_iterator_tag, std::pair< const Key, Value > >
  {
    friend class HashTable< Key, Value >;
    friend class HashTableIterator< Key, Value >;
  public:
    using val_type_t = std::pair< const Key, Value >;
    using ListNode = detail::HashTableNode< val_type_t >;
    using ListIterator = typename List< ListNode* >::iterator;
    using ConstListIterator = typename List< ListNode* >::const_iterator;
    using hash_table_iterator = HashTableIterator< Key, Value >;
    using const_hash_table_iterator = ConstHashTableIterator< Key, Value >;
    explicit ConstHashTableIterator(ConstListIterator current):
      listIter_(current)
    {}
    explicit ConstHashTableIterator(ListIterator current):
      listIter_(ConstListIterator(current))
    {}
    ~ConstHashTableIterator() = default;
    ConstHashTableIterator(const const_hash_table_iterator &) = default;
    const_hash_table_iterator & operator=(const const_hash_table_iterator &) = default;
    ConstHashTableIterator(const_hash_table_iterator &&) = default;
    bool operator==(const const_hash_table_iterator & other) const
    {
      return (listIter_ == other.listIter_);
    }
    bool operator!=(const const_hash_table_iterator & other) const
    {
      return !(*this == other);
    }
    bool operator==(hash_table_iterator && other)
    {
      return (listIter_ == other.listIter_);
    }
    bool operator!=(hash_table_iterator && other)
    {
      return (listIter_ != other.listIter_);
    }
    const val_type_t & operator*() const
    {
      return (*listIter_)->data;
    }
    const val_type_t * operator->() const
    {
      return std::addressof(**this);
    }
    const_hash_table_iterator & operator++()
    {
      ++listIter_;
      return *this;
    }
    const_hash_table_iterator operator++(int)
    {
      const_hash_table_iterator temp(*this);
      ++(*this);
      return temp;
    }
  private:
    ConstListIterator listIter_;
  };
}

#endif
