#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <functional>
#include "node.hpp"

namespace strelyaev
{
  template< typename T, typename Comp = std::less< T > >
  class Tree
  {
    public:
      Tree():
        root(nullptr)
      {}

      void insert(T value)
      {
        if (!root)
        {
          root = new Node< T >(nullptr, nullptr, nullptr, value);
          return;
        }
      }
    private:
      Node< T >* root;
  };
}

#endif

