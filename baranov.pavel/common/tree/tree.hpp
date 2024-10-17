#ifndef TREE
#define TREE
#include <functional>
#include <cstddef>
#include <stdexcept>
#include <tree/treeIterator.hpp>
#include <tree/treeConstIterator.hpp>
#include <tree/treeNode.hpp>
#include <stack.hpp>

namespace baranov
{
  template< typename Key, typename T, typename Compare = std::less< Key > >
  class Tree
  {
  public:
    using this_t = Tree< Key, T, Compare >;
    using iterator_t = TreeIterator< Key, T, Compare >;
    using const_iterator_t = TreeConstIterator< Key, T, Compare >;
    using node_t = TreeNode< Key, T >;
    Tree();
    Tree(const Tree & rhs);
    Tree(Tree && rhs) noexcept;
    Tree & operator=(const Tree & rhs);
    Tree & operator=(Tree && rhs) noexcept;
    ~Tree();
    iterator_t begin();
    iterator_t rbegin();
    iterator_t end();
    const_iterator_t cbegin() const;
    const_iterator_t crbegin() const;
    const_iterator_t cend() const;
    std::pair< iterator_t, bool > insert(const Key & key, const T & val);
    std::pair< iterator_t, bool > insert(const std::pair< Key, T > & pair);
    T & at(const Key & key);
    const T & at(const Key & key) const;
    T & operator[](const Key & key);
    const T & operator[](const Key & key) const;
    iterator_t find(const Key & key);
    const_iterator_t find(const Key & key) const;
    size_t size() const noexcept;
    bool empty() const noexcept;
    void clear() noexcept;
    void erase(iterator_t pos);
    void erase(const_iterator_t pos);
    void swap(this_t & rhs);

    template < typename F >
    F traverse_lnr(F f);
    template < typename F >
    F traverse_lnr(F f) const;

    template < typename F >
    F traverse_rnl(F f);
    template < typename F >
    F traverse_rnl(F f) const;

    template < typename F >
    F traverse_breadth(F f);
    template < typename F >
    F traverse_breadth(F f) const;

  private:
    void clear(node_t * node) noexcept;
    void erase(node_t * todelete);
    TreeNode< Key, T > * root_;
    size_t size_;
  };

  template< typename Key, typename T, typename Compare >
  Tree< Key, T, Compare >::Tree():
    root_(nullptr),
    size_(0)
  {}

  template< typename Key, typename T, typename Compare >
  Tree< Key, T, Compare >::Tree(const Tree & rhs) :
    root_(nullptr),
    size_(0)
  {
    try
    {
      for (auto it = rhs.cbegin(); it != rhs.cend(); ++it)
      {
        insert(*it);
      }
    }
    catch (...)
    {
      clear();
      throw;
    }
  }

  template< typename Key, typename T, typename Compare >
  Tree< Key, T, Compare >::Tree(Tree && rhs) noexcept:
    root_(rhs.root_),
    size_(rhs.size_)
  {
    rhs.root_ = nullptr;
    rhs.size_ = 0;
  }

  template< typename Key, typename T, typename Compare >
  Tree< Key, T, Compare > & Tree< Key, T, Compare >::operator=(const Tree & rhs)
  {
    if (std::addressof(rhs) != this)
    {
      Tree< Key, T, Compare > newtree(rhs);
      swap(newtree);
    }
    return *this;
  }

  template< typename Key, typename T, typename Compare >
  Tree< Key, T, Compare > & Tree< Key, T, Compare >::operator=(Tree && rhs) noexcept
  {
    if (std::addressof(rhs) != this)
    {
      clear();
      swap(rhs);
    }
    return *this;
  }

  template< typename Key, typename T, typename Compare >
  Tree< Key, T, Compare >::~Tree()
  {
    clear();
  }

  template< typename Key, typename T, typename Compare >
  TreeIterator< Key, T, Compare > Tree< Key, T, Compare >::begin()
  {
    if (root_ == nullptr)
    {
      return iterator_t();
    }
    node_t * node = root_;
    while(node->hasLeft())
    {
      node = node->left_;
    }
    return iterator_t(node);
  }

  template< typename Key, typename T, typename Compare >
  TreeIterator< Key, T, Compare > Tree< Key, T, Compare >::rbegin()
  {
    if (root_ == nullptr)
    {
      return iterator_t();
    }
    node_t * node = root_;
    while(node->hasRight())
    {
      node = node->right_;
    }
    return iterator_t(node);
  }

  template< typename Key, typename T, typename Compare >
  TreeIterator< Key, T, Compare > Tree< Key, T, Compare >::end()
  {
    return iterator_t();
  }

