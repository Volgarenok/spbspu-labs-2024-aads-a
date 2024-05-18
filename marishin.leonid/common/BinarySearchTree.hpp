#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

namespace marishin
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  struct BinarySearchTree
  {
    void push(Key k, Value v);
    Value get(Key k);
    Value drop(Key k);
  };

}



#endif
