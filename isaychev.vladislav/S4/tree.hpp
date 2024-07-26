#ifndef TREE_HPP
#define TREE_HPP

#include <functional>
#include <stdexcept>
#include "treeNode.hpp"

namespace isaychev
{
  template < class Key, class Value, class Compare = std::less< Key > >
  class BSTree
  {
    using Tree = BSTree< Key, Value, Compare >;
    using Node = detail::TreeNode< Key, Value >;

   public:
    BSTree();

    //begin();
    //end();

    size_t size() const noexcept;
    void clear() noexcept;
    void swap(Tree & other) noexcept;
    //find(const Key & key) const;
    //at();
    //operator[]();

   private:
    detail::TreeNode< Key, Value > * root_;
    Compare cmp_;
    size_t size_;

    void delete_tree(Node * ptr) noexcept;
  };

  template < class Key, class Value, class Compare >
  BSTree< Key, Value, Compare >::BSTree():
   root_(nullptr),
   cmp_(),
   size_(0)
  {}

  template < class Key, class Value, class Compare >
  size_t BSTree< Key, Value, Compare >::size() const noexcept
  {
    return size_;
  }

  template < class Key, class Value, class Compare >
  void BSTree< Key, Value, Compare >::delete_tree(Node * root) noexcept
  {
    if (root)
    {
      delete_tree(root->left);
      delete_tree(root->right);
      delete root;
    }
  }

  template < class Key, class Value, class Compare >
  void BSTree< Key, Value, Compare >::clear() noexcept
  {
    delete_tree(root_);
  }

  template < class Key, class Value, class Compare >
  void BSTree< Key, Value, Compare >::swap(Tree & other) noexcept
  {
    std::swap(root_, other.root_);
    std::swap(cmp_, other.cmp_);
    std::swap(size_, other.size_);
  }

  //template < class Key, class Value, class Compare >
  //find(const Key & key) const;

/*  template < class Key, class Value, class Compare >
  T & BSTree< Key, Value, Compare >::at(const Key & key)
  {
  }*/

  //operator[]();
}

#endif
