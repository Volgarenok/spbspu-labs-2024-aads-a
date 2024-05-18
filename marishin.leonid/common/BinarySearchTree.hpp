#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

namespace marishin
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  struct BinarySearchTree
  {
    using node_t = detail::TreeNode< Key, Value >;
    BinarySearchTree():
      root_(nullptr),
      size_(0)
    {}

    BinarySearchTree(const BinarySearchTree& rhs):
      root_(nullptr),
      size_(0)
    {
      try
      {
        for (auto begin = rhs.cbegin(); begin != rhs.cend(); ++begin)
        {
          insert(begin->first, begin->second);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
  };

}



#endif
