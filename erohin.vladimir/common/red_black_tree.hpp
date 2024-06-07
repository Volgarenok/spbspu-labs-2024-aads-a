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
    using lnr_iterator = LnrIterator< Key, T >;
    using const_lnr_iterator = ConstLnrIterator< Key, T >;
    using rnl_iterator = RnlIterator< Key, T >;
    using const_rnl_iterator = ConstRnlIterator< Key, T >;
    using breadth_iterator = BreadthIterator< Key, T >;
    using const_breadth_iterator = ConstBreadthIterator< Key, T >;
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
    T & operator[](const Key & key);
    const T & operator[](const Key & key) const;
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
    lnr_iterator lnr_begin();
    lnr_iterator lnr_end();
    const_lnr_iterator lnr_cbegin() const;
    const_lnr_iterator lnr_cend() const;
    rnl_iterator rnl_begin();
    rnl_iterator rnl_end();
    const_rnl_iterator rnl_cbegin() const;
    const_rnl_iterator rnl_cend() const;
    breadth_iterator breadth_begin();
    breadth_iterator breadth_end();
    const_breadth_iterator breadth_cbegin() const;
    const_breadth_iterator breadth_cend() const;
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
    template< class F >
    F traverse_lnr(F f) const;
    template< class F >
    F traverse_rnl(F f) const;
    template< class F >
    F traverse_breadth(F f) const;
  private:
    detail::TreeNode< Key, T > * root_;
    size_t size_;
    Compare cmp_;
    char fake_[sizeof(detail::TreeNode< Key, T >)];
    detail::TreeNode< Key, T > * make_fake_node() const;
    void clear_subtree(detail::TreeNode< Key, T > * subtree);
    detail::TreeNode< Key, T > * find_to_change_erased(detail::TreeNode< Key, T > * subtree);
    detail::TreeNode< Key, T > * find_grandparent(detail::TreeNode< Key, T > * subtree);
    detail::TreeNode< Key, T > * find_uncle(detail::TreeNode< Key, T > * subtree);
    detail::TreeNode< Key, T > * find_brother(detail::TreeNode< Key, T > * subtree);
    template< detail::color_t C >
    bool is_color(detail::TreeNode< Key, T > * node);
    template< detail::color_t C >
    void colorize(detail::TreeNode< Key, T > * node);
    bool is_leaf(detail::TreeNode< Key, T > * node);
    void rotate_left(detail::TreeNode< Key, T > * subtree);
    void rotate_right(detail::TreeNode< Key, T > * subtree);
    void insert_balance_case1(detail::TreeNode< Key, T > * subtree);
    void insert_balance_case2(detail::TreeNode< Key, T > * subtree);
    void insert_balance_case3(detail::TreeNode< Key, T > * subtree);
    void insert_balance_case4(detail::TreeNode< Key, T > * subtree);
    void insert_balance_case5(detail::TreeNode< Key, T > * subtree);
    void erase_balance_case1(detail::TreeNode< Key, T > * subtree);
    void erase_balance_case2(detail::TreeNode< Key, T > * subtree);
    void erase_balance_case3(detail::TreeNode< Key, T > * subtree);
    void erase_balance_case4(detail::TreeNode< Key, T > * subtree);
    void erase_balance_case5(detail::TreeNode< Key, T > * subtree);
    void erase_balance_case6(detail::TreeNode< Key, T > * subtree);
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
  T & RedBlackTree< Key, T, Compare >::operator[](const Key & key)
  {
    auto iter = insert(std::make_pair(key, T())).first;
    return iter->second;
  }

  template< class Key, class T, class Compare >
  const T & RedBlackTree< Key, T, Compare >::operator[](const Key & key) const
  {
    TreeConstIterator< Key, T > iter = find(key);
    return iter->second;
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T > RedBlackTree< Key, T, Compare >::begin()
  {
    detail::TreeNode< Key, T > * result = root_;
    while (result && result->left)
    {
      result = result->left;
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
    const detail::TreeNode< Key, T > * result = root_;
    while (result && result->left)
    {
      result = result->left;
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
    return reverse_iterator(iterator(crbegin().node_));
  }

  template< class Key, class T, class Compare >
  typename RedBlackTree< Key, T, Compare >::reverse_iterator RedBlackTree< Key, T, Compare >::rend()
  {
    return reverse_iterator(iterator(crend().node_));
  }

  template< class Key, class T, class Compare >
  typename RedBlackTree< Key, T, Compare >::const_reverse_iterator RedBlackTree< Key, T, Compare >::crbegin() const
  {
    detail::TreeNode< Key, T > * prev = root_;
    while (prev->right)
    {
      prev = prev->right;
    }
    detail::TreeNode< Key, T > * result = make_fake_node();
    result->left = prev;
    result->right = nullptr;
    return const_reverse_iterator(const_iterator(result));
  }

  template< class Key, class T, class Compare >
  typename RedBlackTree< Key, T, Compare >::const_reverse_iterator RedBlackTree< Key, T, Compare >::crend() const
  {
    return const_reverse_iterator(const_iterator(cbegin().node_));
  }

  template< class Key, class T, class Compare >
  LnrIterator< Key, T > RedBlackTree< Key, T, Compare >::lnr_begin()
  {
    auto iter = lnr_iterator(root_);
    while (iter.node_->left)
    {
      iter.stack_.push(iter.node_);
      iter.node_ = iter.node_->left;
    }
    return iter;
  }

  template< class Key, class T, class Compare >
  LnrIterator< Key, T > RedBlackTree< Key, T, Compare >::lnr_end()
  {
    return lnr_iterator(nullptr);
  }

  template< class Key, class T, class Compare >
  ConstLnrIterator< Key, T > RedBlackTree< Key, T, Compare >::lnr_cbegin() const
  {
    auto iter = const_lnr_iterator(root_);
    while (iter.node_->left)
    {
      iter.stack_.push(iter.node_);
      iter.node_ = iter.node_->left;
    }
    return iter;
  }

  template< class Key, class T, class Compare >
  ConstLnrIterator< Key, T > RedBlackTree< Key, T, Compare >::lnr_cend() const
  {
    return const_lnr_iterator(nullptr);
  }

  template< class Key, class T, class Compare >
  typename RedBlackTree< Key, T, Compare >::rnl_iterator RedBlackTree< Key, T, Compare >::rnl_begin()
  {
    return rnl_iterator(rnl_cbegin().iter_);
  }

  template< class Key, class T, class Compare >
  typename RedBlackTree< Key, T, Compare >::rnl_iterator RedBlackTree< Key, T, Compare >::rnl_end()
  {
    return rnl_iterator(rnl_cend().iter_);
  }

  template< class Key, class T, class Compare >
  typename RedBlackTree< Key, T, Compare >::const_rnl_iterator RedBlackTree< Key, T, Compare >::rnl_cbegin() const
  {
    auto iter = const_lnr_iterator(root_);
    while (iter.node_->right)
    {
      iter.stack_.push(iter.node_);
      iter.node_ = iter.node_->right;
    }
    return const_rnl_iterator(iter);
  }

  template< class Key, class T, class Compare >
  typename RedBlackTree< Key, T, Compare >::const_rnl_iterator RedBlackTree< Key, T, Compare >::rnl_cend() const
  {
    return const_rnl_iterator(nullptr);
  }

  template< class Key, class T, class Compare >
  BreadthIterator< Key, T > RedBlackTree< Key, T, Compare >::breadth_begin()
  {
    return breadth_iterator(root_);
  }

  template< class Key, class T, class Compare >
  BreadthIterator< Key, T > RedBlackTree< Key, T, Compare >::breadth_end()
  {
    return breadth_iterator(nullptr);
  }

  template< class Key, class T, class Compare >
  ConstBreadthIterator< Key, T > RedBlackTree< Key, T, Compare >::breadth_cbegin() const
  {
    return const_breadth_iterator(root_);
  }

  template< class Key, class T, class Compare >
  ConstBreadthIterator< Key, T > RedBlackTree< Key, T, Compare >::breadth_cend() const
  {
    return const_breadth_iterator(nullptr);
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
    detail::TreeNode< Key, T > * node = root_;
    if (empty())
    {
      root_ = new detail::TreeNode< Key, T >(nullptr, nullptr, nullptr, std::move(value));
      node = root_;
    }
    else
    {
      detail::TreeNode< Key, T > * prev = node;
      while (node)
      {
        prev = node;
        if (!cmp_(value.first, node->data.first) && !cmp_(node->data.first, value.first))
        {
          return std::make_pair(iterator(node), false);
        }
        else if (cmp_(value.first, node->data.first))
        {
          node = node->left;
        }
        else
        {
          node = node->right;
        }
      }
      node = new detail::TreeNode< Key, T >(prev, nullptr, nullptr, std::move(value));
      try
      {
        if (cmp_(node->data.first, prev->data.first))
        {
          prev->left = node;
        }
        else
        {
          prev->right = node;
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
    detail::TreeNode< Key, T > * node = pos.node_;
    detail::TreeNode< Key, T > * prev = node;
    while (node)
    {
      prev = node;
      if (cmp_(value.first, node->data.first))
      {
        node = node->left;
      }
      else
      {
        node = node->right;
      }
    }
    node = new detail::TreeNode< Key, T >(prev, nullptr, nullptr, std::move(value));
    try
    {
      if (cmp_(node->data.first, prev->data.first))
      {
        prev->left = node;
      }
      else
      {
        prev->right = node;
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
    detail::TreeNode< Key, T > * emplaced = new detail::TreeNode< Key, T >(nullptr, nullptr, nullptr, std::forward< Args... >(args...));
    try
    {
      if (empty())
      {
        root_ = emplaced;
      }
      else
      {
        detail::TreeNode< Key, T > * node = root_;
        detail::TreeNode< Key, T > * prev = node;
        while (node)
        {
          prev = node;
          if (!cmp_(emplaced->data.first, node->data.first) && !cmp_(node->data.first, emplaced->data.first))
          {
            delete emplaced;
            return std::make_pair(iterator(node), false);
          }
          else if (cmp_(emplaced->data.first, node->data.first))
          {
            node = node->left;
          }
          else
          {
            node = node->right;
          }
        }
        emplaced->parent = prev;
        if (cmp_(emplaced->data.first, prev->data.first))
        {
          prev->left = emplaced;
        }
        else
        {
          prev->right = emplaced;
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
    detail::TreeNode< Key, T > * emplaced = new detail::TreeNode< Key, T >(nullptr, nullptr, nullptr, std::forward< Args... >(args...));
    try
    {
      detail::TreeNode< Key, T > * node = pos.node_;
      detail::TreeNode< Key, T > * prev = node;
      while (node)
      {
        prev = node;
        if (!cmp_(emplaced->first, node->data.first) && !cmp_(node->data.first, emplaced->first))
        {
          delete emplaced;
          return std::make_pair(iterator(node), false);
        }
        else if (cmp_(emplaced->first, node->data.first))
        {
          node = node->left;
        }
        else
        {
          node = node->right;
        }
      }
      emplaced->parent = prev;
      if (cmp_(emplaced->data.first, prev->data.first))
      {
        prev->left = emplaced;
      }
      else
      {
        prev->right = emplaced;
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
    detail::TreeNode< Key, T > * node = root_;
    detail::TreeNode< Key, T > * to_delete = nullptr;
    while (!to_delete && node)
    {
      if (node->data.first == key)
      {
        to_delete = node;
      }
      else if (cmp_(key, node->data.first))
      {
        node = node->left;
      }
      else
      {
        node = node->right;
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
    detail::TreeNode< Key, T > * to_delete = pos.node_;
    detail::TreeNode< Key, T > * found = find_to_change_erased(to_delete);
    if (to_delete == root_ && !found)
    {
      clear();
      return end();
    }
    else if (!found)
    {
      found = to_delete;
    }
    if (found->parent->left == found)
    {
      found->parent->left = found->left;
    }
    else if (found->parent->right == found)
    {
      found->parent->right = found->right;
    }
    if (found != to_delete)
    {
      std::swap(found->data, to_delete->data);
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
    detail::TreeNode< Key, T > * node = root_;
    while (node)
    {
      if (cmp_(key, node->data.first))
      {
        node = node->left;
      }
      else if (cmp_(node->data.first, key))
      {
        node = node->right;
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
    const detail::TreeNode< Key, T > * node = root_;
    while (node)
    {
      if (cmp_(key, node->data.first))
      {
        node = node->left;
      }
      else if (cmp_(node->data.first, key))
      {
        node = node->right;
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
    detail::TreeNode< Key, T > * node = root_;
    detail::TreeNode< Key, T > * prev = root_;
    while (node)
    {
      prev = node;
      if (cmp_(key, node->data.first))
      {
        node = node->left;
      }
      else
      {
        node = node->right;
      }
      if (!cmp_(prev->data.first, key))
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
    detail::TreeNode< Key, T > * node = root_;
    while (node)
    {
      if (cmp_(node->data.first, key))
      {
        return iterator(node);
      }
      else if (cmp_(key, node->data.first))
      {
        node = node->left;
      }
      else
      {
        node = node->right;
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
  template< class F >
  F RedBlackTree< Key, T, Compare >::traverse_lnr(F f) const
  {
    auto citer = lnr_cbegin();
    while (citer != lnr_cend())
    {
      f = f(*(citer++));
    }
    return f;
  }

  template< class Key, class T, class Compare >
  template< class F >
  F RedBlackTree< Key, T, Compare >::traverse_rnl(F f) const
  {
    auto citer = rnl_cbegin();
    while (citer != rnl_cend())
    {
      f = f(*(citer++));
    }
    return f;
  }

  template< class Key, class T, class Compare >
  template< class F >
  F RedBlackTree< Key, T, Compare >::traverse_breadth(F f) const
  {
    auto citer = breadth_cbegin();
    while (citer != breadth_cend())
    {
      f = f(*(citer++));
    }
    return f;
  }

  template< class Key, class T, class Compare >
  detail::TreeNode< Key, T > * RedBlackTree< Key, T, Compare >::make_fake_node() const
  {
    return reinterpret_cast< detail::TreeNode< Key, T > * >(const_cast< char * >(fake_));
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::clear_subtree(detail::TreeNode< Key, T > * subtree)
  {
    if (!subtree)
    {
      return;
    }
    clear_subtree(subtree->left);
    clear_subtree(subtree->right);
    delete subtree;
  }

  template< class Key, class T, class Compare >
  detail::TreeNode< Key, T > * RedBlackTree< Key, T, Compare >::find_to_change_erased(detail::TreeNode< Key, T > * subtree)
  {
    if (subtree->left)
    {
      subtree = subtree->left;
      while (subtree->right)
      {
        subtree = subtree->right;
      }
    }
    else if (subtree->right)
    {
      subtree = subtree->right;
      while (subtree->left)
      {
        subtree = subtree->left;
      }
    }
    else
    {
      subtree = nullptr;
    }
    return subtree;
  }

  template< class Key, class T, class Compare >
  template< detail::color_t C >
  bool RedBlackTree< Key, T, Compare >::is_color(detail::TreeNode< Key, T > * node)
  {
    return (node->color == C);
  }

  template< class Key, class T, class Compare >
  template< detail::color_t C >
  void RedBlackTree< Key, T, Compare >::colorize(detail::TreeNode< Key, T > * node)
  {
    node->color = C;
  }

  template< class Key, class T, class Compare >
  bool RedBlackTree< Key, T, Compare >::is_leaf(detail::TreeNode< Key, T > * node)
  {
    return !(node->left && node->right);
  }

  template< class Key, class T, class Compare >
  detail::TreeNode< Key, T > * RedBlackTree< Key, T, Compare >::find_grandparent(detail::TreeNode< Key, T > * subtree)
  {
    if (subtree && subtree->parent)
    {
      return subtree->parent->parent;
    }
    else
    {
      return nullptr;
    }
  }

  template< class Key, class T, class Compare >
  detail::TreeNode< Key, T > * RedBlackTree< Key, T, Compare >::find_uncle(detail::TreeNode< Key, T > * subtree)
  {
    detail::TreeNode< Key, T > * node = find_grandparent(subtree);
    if (!node)
    {
      return nullptr;
    }
    if (node->parent == node->left)
    {
      return node->right;
    }
    else
    {
      return node->left;
    }
  }

  template< class Key, class T, class Compare >
  detail::TreeNode< Key, T > * RedBlackTree< Key, T, Compare >::find_brother(detail::TreeNode< Key, T > * subtree)
  {
    if (subtree == subtree->parent->left)
    {
      return subtree->parent->right;
    }
    else
    {
      return subtree->parent->left;
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::rotate_left(detail::TreeNode< Key, T > * subtree)
  {
    detail::TreeNode< Key, T > * node = subtree->right;
    node->parent = subtree->parent;
    if (!node->parent)
    {
      root_ = node;
    }
    if (subtree->parent)
    {
      if (subtree->parent->left == subtree)
      {
        subtree->parent->left = node;
      }
      else
      {
        subtree->parent->right = node;
      }
    }
    subtree->right = node->left;
    if (node->left)
    {
      node->left->parent = subtree;
    }
    subtree->parent = node;
    node->left = subtree;
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::rotate_right(detail::TreeNode< Key, T > * subtree)
  {
    detail::TreeNode< Key, T > * node = subtree->left;
    node->parent = subtree->parent;
    if (!node->parent)
    {
      root_ = node;
    }
    if (subtree->parent)
    {
      if (subtree->parent->left == subtree)
      {
        subtree->parent->left = node;
      }
      else
      {
        subtree->parent->right = node;
      }
    }
    subtree->left = node->right;
    if (node->right)
    {
      node->right->parent = subtree;
    }
    subtree->parent = node;
    node->right = subtree;
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::insert_balance_case1(detail::TreeNode< Key, T > * subtree)
  {
    using namespace detail;
    if (!subtree->parent)
    {
      colorize< BLACK >(subtree);
    }
    else
    {
      insert_balance_case2(subtree);
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::insert_balance_case2(detail::TreeNode< Key, T > * subtree)
  {
    using namespace detail;
    if (is_color< RED >(subtree->parent))
    {
      insert_balance_case3(subtree);
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::insert_balance_case3(detail::TreeNode< Key, T > * subtree)
  {
    using namespace detail;
    TreeNode< Key, T > * uncle = find_uncle(subtree);
    if (uncle && is_color< RED >(uncle))
    {
      colorize< BLACK >(subtree->parent);
      colorize< BLACK >(uncle);
      TreeNode< Key, T > * grand = find_grandparent(subtree);
      colorize< RED >(grand);
      insert_balance_case1(grand);
    }
    else
    {
      insert_balance_case4(subtree);
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::insert_balance_case4(detail::TreeNode< Key, T > * subtree)
  {
    using namespace detail;
    TreeNode< Key, T > * grand = find_grandparent(subtree);
    if (subtree == subtree->parent->right && subtree->parent == grand->left)
    {
      rotate_left(subtree->parent);
      subtree = subtree->left;
    }
    else if (subtree == subtree->parent->left && subtree->parent == grand->right)
    {
      rotate_right(subtree->parent);
      subtree = subtree->right;
    }
    insert_balance_case5(subtree);
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::insert_balance_case5(detail::TreeNode< Key, T > * subtree)
  {
    using namespace detail;
    TreeNode< Key, T > * grand = find_grandparent(subtree);
    colorize< BLACK >(subtree->parent);
    colorize< RED >(grand);
    if (subtree == subtree->parent->left && subtree->parent == grand->left)
    {
      rotate_right(grand);
    }
    else
    {
      rotate_left(grand);
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::erase_balance_case1(detail::TreeNode< Key, T > * subtree)
  {
    using namespace detail;
    if (is_color< BLACK >(subtree) && !is_leaf(subtree))
    {
      TreeNode< Key, T > * child = (subtree->right) ? subtree->left : subtree->right;
      if (is_color< RED >(child))
      {
        colorize< BLACK >(child);
      }
      else if (subtree->parent)
      {
        erase_balance_case2(child);
      }
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::erase_balance_case2(detail::TreeNode< Key, T > * subtree)
  {
    using namespace detail;
    TreeNode< Key, T > * brother = find_brother(subtree);
    if (is_color< RED >(brother))
    {
      colorize< RED >(subtree->parent);
      colorize< BLACK >(brother);
      if (subtree == subtree->parent->left)
      {
        rotate_left(subtree->parent);
      }
      else
      {
        rotate_right(subtree->parent);
      }
    }
    erase_balance_case3(subtree);
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::erase_balance_case3(detail::TreeNode< Key, T > * subtree)
  {
    using namespace detail;
    TreeNode< Key, T > * brother = find_brother(subtree);
    bool is_any_child_black = is_color< BLACK >(brother->left) && is_color< BLACK >(brother->right);
    if (is_color< BLACK >(subtree->parent) && is_color< BLACK >(brother) && is_any_child_black)
    {
      colorize< RED >(brother);
      erase_balance_case1(subtree->parent);
    }
    else
    {
      erase_balance_case4(subtree);
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::erase_balance_case4(detail::TreeNode< Key, T > * subtree)
  {
    using namespace detail;
    TreeNode< Key, T > * brother = find_brother(subtree);
    bool is_any_child_black = is_color< BLACK >(brother->left) && is_color< BLACK >(brother->right);
    if (is_color< RED >(subtree->parent) && is_color< BLACK >(brother) && is_any_child_black)
    {
      colorize< RED >(brother);
      colorize< BLACK >(subtree->parent);
    }
    else
    {
      erase_balance_case5(subtree);
    }
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::erase_balance_case5(detail::TreeNode< Key, T > * subtree)
  {
    using namespace detail;
    TreeNode< Key, T > * brother = find_brother(subtree);
    if (is_color< BLACK >(brother))
    {
      if (subtree == subtree->parent->left && is_color< BLACK >(brother->right) && is_color< RED >(brother->left))
      {
        colorize< RED >(brother);
        colorize< BLACK >(brother->left);
        rotate_right(brother);
      }
      else if (subtree == subtree->parent->right && is_color< RED >(brother->right) && is_color< BLACK >(brother->left))
      {
        colorize< RED >(brother);
        colorize< BLACK >(brother->right);
        rotate_left(brother);
      }
    }
    erase_balance_case6(subtree);
  }

  template< class Key, class T, class Compare >
  void RedBlackTree< Key, T, Compare >::erase_balance_case6(detail::TreeNode< Key, T > * subtree)
  {
    using namespace detail;
    TreeNode< Key, T > * brother = find_brother(subtree);
    brother->color = subtree->parent->color;
    colorize< BLACK >(subtree->parent);
    if (subtree == subtree->parent->left)
    {
      colorize< BLACK >(brother->right);
      rotate_left(subtree->parent);
    }
    else
    {
      colorize< BLACK >(brother->left);
      rotate_right(subtree->parent);
    }
  }
}

#endif