  template< typename Key, typename T, typename Compare >
  TreeConstIterator< Key, T, Compare > Tree< Key, T, Compare >::cbegin() const
  {
    if (root_ == nullptr)
    {
      return const_iterator_t();
    }
    node_t * node = root_;
    while(node->hasLeft())
    {
      node = node->left_;
    }
    return const_iterator_t(node);
  }

  template< typename Key, typename T, typename Compare >
  TreeConstIterator< Key, T, Compare > Tree< Key, T, Compare >::crbegin() const
  {
    if (root_ == nullptr)
    {
      return const_iterator_t();
    }
    node_t * node = root_;
    while(node->hasRight())
    {
      node = node->right_;
    }
    return const_iterator_t(node);
  }

  template< typename Key, typename T, typename Compare >
  TreeConstIterator< Key, T, Compare > Tree< Key, T, Compare >::cend() const
  {
    return const_iterator_t();
  }

  template< typename Key, typename T, typename Compare >
  std::pair< TreeIterator< Key, T, Compare >, bool > Tree< Key, T, Compare >::insert(const Key & key, const T & val)
  {
    if (empty())
    {
      root_ = new node_t(key, val, nullptr, nullptr, nullptr);
      ++size_;
      return std::make_pair(iterator_t(root_), true);
    }
    node_t * node = root_;
    while (node)
    {
      if (key == node->data_.first)
      {
        break;
      }
      else if (Compare()(node->data_.first, key))
      {
        if (!node->hasRight())
        {
          node->right_ = new node_t(key, val, nullptr, nullptr, node);
          ++size_;
          return std::make_pair(iterator_t(node->right_), true);
        }
        node = node->right_;
      }
      else
      {
        if (!node->hasLeft())
        {
          node->left_ = new node_t(key, val, nullptr, nullptr, node);
          ++size_;
          return std::make_pair(iterator_t(node->left_), true);
        }
        node = node->left_;
      }
    }
    return std::make_pair(iterator_t(node), false);
  }

  template< typename Key, typename T, typename Compare >
  std::pair< TreeIterator< Key, T, Compare >, bool > Tree< Key, T, Compare >::insert(const std::pair< Key, T > & pair)
  {
    return insert(pair.first, pair.second);
  }

  template< typename Key, typename T, typename Compare >
  T & Tree< Key, T, Compare >::at(const Key & key)
  {
    iterator_t it = find(key);
    if (it == end())
    {
      throw std::out_of_range("Invalid key");
    }
    return it->second;
  }

  template< typename Key, typename T, typename Compare >
  const T & Tree< Key, T, Compare >::at(const Key & key) const
  {
    const_iterator_t it = find(key);
    if (it == cend())
    {
      throw std::out_of_range("Invalid key");
    }
    return it->second;
  }

  template< typename Key, typename T, typename Compare >
  T & Tree< Key, T, Compare >::operator[](const Key & key)
  {
    iterator_t it = find(key);
    if (it == end())
    {
      it = insert(key, T()).first;
    }
    return it->second;
  }

  template< typename Key, typename T, typename Compare >
  const T & Tree< Key, T, Compare >::operator[](const Key & key) const
  {
    const_iterator_t it = find(key);
    if (it == end())
    {
      it = insert(key, T()).first;
    }
    return it->second;
  }

  template< typename Key, typename T, typename Compare >
  TreeIterator< Key, T, Compare > Tree< Key, T, Compare >::find(const Key & key)
  {
    node_t * node = root_;
    while (node && node->data_.first != key)
    {
      if (Compare()(node->data_.first, key))
      {
        node = node->right_;
      }
      else
      {
        node = node->left_;
      }
    }
    return iterator_t(node);
  }

  template< typename Key, typename T, typename Compare >
  TreeConstIterator< Key, T, Compare > Tree< Key, T, Compare >::find(const Key & key) const
  {
    node_t * node = root_;
    while (node && node->data_.first != key)
    {
      if (Compare()(node->data_.first, key))
      {
        node = node->right_;
      }
      else
      {
        node = node->left_;
      }
    }
    return const_iterator_t(node);
  }

  template< typename Key, typename T, typename Compare >
  size_t Tree< Key, T, Compare >::size() const noexcept
  {
    return size_;
  }

  template< typename Key, typename T, typename Compare >
  bool Tree< Key, T, Compare >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename Key, typename T, typename Compare >
  void Tree< Key, T, Compare >::swap(this_t & rhs)
  {
    std::swap(root_, rhs.root_);
    std::swap(size_, rhs.size_);
  }

  template< typename Key, typename T, typename Compare >
  void Tree< Key, T, Compare >::clear() noexcept
  {
    clear(root_);
    root_ = nullptr;
    size_ = 0;
  }

