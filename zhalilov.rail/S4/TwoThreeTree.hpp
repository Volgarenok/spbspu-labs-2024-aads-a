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
    void balanceAndInsert(iterator, const MapPair &);
  };

  template < class Key, class T, class Compare >
  TwoThree < Key, T, Compare >::TwoThree() :
    head_(nullptr), size_(0)
  {}

  template < class Key, class T, class Compare >
  std::pair < typename TwoThree < Key, T, Compare >::iterator, bool > TwoThree < Key, T, Compare >::insert(const MapPair &newPair)
  {
    if (empty())
    {
      head_ = createTwoNode(nullptr, MapPair());
      Node *newNode = createTwoNode(head_, newPair);
      head_->childs[0] = newNode;
    }
    else
    {
      auto resultPair = doFind(newPair.first);
      if (!resultPair.second)
      {
        Node *foundNode = resultPair.first.node_;
      }
    }
  }

  template < class Key, class T, class Compare >
  std::pair < typename TwoThree < Key, T, Compare >::iterator, bool > TwoThree < Key, T, Compare >::doFind(const Key &key)
  {
    Node *currNode = head_->childs[0];
    while (currNode)
    {
      Node *proposedNext = currNode->childs[2];
      if (Compare(currNode->values[0].first, key))
      {
        proposedNext = currNode->childs[0];
      }
      else if (!Compare(currNode->values[0].first, key))
      {
        return std::make_pair(iterator(currNode, true), true);
      }
      else if (currNode->type == detail::NodeType::Three)
      {
        if (Compare(currNode->values[1].first, key))
        {
          proposedNext = currNode->childs[1];
        }
        else if (!Compare(currNode->values[1].first, key))
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
    return new Node{ parent, { nullptr, nullptr, nullptr }, { pair, pair }, detail::NodeType::Two };
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::Node *TwoThree < Key, T, Compare >::createThreeNode(Node *parent, const MapPair &pair1, const MapPair &pair2) const
  {
    return new Node{ parent, { nullptr, nullptr, nullptr }, { pair1, pair2 }, detail::NodeType::Three };
  }

  template < class Key, class T, class Compare >
  void TwoThree < Key, T, Compare >::balanceAndInsert(iterator it, const MapPair &pair)
  {
    if (it.node_->type == detail::NodeType::Two)
    {
      it.node_->values[1] = pair;
      if (!Compare(it.node_->values[0].first, pair.first))
      {
        std::swap(it.node_->values[0], it.node_->values[1]);
      }
      it.node_->type = detail::NodeType::Three;
    }
    else if (it.node_->parent->type == detail::NodeType::Three)
    {
      Node *currNode = it.node_;
      Node *prevNode = createTwoNode(currNode, pair);
      while (currNode == detail::NodeType::Three)
      {
        if (Compare(prevNode->values[0].first, currNode->values[0].first))
        {
          Node *newRight = createTwoNode(currNode, currNode->values[1]);
          newRight->childs[0] = currNode->childs[1];
          newRight->childs[2] = currNode->childs[2];
        }
      }
    }
  }
}

#endif
