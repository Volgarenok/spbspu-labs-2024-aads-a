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

    TwoThree();

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

    bool empty();
    size_t size();

    std::pair < iterator, bool > insert(const MapPair &);
    void clear();
    void swap();

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
  TwoThree < Key, T, Compare >::TwoThree() :
    head_(nullptr), size_(0)
  {}

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
