#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <utility>
#include <cassert>
#include <functional>
#include <stdexcept>
#include <initializer_list>
#include "tree_node.hpp"
#include "tree_iterator.hpp"
#include "const_tree_iterator.hpp"
#include "traverse_iterators.hpp"

namespace nikitov
{
  template< class Key, class T, class Compare = std::less< Key > >
  class Tree
  {
  public:
    typedef TreeIterator< Key, T, Compare > treeIterator;
    typedef ConstTreeIterator< Key, T, Compare > constTreeIterator;
    Tree();
    Tree(constTreeIterator first, constTreeIterator second);
    Tree(std::initializer_list< std::pair< Key, T > > initList);
    Tree(const Tree< Key, T, Compare >& other);
    Tree(Tree< Key, T, Compare >&& other) noexcept;
    ~Tree();

    Tree< Key, T, Compare >& operator=(const Tree& other);
    Tree< Key, T, Compare >& operator=(Tree&& other) noexcept;

    T& operator[](const Key& key) noexcept;
    T& operator[](Key&& key) noexcept;

    T& at(const Key& key);
    const T& at(const Key& key) const;

    treeIterator begin() noexcept;
    constTreeIterator cbegin() const noexcept;
    treeIterator end() noexcept;
    constTreeIterator cend() const noexcept;

    LNRIterator< Key, T, Compare > LNRCbegin() const noexcept;
    LNRIterator< Key, T, Compare > LNRCend() const noexcept;
    RNLIterator< Key, T, Compare > RNLCbegin() const noexcept;
    RNLIterator< Key, T, Compare > RNLCend() const noexcept;
    BreadthIterator< Key, T, Compare > BreadthCbegin() const noexcept;
    BreadthIterator< Key, T, Compare > BreadthCend() const noexcept;

    size_t size() const noexcept;
    bool empty() const noexcept;

    std::pair< treeIterator, bool > insert(const std::pair< Key, T >& value);
    std::pair< treeIterator, bool > insert(std::pair< Key, T >&& value);
    void insert(constTreeIterator first, constTreeIterator second);
    void insert(std::initializer_list< std::pair< Key, T > > initList);

    treeIterator erase(treeIterator position);
    treeIterator erase(constTreeIterator position);
    treeIterator erase(constTreeIterator first, constTreeIterator last);

    void clear() noexcept;
    void swap(Tree< Key, T, Compare >& other) noexcept;

    size_t count(const Key& key) const;
    treeIterator find(const Key& key) noexcept;
    constTreeIterator find(const Key& key) const noexcept;

    treeIterator lowerBound(const Key& key);
    constTreeIterator lowerBound(const Key& key) const;
    treeIterator upperBound(const Key& key);
    constTreeIterator upperBound(const Key& key) const;
    std::pair< treeIterator, treeIterator > equalRange(const Key& key);
    std::pair< constTreeIterator, constTreeIterator > equalRange(const Key& key) const;

    template< class F >
    F traverseLNR(F f);
    template< class F >
    F traverseLNR(F f) const;
    template< class F >
    F traverseRNL(F f);
    template< class F >
    F traverseRNL(F f) const;
    template< class F >
    F traverseBreadth(F f);
    template< class F >
    F traverseBreadth(F f) const;

  private:
    detail::TreeNode< Key, T, Compare >* root_;
    size_t size_;
    Compare cmp_;

    detail::TreeNode< Key, T, Compare >* search(detail::TreeNode< Key, T, Compare >* node, const Key& key) const;
    detail::TreeNode< Key, T, Compare >* findToInsert(const Key& value) const;

    std::pair< TreeIterator< Key, T, Compare >, bool > embed(const std::pair< Key, T >& value);
    std::pair< TreeIterator< Key, T, Compare >, bool > moveEmbed(std::pair< Key, T >&& value);
  };