  template< typename Key, typename T, typename Compare >
  void Tree< Key, T, Compare >::clear(node_t * node) noexcept
  {
    if (node != nullptr)
    {
      clear(node->left_);
      clear(node->right_);
      delete node;
      --size_;
    }
  }

  template< typename Key, typename T, typename Compare >
  void Tree< Key, T, Compare >::erase(iterator_t pos)
  {
    node_t * todelete = pos.node_;
    erase(todelete);
  }

  template< typename Key, typename T, typename Compare >
  void Tree< Key, T, Compare >::erase(const_iterator_t pos)
  {
    node_t * todelete = pos.node_;
    erase(todelete);
  }

  template< typename Key, typename T, typename Compare >
  void Tree< Key, T, Compare >::erase(node_t * todelete)
  {
    if (size_ <= 1)
    {
      clear();
      return;
    }
    if (!todelete->hasLeft() && !todelete->hasRight() && !todelete->isRoot())
    {
      (todelete->isRight() ? todelete->parent_->right_ : todelete->parent_->left_) = nullptr;
    }
    else if (todelete->hasLeft() && todelete->hasRight())
    {
      if (todelete->isRoot())
      {
        root_ = todelete->left_;
      }
      else
      {
        (todelete->isRight() ? todelete->parent_->right_ : todelete->parent_->left_) = todelete->left_;
      }
      todelete->left_->parent_ = todelete->parent_;
      node_t * node = todelete->left_;
      while (node->hasRight())
      {
        node = node->right_;
      }
      node->right_ = todelete->right_;
      node->right_->parent_ = node;
    }
    else
    {
      if (todelete->isRoot())
      {
        root_ = todelete->hasRight() ? todelete->right_ : todelete->left_;
      }
      else
      {
        node_t * tmp = todelete->hasRight() ? todelete->right_ : todelete->left_;
        (todelete->isRight() ? todelete->parent_->right_ : todelete->parent_->left_) = tmp;
      }
      (todelete->hasRight() ? todelete->right_->parent_ : todelete->left_->parent_) = todelete->parent_;
    }
    delete todelete;
    --size_;
  }

  template< typename Key, typename T, typename Compare >
  template < typename F >
  F Tree< Key, T, Compare >::traverse_lnr(F f)
  {
    if (empty())
    {
      throw std::invalid_argument("Tree is empty");
    }
    for (auto it = begin(); it != end(); ++it)
    {
      f(*it);
    }
    return f;
  }

  template< typename Key, typename T, typename Compare >
  template < typename F >
  F Tree< Key, T, Compare >::traverse_lnr(F f) const
  {
    if (empty())
    {
      throw std::invalid_argument("Tree is empty");
    }
    for (auto it = cbegin(); it != cend(); ++it)
    {
      f(*it);
    }
    return f;
  }

  template< typename Key, typename T, typename Compare >
  template < typename F >
  F Tree< Key, T, Compare >::traverse_rnl(F f)
  {
    if (empty())
    {
      throw std::invalid_argument("Tree is empty");
    }
    for (auto it = rbegin(); it != end(); --it)
    {
      f(*it);
    }
    return f;
  }

  template< typename Key, typename T, typename Compare >
  template < typename F >
  F Tree< Key, T, Compare >::traverse_rnl(F f) const
  {
    if (empty())
    {
      throw std::invalid_argument("Tree is empty");
    }
    for (auto it = crbegin(); it != cend(); --it)
    {
      f(*it);
    }
    return f;
  }

  template< typename Key, typename T, typename Compare >
  template < typename F >
  F Tree< Key, T, Compare >::traverse_breadth(F f)
  {
    if (empty())
    {
      throw std::invalid_argument("Tree is empty");
    }
    Stack< node_t * > stack;
    stack.push(root_);
    while (!stack.empty())
    {
      node_t * current = stack.top();
      stack.pop();
      while(current->hasLeft())
      {
        if (current->hasRight())
        {
          stack.push(current->right_);
        }
        f(current->data_);
        current = current->left_;
      }
      f(current->data_);
      if (current->hasRight())
      {
        stack.push(current->right_);
      }
    }
    return f;
  }

  template< typename Key, typename T, typename Compare >
  template < typename F >
  F Tree< Key, T, Compare >::traverse_breadth(F f) const
  {
    if (empty())
    {
      throw std::invalid_argument("Tree is empty");
    }
    Stack< const node_t * > stack;
    stack.push(root_);
    while (!stack.empty())
    {
      const node_t * current = stack.top();
      stack.pop();
      while(current->hasLeft())
      {
        if (current->hasRight())
        {
          stack.push(current->right_);
        }
        f(current->data_);
        current = current->left_;
      }
      f(current->data_);
      if (current->hasRight())
      {
        stack.push(current->right_);
      }
    }
    return f;
  }
}

#endif

