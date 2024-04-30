// ReSharper disable CppDFAUnreachableCode
#ifndef TWOTHREETREE_HPP
#define TWOTHREETREE_HPP

#include <functional>

#include "const_iterator.hpp"
#include "iterator.hpp"
#include "node.hpp"

namespace zhalilov
{
  template < class Key, class T, class Compare = std::less < Key > >
  class TwoThree
  {
  public:
    using MapPair = std::pair < Key, T >;
    using iterator = TwoThreeIterator < MapPair >;
    using const_iterator = ConstTwoThreeIterator < MapPair >;

    TwoThree() = default;
    TwoThree(const TwoThree &);
    TwoThree(TwoThree &&) noexcept;
    ~TwoThree();

    TwoThree &operator=(const TwoThree &);
    TwoThree &operator=(TwoThree &&) noexcept;

    T &at(const Key &);
    const T &at(const Key &) const;
    T &operator[](const Key &);
    T &operator[](Key &&);

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const noexcept;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const noexcept;

    bool empty() const noexcept;
    size_t size() const;

    std::pair < iterator, bool > insert(const MapPair &);
    void clear() noexcept;
    void swap(TwoThree &) noexcept;

    iterator find(const Key &);
    const_iterator find(const Key &) const;

  private:
    using Node = detail::Node < MapPair >;
    Node *head_;
    size_t size_;

    std::pair < iterator, bool > doFind(const Key &);
    Node *createTwoNode(Node *, const MapPair &) const;
    Node *createThreeNode(Node *, const MapPair &, const MapPair &) const;
    void connectNodes(Node *parent, Node *left, Node *right, Node *mid = nullptr);
  };

  template < class Key, class T, class Compare >
  TwoThree < Key, T, Compare >::TwoThree(const TwoThree &other):
    TwoThree()
  {
    auto it = other.cbegin();
    auto endIt = other.cend();
    while (it != endIt)
    {
      insert(it.node_.first, it.node_.second);
      it++;
    }
  }

  template < class Key, class T, class Compare >
  TwoThree < Key, T, Compare >::TwoThree(TwoThree &&other) noexcept:
    head_(other.head_),
    size_(other.size_)
  {
    other.size_ = 0;
    other.head_ = nullptr;
  }

  template < class Key, class T, class Compare >
  TwoThree < Key, T, Compare >::~TwoThree()
  {
    clear();
  }

  template < class Key, class T, class Compare >
  TwoThree < Key, T, Compare > &TwoThree < Key, T, Compare >::operator=(const TwoThree &other)
  {
    TwoThree temp(other);
    swap(temp);
    return *this;
  }

