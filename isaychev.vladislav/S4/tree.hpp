#ifndef TREE_HPP
#define TREE_HPP

#include <functional>
#include <stdexcept>
#include "treeIter.hpp"

namespace isaychev
{
  template < class Key, class Value, class Compare = std::less< Key > >
  class BSTree
  {
    using Tree = BSTree< Key, Value, Compare >;
    using node_t = detail::TreeNode< Key, Value >;
    using const_iterator = ConstTreeIter< Key, Value, Compare >;
    using iterator = TreeIter< Key, Value, Compare >;
    using value_t = std::pair< Key, Value >;

   public:
    BSTree();
    ~BSTree();
    BSTree(const Tree & rhs);
    BSTree(Tree && rhs);
    Tree & operator=(const Tree & rhs);
    Tree & operator=(Tree && rhs);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    size_t size() const noexcept;
    bool empty() const noexcept;
    void clear() noexcept;
    void swap(Tree & other) noexcept;
    iterator find(const Key & key);
    const_iterator find(const Key & key) const;

    Value & at(const Key & key);
    const Value & at(const Key & key) const;
    Value & operator[](const Key & key);
    std::pair< iterator, bool > insert(const value_t & value);

   private:
    node_t * root_;
    Compare cmp_;
    size_t size_;

    void delete_tree(node_t * ptr) noexcept;
    void copy_tree(const Tree & rhs);
    node_t * traverse_left(node_t * root) const;
    std::pair< node_t *, bool > insert_new(const value_t & value);
  };

  template < class Key, class Value, class Compare >
  BSTree< Key, Value, Compare >::BSTree():
   root_(nullptr),
   cmp_(),
   size_(0)
  {}

  template < class Key, class Value, class Compare >
  BSTree< Key, Value, Compare >::~BSTree()
  {
    clear();
  }

  template < class Key, class Value, class Compare >
  void BSTree< Key, Value, Compare >::copy_tree(const Tree & rhs)
  {
    for (auto i = rhs.begin(); i != rhs.end(); ++i)
    {
      (*this)[(*i).first] = (*i).second;
    }
  }

  template < class Key, class Value, class Compare >
  BSTree< Key, Value, Compare >::BSTree(const Tree & rhs):
   root_(nullptr),
   cmp_(rhs.cmp_),
   size_(0)
  {
    copy_tree(rhs);
  }

  template < class Key, class Value, class Compare >
  BSTree< Key, Value, Compare >::BSTree(Tree && rhs):
   root_(rhs.root_),
   cmp_(rhs.cmp_),
   size_(rhs.size_)
  {
    rhs.root_ = nullptr;
    rhs.size_ = 0;
  }

  template < class Key, class Value, class Compare >
  BSTree< Key, Value, Compare > & BSTree< Key, Value, Compare >::operator=(Tree && rhs)
  {
    if (this != std::addressof(rhs))
    {
      root_ = rhs.root_;
      cmp_ = rhs.cmp_;
      size_ = rhs.size_;
      rhs.root_ = nullptr;
      rhs.size_ = 0;
    }
    return *this;
  }

  template < class Key, class Value, class Compare >
  BSTree< Key, Value, Compare > & BSTree< Key, Value, Compare >::operator=(const Tree & rhs)
  {
    clear();
    cmp_ = rhs.cmp_;
    copy_tree(rhs);
    return *this;
  }

  template < class Key, class Value, class Compare >
  detail::TreeNode< Key, Value > * BSTree< Key, Value, Compare >::traverse_left(node_t * root) const
  {
    if (root)
    {
      while (root->left)
      {
        root = root->left;
      }
    }
    return root;
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::begin()
  {
    return TreeIter< Key, Value, Compare >(traverse_left(root_));
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::end()
  {
    return TreeIter< Key, Value, Compare >();
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::begin() const
  {
    return ConstTreeIter< Key, Value, Compare >(traverse_left(root_));
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::end() const
  {
    return ConstTreeIter< Key, Value, Compare >();
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::cbegin() const
  {
    return ConstTreeIter< Key, Value, Compare >(traverse_left(root_));
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::cend() const
  {
    return ConstTreeIter< Key, Value, Compare >();
  }

  template < class Key, class Value, class Compare >
  size_t BSTree< Key, Value, Compare >::size() const noexcept
  {
    return size_;
  }

  template < class Key, class Value, class Compare >
  bool BSTree< Key, Value, Compare >::empty() const noexcept
  {
    return root_ == nullptr;
  }

  template < class Key, class Value, class Compare >
  void BSTree< Key, Value, Compare >::delete_tree(node_t * root) noexcept
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
    root_ = nullptr;
    size_ = 0;
  }

  template < class Key, class Value, class Compare >
  void BSTree< Key, Value, Compare >::swap(Tree & other) noexcept
  {
    std::swap(root_, other.root_);
    std::swap(cmp_, other.cmp_);
    std::swap(size_, other.size_);
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::find(const Key & key)
  {
    node_t * current = root_;
    while (current)
    {
      if (key == current->data.first)
      {
        return TreeIter< Key, Value, Compare >(current);
      }
      if (cmp_(key, current->data.first))
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }
    }
    return end();
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::find(const Key & key) const
  {
    node_t * current = root_;
    while (current)
    {
      if (key == current->data.first)
      {
        return ConstTreeIter< Key, Value, Compare >(current);
      }
      if (cmp_(key, current->data.first))
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      } //mpjno vinesti v func if{} else{}
    }
    return cend();
  }

  template < class Key, class Value, class Compare >
  Value & BSTree< Key, Value, Compare >::at(const Key & key)
  {
    iterator value_iter = find(key);
    if (!value_iter.current_)
    {
      throw std::out_of_range("no element with such key");
    }
    return (*value_iter).second;
  }

  template < class Key, class Value, class Compare >
  const Value & BSTree< Key, Value, Compare >::at(const Key & key) const
  {
    const_iterator value_iter = find(key);
    if (!value_iter.current_)
    {
      throw std::out_of_range("no element with such key");
    }
    return (*value_iter).second;
  }

  template < class Key, class Value, class Compare >
  Value & BSTree< Key, Value, Compare >::operator[](const Key & key)
  {
    auto result = insert_new(std::make_pair(key, Value()));
    return result.first->data.second;
  }

  template < class Key, class Value, class Compare >
  std::pair< TreeIter< Key, Value, Compare >, bool > BSTree< Key, Value, Compare >::insert(const value_t & value)
  {
    auto result = insert_new(value);
    return std::pair< iterator, bool >(iterator(result.first), result.second);
  }

  template < class Key, class Value, class Compare >
  std::pair< detail::TreeNode< Key, Value > *, bool > BSTree< Key, Value, Compare >::insert_new(const value_t & value)
  {
    if (!root_)
    {
      root_ = new node_t(value.first, value.second, nullptr);
      ++size_;
      return std::pair< node_t *, bool >(root_, true);
    }
    node_t * current = root_;
    while (current)
    {
      if (value.first == current->data.first)
      {
        return std::pair< node_t *, bool >(current, false);
      }
      if (cmp_(value.first, current->data.first))
      {
        if (!current->left)
        {
          current->left = new node_t(value.first, value.second, current);
          current = current->left;
          break;
        }
        current = current->left;
      }
      else
      {
        if (!current->right)
        {
          current->right = new node_t(value.first, value.second, current);
          current = current->right;
          break;
        }
        current = current->right;
      }
    }
    ++size_;
    return std::pair< node_t *, bool >(current, true);
  }
}

#endif
