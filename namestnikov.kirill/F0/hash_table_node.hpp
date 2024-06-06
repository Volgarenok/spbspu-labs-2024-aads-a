#ifndef HASH_TABLE_NODE_HPP
#define HASH_TABLE_NODE_HPP

#include <cstddef>

namespace namestnikov
{
  namespace detail
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
}

#endif