  template< class Key, class T, class Compare >
  Tree< Key, T, Compare >::Tree():
    root_(new detail::TreeNode< Key, T, Compare >()),
    size_(0),
    cmp_(Compare())
  {}

  template< class Key, class T, class Compare >
  Tree< Key, T, Compare >::Tree(constTreeIterator first, constTreeIterator second):
    Tree()
  {
    for (auto i = first; i != second; ++i)
    {
      embed(*i);
    }
  }

  template< class Key, class T, class Compare >
  Tree< Key, T, Compare >::Tree(std::initializer_list< std::pair< Key, T > > initList):
    Tree()
  {
    for (auto i = initList.begin(); i != initList.end(); ++i)
    {
      embed(*i);
    }
  }

  template< class Key, class T, class Compare >
  Tree< Key, T, Compare >::Tree(const Tree< Key, T, Compare >& other):
    Tree(other.cbegin(), other.cend())
  {}

  template< class Key, class T, class Compare >
  Tree< Key, T, Compare >::Tree(Tree< Key, T, Compare >&& other) noexcept:
    root_(other.root_),
    size_(other.size_),
    cmp_(other.cmp_)
  {
    other.root_ = new detail::TreeNode< Key, T, Compare >();
    other.size_ = 0;
  }

  template< class Key, class T, class Compare >
  Tree< Key, T, Compare >::~Tree()
  {
    clear();
    delete root_;
  }

  template< class Key, class T, class Compare >
  Tree< Key, T, Compare >& Tree< Key, T, Compare >::operator=(const Tree& other)
  {
    Tree< Key, T, Compare > temp(other);
    if (std::addressof(other) != this)
    {
      swap(temp);
    }
    return *this;
  }

  template< class Key, class T, class Compare >
  Tree< Key, T, Compare >& Tree< Key, T, Compare >::operator=(Tree&& other) noexcept
  {
    Tree< Key, T, Compare > temp(std::move(other));
    if (std::addressof(other) != this)
    {
      swap(temp);
    }
    return *this;
  }

  template< class Key, class T, class Compare >
  T& Tree< Key, T, Compare >::operator[](const Key& key) noexcept
  {
    detail::TreeNode< Key, T, Compare >* node = search(root_, key);
    if (!node)
    {
      insert({ key, T() });
      node = search(root_, key);
    }
    return node->get(key);
  }

  template< class Key, class T, class Compare >
  T& Tree< Key, T, Compare >::operator[](Key&& key) noexcept
  {
    detail::TreeNode< Key, T, Compare >* node = search(root_, key);
    if (!node)
    {
      insert({ key, T() });
      node = search(root_, key);
    }
    return node->get(key);
  }

  template< class Key, class T, class Compare >
  T& Tree< Key, T, Compare >::at(const Key& key)
  {
    detail::TreeNode< Key, T, Compare >* node = search(root_, key);
    if (!node)
    {
      throw std::out_of_range("Error: No element by key");
    }
    return node->get(key);
  }

