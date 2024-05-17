#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <functional>
#include <initializer_list>
#include "tree_node.hpp"
#include "tree_const_iterator.hpp"
#include "tree_iterator.hpp"

#include <iostream>

namespace erohin
{
  template< class Key, class T, class Compare = std::less< Key > >
  class RedBlackTree
  {
  public:
    using iterator = TreeIterator< Key, T >;
    using const_iterator = TreeConstIterator< Key, T >;
    using reverse_iterator = std::reverse_iterator< TreeIterator< Key, T > >;
    using const_reverse_iterator = std::reverse_iterator< TreeConstIterator< Key, T > >;
    using value_type = std::pair< Key, T >;
    RedBlackTree();
    RedBlackTree(const RedBlackTree< Key, T, Compare > & rhs);
    RedBlackTree(RedBlackTree< Key, T, Compare > && rhs) noexcept;
    RedBlackTree(std::initializer_list< value_type > init_list);
    template< class InputIt>
    RedBlackTree(InputIt first, InputIt last);
    ~RedBlackTree();
    RedBlackTree< Key, T, Compare > & operator=(const RedBlackTree< Key, T, Compare > & rhs);
    RedBlackTree< Key, T, Compare > & operator=(RedBlackTree< Key, T, Compare > && rhs) noexcept;
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
    void clear();
    bool empty() const noexcept;
    std::pair< iterator, bool > insert(const value_type & value);
    std::pair< iterator, bool > insert(value_type && value);
    iterator insert(iterator pos, const value_type & value);
    iterator insert(iterator pos, value_type && value);
    template< class InputIt>
    void insert(InputIt first, InputIt last);
    void insert(std::initializer_list< value_type > init_list);
    template< class... Args >
    std::pair< iterator, bool > emplace(Args &&... args);
    template< class... Args >
    iterator emplace_hint(const_iterator pos, Args &&... args);
    iterator erase(const Key & key);
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(iterator first, iterator last);
    iterator erase(const_iterator first, const_iterator last);
    void swap(RedBlackTree & rhs) noexcept;
    size_t size() const noexcept;
    size_t count(const Key & key) const;
    iterator find(const Key & key);
    const_iterator find(const Key & key) const;
    T & at(const Key & key);
    const T & at(const Key & key) const;
    iterator lower_bound(const Key & key);
    const_iterator lower_bound(const Key & key) const;
    iterator upper_bound(const Key & key);
    const_iterator upper_bound(const Key & key) const;
    std::pair< iterator, iterator > equal_range(const Key & key);
    std::pair< const_iterator, const_iterator > equal_range(const Key & key) const;
  private:
    detail::Node< Key, T > * root_;
    Compare cmp_;
    size_t size_;
    void clear_subtree(detail::Node< Key, T > * subtree);
    detail::Node< Key, T > * find_to_change_erased(detail::Node< Key, T > * subtree);
    detail::Node< Key, T > * find_grandparent(detail::Node< Key, T > * subtree);
    detail::Node< Key, T > * find_uncle(detail::Node< Key, T > * subtree);
    detail::Node< Key, T > * find_brother(detail::Node< Key, T > * subtree);
    bool is_leaf(detail::Node< Key, T > * node);
    void rotate_left(detail::Node< Key, T > * subtree);
    void rotate_right(detail::Node< Key, T > * subtree);
    void insert_balance_case1(detail::Node< Key, T > * subtree);
    void insert_balance_case2(detail::Node< Key, T > * subtree);
    void insert_balance_case3(detail::Node< Key, T > * subtree);
    void insert_balance_case4(detail::Node< Key, T > * subtree);
    void insert_balance_case5(detail::Node< Key, T > * subtree);
    void erase_balance_case1(detail::Node< Key, T > * subtree);
    void erase_balance_case2(detail::Node< Key, T > * subtree);
    void erase_balance_case3(detail::Node< Key, T > * subtree);
    void erase_balance_case4(detail::Node< Key, T > * subtree);
    void erase_balance_case5(detail::Node< Key, T > * subtree);
    void erase_balance_case6(detail::Node< Key, T > * subtree);
  };

