#ifndef TREE_HPP
#define TREE_HPP

#include <functional>
#include <stdexcept>
#include <queue.hpp>
#include <initializer_list>
#include "treeIter.hpp"
#include "constTreeIter.hpp"
#include "LNRIter.hpp"
#include "constLNRIter.hpp"
#include "RNLIter.hpp"
#include "constRNLIter.hpp"

namespace isaychev
{
  template < class Key, class Value, class Compare = std::less< Key > >
  class BSTree
  {
    using tree_t = BSTree< Key, Value, Compare >;
    using node_t = detail::TreeNode< Key, Value >;
    using iterator = TreeIter< Key, Value, Compare >;
    using const_iterator = ConstTreeIter< Key, Value, Compare >;
    using value_t = std::pair< Key, Value >;
    using lnr_iterator = LNRIter< Key, Value, Compare >;
    using const_lnr_iterator = ConstLNRIter< Key, Value, Compare >;
    using rnl_iterator = RNLIter< Key, Value, Compare >;
    using const_rnl_iterator = ConstRNLIter< Key, Value, Compare >;

   public:
    BSTree();
    ~BSTree();
    BSTree(const tree_t & rhs);
    BSTree(tree_t && rhs);
    BSTree(std::initializer_list< value_t > l);
    template < class InputIt >
    BSTree(InputIt first, InputIt last);
    tree_t & operator=(const tree_t & rhs);
    tree_t & operator=(tree_t && rhs);

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    lnr_iterator lnrbegin();
    lnr_iterator lnrend();
    const_lnr_iterator lnrbegin() const;
    const_lnr_iterator lnrend() const;
    const_lnr_iterator clnrbegin() const;
    const_lnr_iterator clnrend() const;
    rnl_iterator rnlbegin();
    rnl_iterator rnlend();
    const_rnl_iterator rnlbegin() const;
    const_rnl_iterator rnlend() const;
    const_rnl_iterator crnlbegin() const;
    const_rnl_iterator crnlend() const;

    size_t size() const noexcept;
    bool empty() const noexcept;
    void clear() noexcept;
    void swap(tree_t & other) noexcept;
    iterator find(const Key & key);
    const_iterator find(const Key & key) const;
    size_t count(const Key & key) const;
    std::pair< iterator, iterator > equal_range(const Key & key);
    std::pair< const_iterator, const_iterator > equal_range(const Key & key) const;
    iterator lower_bound(const Key & key);
    const_iterator lower_bound(const Key & key) const;
    iterator upper_bound(const Key & key);
    const_iterator upper_bound(const Key & key) const;

    Value & at(const Key & key);
    const Value & at(const Key & key) const;
    Value & operator[](const Key & key);
    std::pair< iterator, bool > insert(const value_t & value);
    template < class InputIt >
    void insert(InputIt first, InputIt last);
    iterator erase(iterator pos);
    const_iterator erase(const_iterator pos);
    size_t erase(const Key & key);
    iterator erase(iterator first, iterator last);
    iterator erase(const_iterator first, const_iterator last);

    template < class F >
    F traverse_lnr(F f) const;
    template < class F >
    F traverse_lnr(F f);
    template < class F >
    F traverse_rnl(F f) const;
    template < class F >
    F traverse_rnl(F f);
    template < class F >
    F traverse_breadth(F f) const;
    template < class F >
    F traverse_breadth(F f);

   private:
    node_t * root_;
    Compare cmp_;
    size_t size_;

    void delete_tree(node_t * ptr) noexcept;
    void erase_el(node_t * curr);
    std::pair< node_t *, bool > insert_new(const value_t & value);
    node_t * find_el(const Key & key) const;
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
  BSTree< Key, Value, Compare >::BSTree(const tree_t & rhs):
   BSTree(rhs.cbegin(), rhs.cend())
  {}

  template < class Key, class Value, class Compare >
  BSTree< Key, Value, Compare >::BSTree(tree_t && rhs):
   root_(rhs.root_),
   cmp_(rhs.cmp_),
   size_(rhs.size_)
  {
    rhs.root_ = nullptr;
    rhs.size_ = 0;
  }

  template < class Key, class Value, class Compare >
  BSTree< Key, Value, Compare >::BSTree(std::initializer_list< value_t > l):
   BSTree(l.begin(), l.end())
  {}

  template < class Key, class Value, class Compare >
  template < class InputIt >
  BSTree< Key, Value, Compare >::BSTree(InputIt first, InputIt last):
   root_(nullptr),
   cmp_(),
   size_(0)
  {
    for (; first != last; ++first)
    {
      insert(*first);
    }
  }

