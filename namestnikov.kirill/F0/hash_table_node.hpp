#ifndef HASH_TABLE_NODE_HPP
#define HASH_TABLE_NODE_HPP

namespace namestnikov
{
  template< class T >
  struct HashTableNode
  {
    T data;
    size_t hash;
    HashTableNode(const T & value, size_t h):
      data(value),
      hash(h)
    {}
  };
}

#endif