  template< class Key, class T, class Compare >
  RedBlackTree< Key, T, Compare >::RedBlackTree():
    root_(nullptr),
    size_(0)
  {}

  template< class Key, class T, class Compare >
  RedBlackTree< Key, T, Compare >::RedBlackTree(const RedBlackTree< Key, T, Compare > & rhs):
    RedBlackTree(rhs.cbegin(), rhs.cend())
  {}

  template< class Key, class T, class Compare >
  RedBlackTree< Key, T, Compare >::RedBlackTree(RedBlackTree< Key, T, Compare > && rhs) noexcept:
    root_(rhs.root_),
    size_(rhs.size_)
  {
    rhs.root_ = nullptr;
    rhs.size_ = 0;
  }

  template< class Key, class T, class Compare >
  RedBlackTree< Key, T, Compare >::RedBlackTree(std::initializer_list< value_type > init_list):
    RedBlackTree(init_list.begin(), init_list.end())
  {}

  template< class Key, class T, class Compare >
  template< class InputIt >
  RedBlackTree< Key, T, Compare >::RedBlackTree(InputIt first, InputIt last):
    root_(nullptr)
  {
    while (first != last)
    {
      try
      {
        insert(*(first++));
      }
      catch (...)
      {
        clear();
      }
    }
  }

  template< class Key, class T, class Compare >
  RedBlackTree< Key, T, Compare >::~RedBlackTree()
  {
    clear();
  }

  template< class Key, class T, class Compare >
  RedBlackTree< Key, T, Compare > & RedBlackTree< Key, T, Compare >::operator=(const RedBlackTree< Key, T, Compare > & rhs)
  {
    return operator=(RedBlackTree< Key, T, Compare >(rhs));
  }