  template < class Key, class Value, class Compare >
  BSTree< Key, Value, Compare > & BSTree< Key, Value, Compare >::operator=(const tree_t & rhs)
  {
    if (this != std::addressof(rhs))
    {
      clear();
      cmp_ = rhs.cmp_;
      for (auto i = rhs.cbegin(); i != rhs.cend(); ++i)
      {
        (*this)[(*i).first] = (*i).second;
      }
    }
    return *this;
  }

  template < class Key, class Value, class Compare >
  BSTree< Key, Value, Compare > & BSTree< Key, Value, Compare >::operator=(tree_t && rhs)
  {
    if (this != std::addressof(rhs))
    {
      clear();
      root_ = rhs.root_;
      cmp_ = rhs.cmp_;
      size_ = rhs.size_;
      rhs.root_ = nullptr;
      rhs.size_ = 0;
    }
    return *this;
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::begin() noexcept
  {
    return TreeIter< Key, Value, Compare >(detail::traverse_left(root_));
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::end() noexcept
  {
    return TreeIter< Key, Value, Compare >();
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::begin() const noexcept
  {
    return ConstTreeIter< Key, Value, Compare >(detail::traverse_left(root_));
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::end() const noexcept
  {
    return ConstTreeIter< Key, Value, Compare >();
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::cbegin() const noexcept
  {
    return ConstTreeIter< Key, Value, Compare >(detail::traverse_left(root_));
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::cend() const noexcept
  {
    return ConstTreeIter< Key, Value, Compare >();
  }

  template < class Key, class Value, class Compare >
  LNRIter< Key, Value, Compare > BSTree< Key, Value, Compare >::lnrbegin()
  {
    Stack< node_t * > s;
    auto curr = root_;
    while (curr && curr->left)
    {
      s.push(curr);
      curr = curr->left;
    }
    return lnr_iterator(curr, std::move(s));
  }

  template < class Key, class Value, class Compare >
  LNRIter< Key, Value, Compare > BSTree< Key, Value, Compare >::lnrend()
  {
    return lnr_iterator(nullptr, Stack< node_t * >());
  }

  template < class Key, class Value, class Compare >
  ConstLNRIter< Key, Value, Compare > BSTree< Key, Value, Compare >::lnrbegin() const
  {
    Stack< node_t * > s;
    auto curr = root_;
    while (curr && curr->left)
    {
      s.push(curr);
      curr = curr->left;
    }
    return const_lnr_iterator(curr, std::move(s));
  }

  template < class Key, class Value, class Compare >
  ConstLNRIter< Key, Value, Compare > BSTree< Key, Value, Compare >::lnrend() const
  {
    return const_lnr_iterator(nullptr, Stack< node_t * >());
  }

  template < class Key, class Value, class Compare >
  ConstLNRIter< Key, Value, Compare > BSTree< Key, Value, Compare >::clnrbegin() const
  {
    Stack< const node_t * > s;
    auto curr = root_;
    while (curr && curr->left)
    {
      s.push(curr);
      curr = curr->left;
    }
    return const_lnr_iterator(curr, std::move(s));
  }

  template < class Key, class Value, class Compare >
  ConstLNRIter< Key, Value, Compare > BSTree< Key, Value, Compare >::clnrend() const
  {
    return const_lnr_iterator(nullptr, Stack< const node_t * >());
  }

  template < class Key, class Value, class Compare >
  RNLIter< Key, Value, Compare > BSTree< Key, Value, Compare >::rnlbegin()
  {
    Stack< node_t * > s;
    auto curr = root_;
    while (curr && curr->right)
    {
      s.push(curr);
      curr = curr->right;
    }
    return rnl_iterator(curr, std::move(s));
  }

  template < class Key, class Value, class Compare >
  RNLIter< Key, Value, Compare > BSTree< Key, Value, Compare >::rnlend()
  {
    return rnl_iterator(nullptr, Stack< node_t * >());
  }

  template < class Key, class Value, class Compare >
  ConstRNLIter< Key, Value, Compare > BSTree< Key, Value, Compare >::rnlbegin() const
  {
    Stack< const node_t * > s;
    auto curr = root_;
    while (curr && curr->right)
    {
      s.push(curr);
      curr = curr->right;
    }
    return const_rnl_iterator(curr, std::move(s));
  }

  template < class Key, class Value, class Compare >
  ConstRNLIter< Key, Value, Compare > BSTree< Key, Value, Compare >::rnlend() const
  {
    return const_rnl_iterator(nullptr, Stack< const node_t * >());
  }

  template < class Key, class Value, class Compare >
  ConstRNLIter< Key, Value, Compare > BSTree< Key, Value, Compare >::crnlbegin() const
  {
    Stack< const node_t * > s;
    auto curr = root_;
    while (curr && curr->right)
    {
      s.push(curr);
      curr = curr->right;
    }
    return const_rnl_iterator(curr, std::move(s));
  }

  template < class Key, class Value, class Compare >
  ConstRNLIter< Key, Value, Compare > BSTree< Key, Value, Compare >::crnlend() const
  {
    return const_rnl_iterator(nullptr, Stack< const node_t * >());
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
  void BSTree< Key, Value, Compare >::clear() noexcept
  {
    delete_tree(root_);
    root_ = nullptr;
    size_ = 0;
  }

  template < class Key, class Value, class Compare >
  void BSTree< Key, Value, Compare >::swap(tree_t & other) noexcept
  {
    std::swap(root_, other.root_);
    std::swap(cmp_, other.cmp_);
    std::swap(size_, other.size_);
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::find(const Key & key)
  {
    return iterator(find_el(key));
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::find(const Key & key) const
  {
    return const_iterator(find_el(key));
  }

  template < class Key, class Value, class Compare >
  size_t BSTree< Key, Value, Compare >::count(const Key & key) const
  {
    auto result = find(key);
    if (!result.current_)
    {
      return 0;
    }
    return 1;
  }

  template < class Key, class Value, class Compare >
  std::pair< TreeIter< Key, Value, Compare >, TreeIter< Key, Value, Compare > >
  BSTree< Key, Value, Compare >::equal_range(const Key & key)
  {
    auto res = static_cast< const tree_t & >(*this).equal_range(key);
    return std::pair< iterator, iterator >(iterator(res.first.current_), iterator(res.second.current_));
  }

  template < class Key, class Value, class Compare >
  std::pair< ConstTreeIter< Key, Value, Compare >, ConstTreeIter< Key, Value, Compare > >
  BSTree< Key, Value, Compare >::equal_range(const Key & key) const
  {
    const_iterator result = find(key);
    if (!result.current_)
    {
      return std::pair< const_iterator, const_iterator >(cend(), cend());
    }
    const_iterator lesser;
    if (result == (*this).cbegin())
    {
      return std::pair< const_iterator, const_iterator >(cend(), ++result);
    }
    lesser = result++;
    --lesser;
    return std::pair< const_iterator, const_iterator >(lesser, result);
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::lower_bound(const Key & key)
  {
    return iterator((static_cast< const tree_t & >(*this).lower_bound(key)).current_);
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::lower_bound(const Key & key) const
  {
    node_t * temp = root_;
    while (temp)
    {
      if (!cmp_(temp->data.first, key))
      {
        return const_iterator(temp);
      }
      if (cmp_(key, temp->data.first))
      {
        temp = temp->left;
      }
      else
      {
        temp = temp->right;
      }
    }
    return cend();
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::upper_bound(const Key & key)
  {
    return iterator((static_cast< const tree_t & >(*this).upper_bound(key)).current_);
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::upper_bound(const Key & key) const
  {
    node_t * temp = root_;
    while (temp)
    {
      if (cmp_(temp->data.first, key))
      {
        return const_iterator(temp);
      }
      if (cmp_(key, temp->data.first))
      {
        temp = temp->left;
      }
      else
      {
        temp = temp->right;
      }
    }
    return cend();
  }

  template < class Key, class Value, class Compare >
  Value & BSTree< Key, Value, Compare >::at(const Key & key)
  {
    return const_cast< Value & >(static_cast< const tree_t & >(*this).at(key));
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
  template < class InputIt >
  void BSTree< Key, Value, Compare >::insert(InputIt first, InputIt last)
  {
    for (; first != last; ++first)
    {
      insert(*first);
    }
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::erase(iterator pos)
  {
    node_t * trash = pos.current_;
    iterator next = ++pos;
    erase_el(trash);
    return next;
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare >  BSTree< Key, Value, Compare >::erase(const_iterator pos)
  {
    node_t * trash = pos.current_;
    const_iterator next = ++pos;
    erase_el(trash);
    return next;
  }

  template < class Key, class Value, class Compare >
  size_t BSTree< Key, Value, Compare >::erase(const Key & key)
  {
    auto trash = find(key);
    if (!trash.current_)
    {
      return 0;
    }
    erase_el(trash.current_);
    return 1;
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::erase(iterator first, iterator last)
  {
    iterator curr_next;
    while (first != last)
    {
      curr_next = erase(first++);
    }
    return curr_next;
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::erase(const_iterator first, const_iterator last)
  {
    return erase(iterator(first.current_), iterator(last.current_));
  }

  template < class Key, class Value, class Compare >
  template < class F >
  F BSTree< Key, Value, Compare >::traverse_lnr(F f) const
  {
    if (!root_)
    {
      return f;
    }
    for (auto i = (*this).clnrbegin(); i != (*this).clnrend(); ++i)
    {
      f(*i);
    }
    return f;
  }

  template < class Key, class Value, class Compare >
  template < class F >
  F BSTree< Key, Value, Compare >::traverse_lnr(F f)
  {
    if (!root_)
    {
      return f;
    }
    for (auto i = (*this).lnrbegin(); i != (*this).lnrend(); ++i)
    {
      f(*i);
    }
    return f;
  }

  template < class Key, class Value, class Compare >
  template < class F >
  F BSTree< Key, Value, Compare >::traverse_rnl(F f) const
  {
    if (!root_)
    {
      return f;
    }
    for (auto i = (*this).crnlbegin(); i != (*this).crnlend(); ++i)
    {
      f(*i);
    }
    return f;
  }

  template < class Key, class Value, class Compare >
  template < class F >
  F BSTree< Key, Value, Compare >::traverse_rnl(F f)
  {
    if (!root_)
    {
      return f;
    }
    for (auto i = (*this).rnlbegin(); i != (*this).rnlend(); ++i)
    {
      f(*i);
    }
    return f;
  }

  template < class Key, class Value, class Compare >
  template < class F >
  F BSTree< Key, Value, Compare >::traverse_breadth(F f) const
  {
    if (!root_)
    {
      return f;
    }
    node_t * current = root_;
    Queue< node_t * > q;
    q.push(root_);
    while (!q.empty())
    {
      current = q.front();
      q.pop();
      if (current)
      {
        q.push(current->left);
        q.push(current->right);
        f(current->data);
      }
    }
    return f;
  }

  template < class Key, class Value, class Compare >
  template < class F >
  F BSTree< Key, Value, Compare >::traverse_breadth(F f)
  {
    if (!root_)
    {
      return f;
    }
    const node_t * current = root_;
    Queue< const node_t * > q;
    q.push(root_);
    while (!q.empty())
    {
      current = q.front();
      q.pop();
      if (current)
      {
        q.push(current->left);
        q.push(current->right);
        f(current->data);
      }
    }
    return f;
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
  void BSTree< Key, Value, Compare >::erase_el(node_t * curr)
  {
    if (curr)
    {
      if (!curr->left && !curr->right)
      {
        if (!curr->parent)
        {
          root_ = nullptr;
        }
        else if (curr->parent->left == curr)
        {
          curr->parent->left = nullptr;
        }
        else if (curr->parent->right == curr)
        {
          curr->parent->right = nullptr;
        }
      }
      else if (!curr->left)
      {
        if (!curr->parent)
        {
          root_ = curr->right;
          curr->right->parent = nullptr;
        }
        else if (curr->parent->left == curr)
        {
          curr->parent->left = curr->right;
          curr->right->parent = curr->parent;
        }
        else if (curr->parent->right == curr)
        {
          curr->parent->right = curr->right;
          curr->right->parent = curr->parent;
        }
      }
      else if (!curr->right)
      {
        if (!curr->parent)
        {
          root_ = curr->left;
          curr->left->parent = nullptr;
        }
        else if (curr->parent->left == curr)
        {
          curr->parent->left = curr->left;
          curr->left->parent = curr->parent;
        }
        else if (curr->parent->right == curr)
        {
          curr->parent->right = curr->left;
          curr->left->parent = curr->parent;
        }
      }
      else
      {
        node_t * min_right = detail::traverse_left(curr->right);
        min_right->left = curr->left;
        curr->left->parent = min_right;
        if (!curr->parent)
        {
          root_ = min_right;
          min_right->parent = nullptr;
        }
        else
        {
          if (curr->parent->left == curr)
          {
            curr->parent->left = curr->right;
          }
          else if (curr->parent->right == curr)
          {
            curr->parent->right = curr->right;
          }
          curr->right->parent = curr->parent;
        }
      }
      --size_;
      delete curr;
    }
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

  template < class Key, class Value, class Compare >
  detail::TreeNode< Key, Value > * BSTree< Key, Value, Compare >::find_el(const Key & key) const
  {
    node_t * current = root_;
    while (current)
    {
      if (key == current->data.first)
      {
        return current;
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
    return nullptr;
  }
}

#endif