  template < class Key, class T, class Compare >
  TwoThree < Key, T, Compare > &TwoThree < Key, T, Compare >::operator=(TwoThree &&other) noexcept
  {
    if (head_ != other.head_)
    {
      clear();
      head_ = other.head_;
      size_ = other.size_;
      other.head_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  template < class Key, class T, class Compare >
  T &TwoThree < Key, T, Compare >::at(const Key &key)
  {
    auto it = find(key);
    if (it == end())
    {
      throw std::out_of_range("TwoThree: accessing element doesn't exist");
    }
    return *it;
  }

  template < class Key, class T, class Compare >
  const T &TwoThree < Key, T, Compare >::at(const Key &key) const
  {
    auto it = find(key);
    if (it == cend())
    {
      throw std::out_of_range("TwoThree: accessing element doesn't exist");
    }
    return *it;
  }

  template < class Key, class T, class Compare >
  T &TwoThree < Key, T, Compare >::operator[](const Key &key)
  {
    return *((insert(std::make_pair(key, T()))).first);
  }

  template < class Key, class T, class Compare >
  T &TwoThree < Key, T, Compare >::operator[](Key &&key)
  {
    return *((insert(std::make_pair(std::move(key), T()))).first);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::iterator TwoThree < Key, T, Compare >::begin()
  {
    return iterator(iterator::findMin(head_->left), true);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::const_iterator TwoThree < Key, T, Compare >::begin() const
  {
    return const_iterator(const_iterator::findMin(head_->left), true);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::const_iterator TwoThree < Key, T, Compare >::cbegin() const noexcept
  {
    return const_iterator(const_iterator::findMin(head_->left), true);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::iterator TwoThree < Key, T, Compare >::end()
  {
    return iterator(head_, true);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::const_iterator TwoThree < Key, T, Compare >::end() const
  {
    return const_iterator(head_, true);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::const_iterator TwoThree < Key, T, Compare >::cend() const noexcept
  {
    return const_iterator(head_, true);
  }

  template < class Key, class T, class Compare >
  bool TwoThree < Key, T, Compare >::empty() const noexcept
  {
    return size_ == 0;
  }

  template < class Key, class T, class Compare >
  size_t TwoThree < Key, T, Compare >::size() const
  {
    return size_;
  }

  template < class Key, class T, class Compare >
  std::pair < typename TwoThree < Key, T, Compare >::iterator, bool > TwoThree < Key, T, Compare >::insert(const MapPair &newPair)
  {
    if (empty())
    {
      head_ = createTwoNode(nullptr, MapPair());
      Node *newNode = createTwoNode(head_, newPair);
      head_->left = newNode;
      size_++;
      return std::make_pair(begin(), true);
    }

    auto resultPair = doFind(newPair.first);
    if (!resultPair.second)
    {
      Node *prevLeft = nullptr;
      Node *prevRight = nullptr;
      MapPair currPair = newPair;
      Node *currNode = resultPair.first.node_;
      while (currNode == detail::NodeType::Three)
      {
        if (Compare(currPair.first, currNode->one.first))
        {
          Node *newRight = createTwoNode(nullptr, currNode->two);
          connectNodes(newRight, currNode->mid, currNode->right);
          connectNodes(currNode, prevLeft, prevRight);
          std::swap(currPair, currNode->one);
          prevRight = newRight;
          prevLeft = currNode;
        }
        else if (Compare(currPair.first, currNode->two.first))
        {
          Node *newRight = createTwoNode(nullptr, currNode->two);
          connectNodes(newRight, prevRight, currNode->right);
          connectNodes(currNode, currNode->left, prevLeft);
          prevRight = newRight;
          prevLeft = currNode;
        }
        else
        {
          Node *newLeft = createTwoNode(nullptr, currNode->one);
          connectNodes(newLeft, currNode->left, currNode->mid);
          connectNodes(currNode, prevLeft, prevRight);
          std::swap(currPair, currNode->two);
          prevRight = currNode;
          prevLeft = newLeft;
        }
        currNode->type = detail::NodeType::Two;
        currNode = currNode->parent;
      }

      if (currNode == head_)
      {
        Node *newNode = createTwoNode(head_, currPair);
        connectNodes(head_, newNode, nullptr);
        connectNodes(newNode, prevLeft, prevRight);
      }
      else if (Compare(currNode->one.first, newPair.first))
      {
        connectNodes(currNode, currNode->left, prevRight, prevLeft);
        currNode->two = newPair;
      }
      else
      {
        connectNodes(currNode, prevLeft, currNode->right, prevRight);
        currNode->one = newPair;
      }
      currNode->type = detail::NodeType::Three;
      size_++;
      return std::make_pair(doFind(newPair.key).first, true);
    }
    return std::make_pair(resultPair.first, false);
  }

  template < class Key, class T, class Compare >
  void TwoThree < Key, T, Compare >::clear() noexcept
  {
    auto it = begin();
    auto endIt = end();
    while (it != endIt)
    {
      auto prevIt = it;
      it++;
      if (prevIt.node_->parent == it.node_)
      {
        delete prevIt.node_;
      }
    }
    delete head_;
    size_ = 0;
  }

  template < class Key, class T, class Compare >
  void TwoThree < Key, T, Compare >::swap(TwoThree &other) noexcept
  {
    TwoThree temp(std::move(*this));
    *this = std::move(other);
    other = std::move(temp);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::iterator TwoThree < Key, T, Compare >::find(const Key &key)
  {
    auto resultPair = doFind(key);
    if (resultPair.second)
    {
      return std::make_pair(resultPair.first, true);
    }
    return std::make_pair(end(), false);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::const_iterator TwoThree < Key, T, Compare >::find(const Key &key) const
  {
    auto resultPair = doFind(key);
    if (resultPair.second)
    {
      return std::make_pair(const_iterator(resultPair.first.node_, resultPair.first.isPtrToLeft_), true);
    }
    return std::make_pair(cend(), false);
  }

  template < class Key, class T, class Compare >
  std::pair < typename TwoThree < Key, T, Compare >::iterator, bool > TwoThree < Key, T, Compare >::doFind(const Key &key)
  {
    Node *currNode = head_->left;
    while (currNode)
    {
      Node *proposedNext = currNode->right;
      if (Compare(key, currNode->one.first))
      {
        proposedNext = currNode->left;
      }
      else if (!Compare(currNode->one.first, key))
      {
        return std::make_pair(iterator(currNode, true), true);
      }
      else if (currNode->type == detail::NodeType::Three)
      {
        if (Compare(key, currNode->two.first))
        {
          proposedNext = currNode->mid;
        }
        else if (!Compare(currNode->two.first, key))
        {
          return std::make_pair(iterator(currNode, false), true);
        }
      }
      currNode = proposedNext;
    }
    return std::make_pair(iterator(currNode->parent, true), false);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::Node *TwoThree < Key, T, Compare >::createTwoNode(Node *parent, const MapPair &pair) const
  {
    return new Node{ parent, nullptr, nullptr, nullptr, pair, pair, detail::NodeType::Two };
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::Node *TwoThree < Key, T, Compare >::createThreeNode(Node *parent, const MapPair &pair1, const MapPair &pair2) const
  {
    return new Node{ parent, nullptr, nullptr, nullptr, pair1, pair2, detail::NodeType::Three };
  }

  template < class Key, class T, class Compare >
  void TwoThree < Key, T, Compare >::connectNodes(Node *parent, Node *left, Node *right, Node *mid)
  {
    parent->left = left;
    parent->right = right;
    parent->mid = mid;
    if (left)
    {
      left->parent = parent;
      right->parent = parent;
      if (mid)
      {
        mid->parent = parent;
      }
    }
  }
}

#endif