  template< class Key, class T, class Compare >
  RedBlackTree< Key, T, Compare > & RedBlackTree< Key, T, Compare >::operator=(RedBlackTree< Key, T, Compare > && rhs) noexcept
  {
    if (std::addressof(rhs) != this)
    {
      RedBlackTree< Key, T, Compare > temp(std::move(rhs));
      swap(temp);
    }
    return *this;
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::begin()
  {
    detail::Node< Key, T > * result = root_;
    while (result && result->left_)
    {
      result = result->left_;
    }
    return iterator(result);
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::end()
  {
    return iterator(nullptr);
  }

  template< class Key, class T, class Compare >
  TreeConstIterator< Key, T > RedBlackTree< Key, T, Compare >::cbegin() const
  {
    const detail::Node< Key, T > * result = root_;
    while (result && result->left_)
    {
      result = result->left_;
    }
    return const_iterator(result);
  }

  template< class Key, class T, class Compare >
  TreeConstIterator< Key, T > RedBlackTree< Key, T, Compare >::cend() const
  {
    return const_iterator(nullptr);
  }

  template< class Key, class T, class Compare >
  typename RedBlackTree< Key, T, Compare >::reverse_iterator RedBlackTree< Key, T, Compare >::rbegin()
  {
    return reverse_iterator(crbegin().node_);
  }

  template< class Key, class T, class Compare >
  typename RedBlackTree< Key, T, Compare >::reverse_iterator RedBlackTree< Key, T, Compare >::rend()
  {
    return reverse_iterator(nullptr);
  }

  template< class Key, class T, class Compare >
  typename RedBlackTree< Key, T, Compare >::const_reverse_iterator RedBlackTree< Key, T, Compare >::crbegin() const
  {
    detail::Node< Key, T > * result = root_;
    while (result->right_)
    {
      result = result->right_;
    }
    return const_reverse_iterator(result);
  }

  template< class Key, class T, class Compare >
  typename RedBlackTree< Key, T, Compare >::const_reverse_iterator RedBlackTree< Key, T, Compare >::crend() const
  {
    return const_reverse_iterator(nullptr);
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::clear()
  {
    clear_subtree(root_);
    root_ = nullptr;
    size_ = 0;
  }

  template< class Key, class T, class Compare >
  std::pair< TreeIterator< Key, T >, bool > RedBlackTree< Key, T, Compare >::insert(const value_type & value)
  {
    return insert(value_type(value));
  }

  template< class Key, class T, class Compare >
  std::pair< TreeIterator< Key, T >, bool > RedBlackTree< Key, T, Compare >::insert(value_type && value)
  {
    detail::Node< Key, T > * node = root_;
    if (empty())
    {
      root_ = new detail::Node< Key, T >(nullptr, nullptr, nullptr, std::move(value));
      node = root_;
    }
    else
    {
      detail::Node< Key, T > * prev = node;
      while (node)
      {
        prev = node;
        if (!cmp_(value.first, node->data_.first) && !cmp_(node->data_.first, value.first))
        {
          return std::make_pair(iterator(node), false);
        }
        else if (cmp_(value.first, node->data_.first))
        {
          node = node->left_;
        }
        else
        {
          node = node->right_;
        }
      }
      node = new detail::Node< Key, T >(prev, nullptr, nullptr, std::move(value));
      try
      {
        if (cmp_(node->data_.first, prev->data_.first))
        {
          prev->left_ = node;
        }
        else
        {
          prev->right_ = node;
        }
      }
      catch (...)
      {
        delete node;
        throw;
      }
    }
    insert_balance_case1(node);
    ++size_;
    return std::make_pair(iterator(node), true);
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::insert(iterator pos, const value_type & value)
  {
    return insert(pos, value_type(value));
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::insert(iterator pos, value_type && value)
  {
    detail::Node< Key, T > * node = pos.node_;
    detail::Node< Key, T > * prev = node;
    while (node)
    {
      prev = node;
      if (cmp_(value.first, node->data_.first))
      {
        node = node->left_;
      }
      else
      {
        node = node->right_;
      }
    }
    node = new detail::Node< Key, T >(prev, nullptr, nullptr, std::move(value));
    try
    {
      if (cmp_(node->data_.first, prev->data_.first))
      {
        prev->left_ = node;
      }
      else
      {
        prev->right_ = node;
      }
    }
    catch (...)
    {
      delete node;
      throw;
    }
    insert_balance_case1(node);
    ++size_;
    return iterator(node);
  }

  template< class Key, class T, class Compare >
  template< class InputIt >
  void RedBlackTree< Key, T, Compare >::insert(InputIt first, InputIt last)
  {
    while (first != last)
    {
      insert(*(first++));
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::insert(std::initializer_list< value_type > init_list)
  {
    insert(init_list.begin(), init_list.end());
  }

  template< class Key, class T, class Compare >
  template< class... Args >
  std::pair< TreeIterator< Key, T >, bool > RedBlackTree< Key, T, Compare >::emplace(Args &&... args)
  {
    detail::Node< Key, T > * emplaced = new detail::Node< Key, T >(nullptr, nullptr, nullptr, std::forward< Args... >(args...));
    try
    {
      if (empty())
      {
        root_ = emplaced;
      }
      else
      {
        detail::Node< Key, T > * node = root_;
        detail::Node< Key, T > * prev = node;
        while (node)
        {
          prev = node;
          if (!cmp_(emplaced->first, node->data_.first) && !cmp_(node->data_.first, emplaced->first))
          {
            delete emplaced;
            return std::make_pair(iterator(node), false);
          }
          else if (cmp_(emplaced->first, node->data_.first))
          {
            node = node->left_;
          }
          else
          {
            node = node->right_;
          }
        }
        emplaced->parent_ = prev;
        if (cmp_(emplaced->data_.first, prev->data_.first))
        {
          prev->left_ = emplaced;
        }
        else
        {
          prev->right_ = emplaced;
        }
      }
    }
    catch (...)
    {
      delete emplaced;
      throw;
    }
    insert_balance_case1(emplaced);
    ++size_;
    return std::make_pair(iterator(emplaced), true);
  }

  template< class Key, class T, class Compare >
  template< class... Args >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::emplace_hint(const_iterator pos, Args &&... args)
  {
    detail::Node< Key, T > * emplaced = new detail::Node< Key, T >(nullptr, nullptr, nullptr, std::forward< Args... >(args...));
    try
    {
      detail::Node< Key, T > * node = pos.node_;
      detail::Node< Key, T > * prev = node;
      while (node)
      {
        prev = node;
        if (!cmp_(emplaced->first, node->data_.first) && !cmp_(node->data_.first, emplaced->first))
        {
          delete emplaced;
          return std::make_pair(iterator(node), false);
        }
        else if (cmp_(emplaced->first, node->data_.first))
        {
          node = node->left_;
        }
        else
        {
          node = node->right_;
        }
      }
      emplaced->parent_ = prev;
      if (cmp_(emplaced->data_.first, prev->data_.first))
      {
        prev->left_ = emplaced;
      }
      else
      {
        prev->right_ = emplaced;
      }
    }
    catch (...)
    {
      delete emplaced;
      throw;
    }
    insert_balance_case1(emplaced);
    ++size_;
    return std::make_pair(iterator(emplaced), true);
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::erase(const Key & key)
  {
    detail::Node< Key, T > * node = root_;
    detail::Node< Key, T > * to_delete = nullptr;
    while (!to_delete && node)
    {
      if (node->data_.first == key)
      {
        to_delete = node;
      }
      else if (cmp_(key, node->data_.first))
      {
        node = node->left_;
      }
      else
      {
        node = node->right_;
      }
    }
    if (!to_delete)
    {
      return end();
    }
    return erase(iterator(to_delete));
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::erase(iterator pos)
  {
    detail::Node< Key, T > * to_delete = pos.node_;
    detail::Node< Key, T > * found = find_to_change_erased(to_delete);
    if (to_delete == root_ && !found)
    {
      clear();
      return end();
    }
    else if (!found)
    {
      found = to_delete;
    }
    if (found->parent_->left_ == found)
    {
      found->parent_->left_ = found->left_;
    }
    else if (found->parent_->right_ == found)
    {
      found->parent_->right_ = found->right_;
    }
    if (found != to_delete)
    {
      std::swap(found->data_, to_delete->data_);
    }
    erase_balance_case1(found);
    auto iter = ++pos;
    delete found;
    --size_;
    return iter;
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::erase(const_iterator pos)
  {
    return TreeConstIterator< Key, T >(erase(iterator(pos.node_)));
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::erase(iterator first, iterator last)
  {
    iterator result;
    while (first != last)
    {
      result = erase(first++);
    }
    return result;
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::erase(const_iterator first, const_iterator last)
  {
    return erase(iterator(first.node_), iterator(last.node_));
  }

  template< class Key, class T, class Compare >
  bool RedBlackTree< Key, T, Compare >::empty() const noexcept
  {
    return (!root_);
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::swap(RedBlackTree< Key, T, Compare > & rhs) noexcept
  {
    std::swap(root_, rhs.root_);
  }

  template< class Key, class T, class Compare >
  size_t RedBlackTree< Key, T, Compare >::size() const noexcept
  {
    return size_;
  }

  template< class Key, class T, class Compare >
  size_t RedBlackTree< Key, T, Compare >::count(const Key & key) const
  {
    auto citer = cbegin();
    size_t size = 0;
    while (citer != cend())
    {
      if (!cmp_(key, citer->first) && !cmp_(citer->first, key))
      {
        ++size;
      }
    }
    return size;
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::find(const Key & key)
  {
    detail::Node< Key, T > * node = root_;
    while (node)
    {
      if (cmp_(key, node->data_.first))
      {
        node = node->left_;
      }
      else if (cmp_(node->data_.first, key))
      {
        node = node->right_;
      }
      else
      {
        return iterator(node);
      }
    }
    return end();
  }

  template< class Key, class T, class Compare >
  TreeConstIterator< Key, T > RedBlackTree< Key, T, Compare >::find(const Key & key) const
  {
    const detail::Node< Key, T > * node = root_;
    while (node)
    {
      if (cmp_(key, node->data_.first))
      {
        node = node->left_;
      }
      else if (cmp_(node->data_.first, key))
      {
        node = node->right_;
      }
      else
      {
        return const_iterator(node);
      }
    }
    return cend();
  }

  template< class Key, class T, class Compare >
  T & RedBlackTree< Key, T, Compare >::at(const Key & key)
  {
    TreeIterator< Key, T > iter = find(key);
    if (iter == end())
    {
      throw std::out_of_range("Out of range in element access");
    }
    return iter->second;
  }

  template< class Key, class T, class Compare >
  const T & RedBlackTree< Key, T, Compare >::at(const Key & key) const
  {
    TreeConstIterator< Key, T > iter = find(key);
    if (iter == cend())
    {
      throw std::out_of_range("Out of range in element access");
    }
    return iter->second;
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::lower_bound(const Key & key)
  {
    detail::Node< Key, T > * node = root_;
    detail::Node< Key, T > * prev = root_;
    while (node)
    {
      prev = node;
      if (cmp_(key, node->data_.first))
      {
        node = node->left_;
      }
      else
      {
        node = node->right_;
      }
      if (!cmp_(prev->data_.first, key))
      {
        return iterator(node);
      }
    }
    return end();
  }

  template< class Key, class T, class Compare >
  TreeConstIterator< Key, T > RedBlackTree< Key, T, Compare >::lower_bound(const Key & key) const
  {
    return const_iterator(lower_bound(key).node_);
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::upper_bound(const Key & key)
  {
    detail::Node< Key, T > * node = root_;
    while (node)
    {
      if (cmp_(node->data_.first, key))
      {
        return iterator(node);
      }
      else if (cmp_(key, node->data_.first))
      {
        node = node->left_;
      }
      else
      {
        node = node->right_;
      }
    }
    return end();
  }

  template< class Key, class T, class Compare >
  TreeConstIterator< Key, T > RedBlackTree< Key, T, Compare >::upper_bound(const Key & key) const
  {
    return const_iterator(upper_bound(key).node_);
  }

  template< class Key, class T, class Compare >
  std::pair< TreeIterator< Key, T >, TreeIterator< Key, T > > RedBlackTree< Key, T, Compare >::equal_range(const Key & key)
  {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }

  template< class Key, class T, class Compare >
  std::pair< TreeConstIterator< Key, T >, TreeConstIterator< Key, T > > RedBlackTree< Key, T, Compare >::equal_range(const Key & key) const
  {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::clear_subtree(detail::Node< Key, T > * subtree)
  {
    if (!subtree)
    {
      return;
    }
    clear_subtree(subtree->left_);
    clear_subtree(subtree->right_);
    delete subtree;
  }

  template< class Key, class T, class Compare >
  detail::Node< Key, T > * RedBlackTree< Key, T, Compare >::find_to_change_erased(detail::Node< Key, T > * subtree)
  {
    if (subtree->left_)
    {
      subtree = subtree->left_;
      while (subtree->right_)
      {
        subtree = subtree->right_;
      }
    }
    else if (subtree->right_)
    {
      subtree = subtree->right_;
      while (subtree->left_)
      {
        subtree = subtree->left_;
      }
    }
    else
    {
      subtree = nullptr;
    }
    return subtree;
  }

  template< class Key, class T, class Compare >
  bool RedBlackTree< Key, T, Compare >::is_leaf(detail::Node< Key, T > * node)
  {
    return !(node->left_ && node->right_);
  }

  template< class Key, class T, class Compare >
  detail::Node< Key, T > * RedBlackTree< Key, T, Compare >::find_grandparent(detail::Node< Key, T > * subtree)
  {
    if (subtree && subtree->parent_)
    {
      return subtree->parent_->parent_;
    }
    else
    {
      return nullptr;
    }
  }

  template< class Key, class T, class Compare >
  detail::Node< Key, T > * RedBlackTree< Key, T, Compare >::find_uncle(detail::Node< Key, T > * subtree)
  {
    detail::Node< Key, T > * node = find_grandparent(subtree);
    if (!node)
    {
      return nullptr;
    }
    if (node->parent_ == node->left_)
    {
      return node->right_;
    }
    else
    {
      return node->left_;
    }
  }

  template< class Key, class T, class Compare >
  detail::Node< Key, T > * RedBlackTree< Key, T, Compare >::find_brother(detail::Node< Key, T > * subtree)
  {
    if (subtree == subtree->parent_->left_)
    {
      return subtree->parent_->right_;
    }
    else
    {
      return subtree->parent_->left_;
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::rotate_left(detail::Node< Key, T > * subtree)
  {
    detail::Node< Key, T > * node = subtree->right_;
    node->parent_ = subtree->parent_;
    if (!node->parent_)
    {
      root_ = node;
    }
    if (subtree->parent_)
    {
      if (subtree->parent_->left_ == subtree)
      {
        subtree->parent_->left_ = node;
      }
      else
      {
        subtree->parent_->right_ = node;
      }
    }
    subtree->right_ = node->left_;
    if (node->left_)
    {
      node->left_->parent_ = subtree;
    }
    subtree->parent_ = node;
    node->left_ = subtree;
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::rotate_right(detail::Node< Key, T > * subtree)
  {
    detail::Node< Key, T > * node = subtree->left_;
    node->parent_ = subtree->parent_;
    if (!node->parent_)
    {
      root_ = node;
    }
    if (subtree->parent_)
    {
      if (subtree->parent_->left_ == subtree)
      {
        subtree->parent_->left_ = node;
      }
      else
      {
        subtree->parent_->right_ = node;
      }
    }
    subtree->left_ = node->right_;
    if (node->right_)
    {
      node->right_->parent_ = subtree;
    }
    subtree->parent_ = node;
    node->right_ = subtree;
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::insert_balance_case1(detail::Node< Key, T > * subtree)
  {
    if (!subtree->parent_)
    {
      subtree->color_ = detail::color_t::BLACK;
    }
    else
    {
      insert_balance_case2(subtree);
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::insert_balance_case2(detail::Node< Key, T > * subtree)
  {
    if (subtree->parent_->color_ == detail::color_t::RED)
    {
      insert_balance_case3(subtree);
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::insert_balance_case3(detail::Node< Key, T > * subtree)
  {
    detail::Node< Key, T > * uncle = find_uncle(subtree);
    if (uncle && uncle->color_ == detail::color_t::RED)
    {
      subtree->parent_->color_ = detail::color_t::BLACK;
      uncle->color_ = detail::color_t::BLACK;
      detail::Node< Key, T > * grand = find_grandparent(subtree);
      grand->color_ = detail::color_t::RED;
      insert_balance_case1(grand);
    }
    else
    {
      insert_balance_case4(subtree);
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::insert_balance_case4(detail::Node< Key, T > * subtree)
  {
    detail::Node< Key, T > * grand = find_grandparent(subtree);
    if (subtree == subtree->parent_->right_ && subtree->parent_ == grand->left_)
    {
      rotate_left(subtree->parent_);
      subtree = subtree->left_;
    }
    else if (subtree == subtree->parent_->left_ && subtree->parent_ == grand->right_)
    {
      rotate_right(subtree->parent_);
      subtree = subtree->right_;
    }
    insert_balance_case5(subtree);
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::insert_balance_case5(detail::Node< Key, T > * subtree)
  {
    detail::Node< Key, T > * grand = find_grandparent(subtree);
    subtree->parent_->color_ = detail::color_t::BLACK;
    grand->color_ = detail::color_t::RED;
    if (subtree == subtree->parent_->left_ && subtree->parent_ == grand->left_)
    {
      rotate_right(grand);
    }
    else
    {
      rotate_left(grand);
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::erase_balance_case1(detail::Node< Key, T > * subtree)
  {
    if (subtree->color_ == detail::color_t::BLACK && !is_leaf(subtree))
    {
      detail::Node< Key, T > * child = (subtree->right_) ? subtree->left_ : subtree->right_;
      if (child->color_ == detail::color_t::RED)
      {
        child->color_ = detail::color_t::BLACK;
      }
      else if (subtree->parent_)
      {
        erase_balance_case2(child);
      }
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::erase_balance_case2(detail::Node< Key, T > * subtree)
  {
    detail::Node< Key, T > * brother = find_brother(subtree);
    if (brother->color_ == detail::color_t::RED)
    {
      subtree->parent_->color_ = detail::color_t::RED;
      brother->color_ = detail::color_t::BLACK;
      if (subtree == subtree->parent_->left_)
      {
        rotate_left(subtree->parent_);
      }
      else
      {
        rotate_right(subtree->parent_);
      }
    }
    erase_balance_case3(subtree);
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::erase_balance_case3(detail::Node< Key, T > * subtree)
  {
    detail::Node< Key, T > * brother = find_brother(subtree);
    bool is_left_black = (brother->left_->color_ == detail::color_t::BLACK);
    bool is_right_black = (brother->right_->color_ == detail::color_t::BLACK);
    bool is_black = (brother->color_ == detail::color_t::BLACK);
    if (subtree->parent_->color_ == detail::color_t::BLACK && is_black && is_left_black && is_right_black)
    {
      brother->color_ = detail::color_t::RED;
      erase_balance_case1(subtree->parent_);
    }
    else
    {
      erase_balance_case4(subtree);
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::erase_balance_case4(detail::Node< Key, T > * subtree)
  {
    detail::Node< Key, T > * brother = find_brother(subtree);
    bool is_left_black = (brother->left_->color_ == detail::color_t::BLACK);
    bool is_right_black = (brother->right_->color_ == detail::color_t::BLACK);
    bool is_black = (brother->color_ == detail::color_t::BLACK);
    if (subtree->parent_->color_ == detail::color_t::RED && is_black && is_left_black && is_right_black)
    {
      brother->color_ = detail::color_t::RED;
      subtree->parent_->color_ = detail::color_t::BLACK;
    }
    else
    {
      erase_balance_case5(subtree);
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::erase_balance_case5(detail::Node< Key, T > * subtree)
  {
    detail::Node< Key, T > * brother = find_brother(subtree);
    bool is_left_black = (brother->left_->color_ == detail::color_t::BLACK);
    bool is_right_black = (brother->right_->color_ == detail::color_t::BLACK);
    if (brother->color_ == detail::color_t::BLACK)
    {
      if (subtree == subtree->parent_->left_ && is_right_black && !is_left_black)
      {
        brother->color_ = detail::color_t::RED;
        brother->left_->color_ = detail::color_t::BLACK;
        rotate_right(brother);
      }
      else if (subtree == subtree->parent_->right_ && is_left_black && !is_right_black)
      {
        brother->color_ = detail::color_t::RED;
        brother->right_->color_ = detail::color_t::BLACK;
        rotate_left(brother);
      }
    }
    erase_balance_case6(subtree);
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::erase_balance_case6(detail::Node< Key, T > * subtree)
  {
    detail::Node< Key, T > * brother = find_brother(subtree);
    brother->color_ = subtree->parent_->color_;
    subtree->parent_->color_ = detail::color_t::BLACK;
    if (subtree == subtree->parent_->left_)
    {
      brother->right_->color_ = detail::color_t::BLACK;
      rotate_left(subtree->parent_);
    }
    else
    {
      brother->left_->color_ = detail::color_t::BLACK;
      rotate_right(subtree->parent_);
    }
  }
}

#endif