  template< class Key, class T, class Compare >
  const T& Tree< Key, T, Compare >::at(const Key& key) const
  {
    detail::TreeNode< Key, T, Compare >* node = search(root_, key);
    if (!node)
    {
      throw std::out_of_range("Error: No element by key");
    }
    return node->get(key);
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T, Compare > Tree< Key, T, Compare >::begin() noexcept
  {
    treeIterator iterator(root_);
    iterator.fallLeft();
    return iterator;
  }

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare > Tree< Key, T, Compare >::cbegin() const noexcept
  {
    constTreeIterator iterator(root_);
    iterator.fallLeft();
    return iterator;
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T, Compare > Tree< Key, T, Compare >::end() noexcept
  {
    if (empty())
    {
      return treeIterator(root_);
    }
    return treeIterator(root_->parent_);
  }

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare > Tree< Key, T, Compare >::cend() const noexcept
  {
    if (empty())
    {
      return constTreeIterator(root_);
    }
    return constTreeIterator(root_->parent_);
  }

  template< class Key, class T, class Compare >
  LNRIterator< Key, T, Compare > Tree< Key, T, Compare >::LNRCbegin() const noexcept
  {
    return LNRIterator< Key, T, Compare >(cend().node_, cbegin().node_);
  }

  template< class Key, class T, class Compare >
  LNRIterator< Key, T, Compare > Tree< Key, T, Compare >::LNRCend() const noexcept
  {
    return LNRIterator< Key, T, Compare >(cend().node_, cend().node_);
  }

  template< class Key, class T, class Compare >
  RNLIterator< Key, T, Compare > Tree< Key, T, Compare >::RNLCbegin() const noexcept
  {
    return RNLIterator< Key, T, Compare >(cend().node_, (--cend()).node_);
  }

  template< class Key, class T, class Compare >
  RNLIterator< Key, T, Compare > Tree< Key, T, Compare >::RNLCend() const noexcept
  {
    return RNLIterator< Key, T, Compare >(cend().node_, cend().node_);
  }

  template< class Key, class T, class Compare >
  BreadthIterator< Key, T, Compare > Tree< Key, T, Compare >::BreadthCbegin() const noexcept
  {
    return BreadthIterator< Key, T, Compare >(cend().node_, root_);
  }

  template< class Key, class T, class Compare >
  BreadthIterator< Key, T, Compare > Tree< Key, T, Compare >::BreadthCend() const noexcept
  {
    return BreadthIterator< Key, T, Compare >(cend().node_, cend().node_);
  }

  template< class Key, class T, class Compare >
  size_t Tree< Key, T, Compare >::size() const noexcept
  {
    return size_;
  }

  template< class Key, class T, class Compare >
  bool Tree< Key, T, Compare >::empty() const noexcept
  {
    return !size_;
  }

  template< class Key, class T, class Compare >
  std::pair< TreeIterator< Key, T, Compare >, bool > Tree< Key, T, Compare >::insert(const std::pair< Key, T >& value)
  {
    return embed(value);
  }

  template< class Key, class T, class Compare >
  std::pair< TreeIterator< Key, T, Compare >, bool > Tree< Key, T, Compare >::insert(std::pair< Key, T >&& value)
  {
    return moveEmbed(std::move(value));
  }

  template< class Key, class T, class Compare >
  void Tree< Key, T, Compare >::insert(constTreeIterator first, constTreeIterator second)
  {
    for (auto i = first; i != second; ++i)
    {
      embed(*i);
    }
  }

  template< class Key, class T, class Compare >
  void Tree< Key, T, Compare >::insert(std::initializer_list< std::pair< Key, T > > initList)
  {
    auto begin = initList.begin();
    auto end = initList.end();
    while (begin != end)
    {
      embed(*begin++);
    }
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T, Compare > Tree< Key, T, Compare >::erase(treeIterator position)
  {
    return erase(constTreeIterator(position.node_, position.isFirst_));
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T, Compare > Tree< Key, T, Compare >::erase(constTreeIterator position)
  {
    if (size_ == 1)
    {
      root_ = root_->parent_;
      delete root_->middle_;
      root_->middle_ = nullptr;
      --size_;
      return end();
    }

    treeIterator iterator(position.node_, position.isFirst_);
    if (!iterator.node_->isLeaf())
    {
      treeIterator toSwap = iterator--;
      std::swap(*iterator, *toSwap);
    }
    if (iterator.node_->size_ == 2)
    {
      if (iterator.isFirst_)
      {
        iterator.node_->freeFirst();
      }
      else
      {
        iterator.node_->freeSecond();
      }
    }
    else
    {
      detail::TreeNode< Key, T, Compare >* parent = iterator.node_->parent_;
      if (parent->left_ == iterator.node_)
      {
        parent->left_ = nullptr;
      }
      else if (parent->right_ == iterator.node_)
      {
        parent->right_ = nullptr;
      }
      else
      {
        parent->middle_ = nullptr;
      }
      delete iterator.node_;
      parent->fixErase();
    }
    --size_;
    return upperBound((*position).first);
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T, Compare > Tree< Key, T, Compare >::erase(constTreeIterator first, constTreeIterator last)
  {
    if (last == cend())
    {
      while (first != cend())
      {
        treeIterator iterator = erase(first);
        first = constTreeIterator(iterator.node_, iterator.isFirst_);
      }
    }
    else
    {
      Key key = (*last).first;
      while ((*first).first != key)
      {
        treeIterator iterator = erase(first);
        first = constTreeIterator(iterator.node_, iterator.isFirst_);
      }
    }
    return treeIterator(first.node_);
  }

  template< class Key, class T, class Compare >
  void Tree< Key, T, Compare >::clear() noexcept
  {
    root_->clear();
    if (root_->parent_)
    {
      root_ = root_->parent_;
      delete root_->middle_;
    }
    size_ = 0;
  }

  template< class Key, class T, class Compare >
  void Tree< Key, T, Compare >::swap(Tree< Key, T, Compare >& other) noexcept
  {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(cmp_, other.cmp_);
  }

  template< class Key, class T, class Compare >
  size_t Tree< Key, T, Compare >::count(const Key& key) const
  {
    return search(root_, key) != nullptr;
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T, Compare > Tree< Key, T, Compare >::find(const Key& key) noexcept
  {
    detail::TreeNode< Key, T, Compare >* node = search(root_, key);
    if (node)
    {
      bool isFirst = false;
      if (node->firstValue_.first == key)
      {
        isFirst = true;
      }
      return treeIterator(node, isFirst);
    }
    return end();
  }

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare > Tree< Key, T, Compare >::find(const Key& key) const noexcept
  {
    detail::TreeNode< Key, T, Compare >* node = search(root_, key);
    if (node)
    {
      bool isFirst = false;
      if (node->firstValue_.first == key)
      {
        isFirst = true;
      }
      return constTreeIterator(node, isFirst);
    }
    return cend();
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T, Compare > Tree< Key, T, Compare >::lowerBound(const Key& key)
  {
    treeIterator iterator = find(key);
    if (iterator == end())
    {
      iterator = begin();
      while (iterator != end() && (*iterator).first < key)
      {
        ++iterator;
      }
    }
    return iterator;
  }

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare > Tree< Key, T, Compare >::lowerBound(const Key& key) const
  {
    constTreeIterator iterator = find(key);
    if (iterator == cend())
    {
      iterator = cbegin();
      while (iterator != cend() && (*iterator).first < key)
      {
        ++iterator;
      }
    }
    return iterator;
  }

  template< class Key, class T, class Compare >
  TreeIterator< Key, T, Compare > Tree< Key, T, Compare >::upperBound(const Key& key)
  {
    treeIterator iterator = lowerBound(key);
    if (iterator != end() && (*iterator).first == key)
    {
      ++iterator;
    }
    return iterator;
  }

  template< class Key, class T, class Compare >
  ConstTreeIterator< Key, T, Compare > Tree< Key, T, Compare >::upperBound(const Key& key) const
  {
    constTreeIterator iterator = lowerBound(key);
    if (iterator != cend() && (*iterator).first == key)
    {
      ++iterator;
    }
    return iterator;
  }

  template< class Key, class T, class Compare >
  std::pair< TreeIterator< Key, T, Compare >, TreeIterator< Key, T, Compare > >
    Tree< Key, T, Compare >::equalRange(const Key& key)
  {
    return { lowerBound(key), upperBound(key) };
  }

  template< class Key, class T, class Compare >
  std::pair< ConstTreeIterator< Key, T, Compare >, ConstTreeIterator< Key, T, Compare > >
    Tree< Key, T, Compare >::equalRange(const Key& key) const
  {
    return { lowerBound(key), upperBound(key) };
  }

  template< class Key, class T, class Compare >
  template< class F >
  F Tree< Key, T, Compare >::traverseLNR(F f)
  {
    for (auto i = LNRCbegin(); i != LNRCend(); ++i)
    {
      f(*i);
    }
    return f;
  }

  template< class Key, class T, class Compare >
  template< class F >
  F Tree< Key, T, Compare >::traverseLNR(F f) const
  {
    for (auto i = LNRCbegin(); i != LNRCend(); ++i)
    {
      f(*i);
    }
    return f;
  }

  template< class Key, class T, class Compare >
  template< class F >
  F Tree< Key, T, Compare >::traverseRNL(F f)
  {
    for (auto i = RNLCbegin(); i != RNLCend(); ++i)
    {
      f(*i);
    }
    return f;
  }

  template< class Key, class T, class Compare >
  template< class F >
  F Tree< Key, T, Compare >::traverseRNL(F f) const
  {
    for (auto i = RNLCbegin(); i != RNLCend(); ++i)
    {
      f(*i);
    }
    return f;
  }

  template< class Key, class T, class Compare >
  template< class F >
  F Tree< Key, T, Compare >::traverseBreadth(F f)
  {
    for (auto i = BreadthCbegin(); i != BreadthCend(); ++i)
    {
      f(*i);
    }
    return f;
  }

  template< class Key, class T, class Compare >
  template< class F >
  F Tree< Key, T, Compare >::traverseBreadth(F f) const
  {
    for (auto i = BreadthCbegin(); i != BreadthCend(); ++i)
    {
      f(*i);
    }
    return f;
  }

  template< class Key, class T, class Compare >
  detail::TreeNode< Key, T, Compare >* Tree< Key, T, Compare >::search(detail::TreeNode< Key, T, Compare >* node,
    const Key& key) const
  {
    if (!node)
    {
      return nullptr;
    }
    else if (node->find(key))
    {
      return node;
    }
    else if (cmp_(key, node->firstValue_.first))
    {
      return search(node->left_, key);
    }
    else if (node->size_ == 1 || cmp_(node->secondValue_.first, key))
    {
      return search(node->right_, key);
    }
    return search(node->middle_, key);
  }

  template< class Key, class T, class Compare >
  detail::TreeNode< Key, T, Compare >* Tree< Key, T, Compare >::findToInsert(const Key& value) const
  {
    detail::TreeNode< Key, T, Compare >* node = root_;
    while (node->left_ || node->right_)
    {
      if (cmp_(value, node->firstValue_.first))
      {
        node = node->left_;
      }
      else if (node->size_ == 1 || cmp_(node->secondValue_.first, value))
      {
        node = node->right_;
      }
      else
      {
        node = node->middle_;
      }
    }
    return node;
  }

  template< class Key, class T, class Compare >
  std::pair< TreeIterator< Key, T, Compare >, bool > Tree< Key, T, Compare >::embed(const std::pair< Key, T >& value)
  {
    std::pair< Key, T > copy = value;
    return moveEmbed(std::move(copy));
  }

  template< class Key, class T, class Compare >
  std::pair< TreeIterator< Key, T, Compare >, bool > Tree< Key, T, Compare >::moveEmbed(std::pair< Key, T >&& value)
  {
    Key key = value.first;
    bool isInserted = false;
    if (!search(root_, key))
    {
      if (empty())
      {
        root_->middle_ = new detail::TreeNode< Key, T, Compare >(std::move(value));
        root_->middle_->parent_ = root_;
        root_ = root_->middle_;
      }
      else
      {
        detail::TreeNode< Key, T, Compare >* newRoot = findToInsert(key)->moveAdd(std::move(value));
        if (newRoot)
        {
          root_ = newRoot;
        }
      }
      isInserted = true;
      ++size_;
    }
    return std::pair< treeIterator, bool > { find(value.first), isInserted };
  }
}
#endif
