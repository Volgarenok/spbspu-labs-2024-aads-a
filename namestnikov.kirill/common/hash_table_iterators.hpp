#ifndef HASH_TABLE_ITERATORS_HPP
#define HASH_TABLE_ITERATORS_HPP

#include <iterator>
#include <utility>
#include <bidirectional_list.hpp>
#include <hash_table_node.hpp>
#include <const_hash_table_iterators.hpp>

namespace namestnikov
{
  template< class Key, class Value >
  class HashTable;

  template< class Key, class Value >
  class ConstHashTableIterator;

  template< class Key, class Value >
  class HashTableIterator: public std::iterator< std::forward_iterator_tag, std::pair< const Key, Value > >
  {
    friend class HashTable< Key, Value >;
    friend class ConstHashTableIterator< Key, Value >;
  public:
    using val_type_t = std::pair< const Key, Value >;
    using ListNode = detail::HashTableNode< val_type_t >;
    using ListIterator = typename List< ListNode* >::iterator;
    using hash_table_iterator = HashTableIterator< Key, Value >;
    using const_hash_table_iterator = ConstHashTableIterator< Key, Value >;
    HashTableIterator(const hash_table_iterator &) = default;
    hash_table_iterator & operator=(const hash_table_iterator &) = default;
    HashTableIterator(hash_table_iterator &&) = default;

    bool operator==(const hash_table_iterator & other) const
    {
      return listIter_ == other.listIter_;
    }
    bool operator!=(const hash_table_iterator & other) const
    {
      return !(*this == other);
    }
    bool operator==(const_hash_table_iterator && other) const
    {
      return (listIter_ == other.listIter_);
    }
    bool operator!=(const_hash_table_iterator && other) const
    {
      return (listIter_ != other.listIter_);
    }
    val_type_t & operator*()
    {
      return (*listIter_)->data;
    }
    const val_type_t & operator*() const
    {
      return (*listIter_)->data;
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
      ++listIter_;
      return *this;
    }
    hash_table_iterator operator++(int)
    {
      hash_table_iterator temp(*this);
      ++(*this);
      return temp;
    }
    ~HashTableIterator() = default;
  private:
    ListIterator listIter_;
    explicit HashTableIterator(ListIterator current):
      listIter_(current)
    {}
  };
}

#endif
