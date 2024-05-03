// ReSharper disable CppDFAUnreachableCode
#ifndef TWOTHREETREE_HPP
#define TWOTHREETREE_HPP

#include <functional>

#include "const_treeIterator.hpp"
#include "treeIterator.hpp"
#include "treeNode.hpp"

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
    iterator erase(iterator);
    iterator erase(const_iterator);
    char erase(const Key &);
    void clear() noexcept;
    void swap(TwoThree &) noexcept;

    iterator find(const Key &);
    const_iterator find(const Key &) const;

  private:
    Compare compare_;
    using Node = detail::TreeNode < MapPair >;
    Node *head_;
    size_t size_;

    std::pair < iterator, bool > doFind(const Key &) const;
    Node *createTwoNode(const MapPair &) const;
    Node *createThreeNode(const MapPair &, const MapPair &) const;
    void connectNodes(Node *parent, Node *left, Node *right, Node *mid = nullptr);

    std::pair < iterator, bool > balanceFromBros(iterator);
    std::pair < iterator, bool > balanceFromParents(iterator);
  };

  template < class Key, class T, class Compare >
  TwoThree < Key, T, Compare >::TwoThree():
    head_(createTwoNode(MapPair())),
    size_(0)
  {
    connectNodes(head_, nullptr, head_);
  }

  template < class Key, class T, class Compare >
  TwoThree < Key, T, Compare >::TwoThree(const TwoThree &other):
    TwoThree()
  {
    auto it = other.cbegin();
    auto endIt = other.cend();
    while (it != endIt)
    {
      insert({ it->first, it->second });
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
    return it->second;
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
    return (insert(std::make_pair(key, T()))).first->second;
  }

  template < class Key, class T, class Compare >
  T &TwoThree < Key, T, Compare >::operator[](Key &&key)
  {
    return *((insert(std::make_pair(std::move(key), T()))).first);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::iterator TwoThree < Key, T, Compare >::begin()
  {
    return iterator(iterator::findMin(head_->right), true);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::const_iterator TwoThree < Key, T, Compare >::begin() const
  {
    return const_iterator(const_iterator::findMin(head_->right), true);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::const_iterator TwoThree < Key, T, Compare >::cbegin() const noexcept
  {
    return const_iterator(const_iterator::findMin(head_->right), true);
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
    auto resultPair = doFind(newPair.first);
    if (!resultPair.second)
    {
      Node *prevLeft = nullptr;
      Node *prevRight = nullptr;
      MapPair currPair = newPair;
      Node *currNode = resultPair.first.node_;
      while (currNode->type == detail::NodeType::Three)
      {
        if (compare_(currNode->one.first, currPair.first))
        {
          Node *newRight = createTwoNode(currNode->two);
          connectNodes(newRight, currNode->mid, currNode->right);
          connectNodes(currNode, prevLeft, prevRight);
          std::swap(currPair, currNode->one);
          prevRight = newRight;
          prevLeft = currNode;
        }
        else if (compare_(currPair.first, currNode->two.first))
        {
          Node *newRight = createTwoNode(currNode->two);
          connectNodes(newRight, prevRight, currNode->right);
          connectNodes(currNode, currNode->left, prevLeft);
          prevRight = newRight;
          prevLeft = currNode;
        }
        else
        {
          Node *newLeft = createTwoNode(currNode->one);
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
        Node *newNode = createTwoNode(currPair);
        connectNodes(head_, nullptr, newNode);
        connectNodes(newNode, prevLeft, prevRight);
      }
      else if (compare_(currNode->one.first, newPair.first))
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
      return std::make_pair(doFind(newPair.first).first, true);
    }
    return std::make_pair(resultPair.first, false);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::iterator TwoThree < Key, T, Compare >::erase(iterator it)
  {
    if (size_ == 1)
    {
      delete head_->left;
      delete head_;
      head_ = nullptr;
      size--;
      return end();
    }
    if (it.node_->left)
    {
      Node *nodeFrom = nullptr;
      if (it.node_->type == detail::NodeType::Three && !it.isPtrToLeft_)
      {
        nodeFrom = it.node_->mid;
      }
      else
      {
        nodeFrom = it.node_->left;
      }
      iterator toSwapIt(iterator::findMax(nodeFrom), false);
      std::swap(*it, *toSwapIt);
      it = toSwapIt;
    }
    iterator itToReturn = it;
    size_--;
    if (it.node_->type == detail::NodeType::Three)
    {
      if (!it.isPtrToLeft_)
      {
        std::swap(it.node_->one, it.node->two);
      }
      it.node_->type = detail::NodeType::Two;
    }
    else
    {
      auto isBalancedFroBrosPair = balanceFromBros(it);
      if (isBalancedFroBrosPair.second)
      {
        itToReturn = isBalancedFroBrosPair.first;
      }
      else
      {
        itToReturn = balanceFromParents(it).first;
      }
    }
    return itToReturn;
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::iterator TwoThree < Key, T, Compare >::erase(const_iterator it)
  {
    return erase(iterator(it.node_, it.isPtrToLeft_));
  }

  template < class Key, class T, class Compare >
  char TwoThree < Key, T, Compare >::erase(const Key &key)
  {
    return erase(find(key));
  }

  template < class Key, class T, class Compare >
  void TwoThree < Key, T, Compare >::clear() noexcept
  {
    Node *currNode = iterator::findMin(head_);
    while (currNode != head_)
    {
      Node *nextNode = nullptr;
      Node *parentNode = currNode->parent;
      if (parentNode->left == currNode)
      {
        nextNode = parentNode->mid ? parentNode->mid : parentNode->right;
        nextNode = iterator::findMin(nextNode);
      }
      else if (parentNode->mid == currNode)
      {
        nextNode = iterator::findMin(parentNode->right);
      }
      else
      {
        nextNode = parentNode;
      }
      delete currNode;
      currNode = nextNode;
    }
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
      return resultPair.first;
    }
    return end();
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
  std::pair < typename TwoThree < Key, T, Compare >::iterator, bool > TwoThree < Key, T, Compare >::doFind(const Key &key) const
  {
    if (empty())
    {
      return std::make_pair(iterator(head_, true), false);
    }
    Node *currNode = head_->right;
    while (currNode->left)
    {
      Node *proposedNext = currNode->right;
      if (compare_(key, currNode->one.first))
      {
        proposedNext = currNode->left;
      }
      else if (!compare_(currNode->one.first, key))
      {
        return std::make_pair(iterator(currNode, true), true);
      }
      else if (currNode->type == detail::NodeType::Three)
      {
        if (compare_(key, currNode->two.first))
        {
          proposedNext = currNode->mid;
        }
        else if (!compare_(currNode->two.first, key))
        {
          return std::make_pair(iterator(currNode, false), true);
        }
      }
      currNode = proposedNext;
    }
    return std::make_pair(iterator(currNode, true), false);
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::Node *TwoThree < Key, T, Compare >::createTwoNode(const MapPair &pair) const
  {
    return new Node{ nullptr, nullptr, nullptr, nullptr, pair, pair, detail::NodeType::Two };
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::Node *TwoThree < Key, T, Compare >::createThreeNode(const MapPair &pair1, const MapPair &pair2) const
  {
    return new Node{ nullptr, nullptr, nullptr, nullptr, pair1, pair2, detail::NodeType::Three };
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
    }
    if (right)
    {
      right->parent = parent;
    }
    if (mid)
    {
      mid->parent = parent;
    }
  }

  template < class Key, class T, class Compare >
  std::pair < typename TwoThree < Key, T, Compare >::iterator, bool > TwoThree < Key, T, Compare >::balanceFromBros(iterator emptyIt)
  {
    Node *parentNode = emptyIt.node_->parent;
    bool balanced = true;
    auto lastRemovedIt = emptyIt;
    lastRemovedIt++;
    MapPair lastRemovedPair = *lastRemovedIt;
    if (parentNode->mid && parentNode->mid == emptyIt.node_)
    {
      if (parentNode->left->type == detail::NodeType::Three)
      {
        std::swap(parentNode->one, emptyIt.node_->one);
        std::swap(parentNode->one, parentNode->left->two);
        if (emptyIt.node_->left)
        {
          connectNodes(emptyIt, parentNode->left->right, emptyIt->left);
          connectNodes(parentNode->left, parentNode->left->left, parentNode->left->mid);
        }
        else if (emptyIt.node_->right)
        {
          connectNodes(emptyIt, parentNode->left->right, emptyIt->right);
          connectNodes(parentNode->left, parentNode->left->left, parentNode->left->mid);
        }
        parentNode->left->type = detail::NodeType::Two;
      }
      else if (parentNode->right->type == detail::NodeType::Three)
      {
        std::swap(parentNode->two, emptyIt.node_->one);
        std::swap(parentNode->two, parentNode->right->one);
        std::swap(parentNode->right->one, parentNode->right->two);
        if (emptyIt.node_->left)
        {
          connectNodes(emptyIt, emptyIt->left, parentNode->right->left);
          connectNodes(parentNode->right, parentNode->left, parentNode->mid);
        }
        else if (emptyIt.node_->right)
        {
          connectNodes(emptyIt, parentNode->left->right, emptyIt->right);
          connectNodes(parentNode->right, parentNode->right->mid, parentNode->right->right);
        }
        parentNode->right->type = detail::NodeType::Two;
      }
      else
      {
        balanced = false;
      }
    }
    else if (parentNode->right == emptyIt.node_)
    {
      if (parentNode->mid)
      {
        if (parentNode->mid->type == detail::NodeType::Three)
        {
          std::swap(parentNode->two, parentNode->right->one);
          std::swap(parentNode->two, parentNode->mid->two);
          if (emptyIt.node_->left)
          {
            connectNodes(emptyIt, parentNode->mid->right, emptyIt->left);
            connectNodes(parentNode->mid, parentNode->mid->left, parentNode->mid->mid);
          }
          else if (emptyIt.node_->right)
          {
            connectNodes(emptyIt, parentNode->mid->right, emptyIt->right);
            connectNodes(parentNode->mid, parentNode->mid->left, parentNode->mid->mid);
          }
          parentNode->mid->type = detail::NodeType::Two;
        }
        else if (parentNode->left->type == detail::NodeType::Three)
        {
          std::swap(parentNode->two, parentNode->right->one);
          std::swap(parentNode->two, parentNode->mid->one);
          std::swap(parentNode->one, parentNode->mid->one);
          std::swap(parentNode->one, parentNode->left->two);
          if (emptyIt.node_->left)
          {
            connectNodes(emptyIt, parentNode->mid->right, emptyIt->left);
            connectNodes(parentNode->mid, parentNode->left->right, parentNode->mid->left);
            connectNodes(parentNode->left, parentNode->left->left, parentNode->left->mid);
          }
          else if (emptyIt.node_->right)
          {
            connectNodes(emptyIt, parentNode->mid->right, emptyIt->right);
            connectNodes(parentNode->mid, parentNode->left->right, parentNode->mid->left);
            connectNodes(parentNode->left, parentNode->left->left, parentNode->left->mid);
          }
          parentNode->left->type = detail::NodeType::Two;
        }
        else
        {
          balanced = false;
        }
      }
      else if (parentNode->left->type == detail::NodeType::Three)
      {
        std::swap(parentNode->one, parentNode->right->one);
        std::swap(parentNode->one, parentNode->left->two);
        if (emptyIt.node_->left)
        {
          connectNodes(emptyIt, parentNode->left->right, emptyIt->left);
          connectNodes(parentNode->left, parentNode->left->left, parentNode->left->mid);
        }
        else if (emptyIt.node_->right)
        {
          connectNodes(emptyIt, parentNode->left->right, emptyIt->right);
          connectNodes(parentNode->left, parentNode->left->left, parentNode->left->mid);
        }
        parentNode->left->type = detail::NodeType::Two;
      }
      else
      {
        balanced = false;
      }
    }
    else if (parentNode->left == emptyIt.node_)
    {
      if (parentNode->mid)
      {
        if (parentNode->mid->type == detail::NodeType::Three)
        {
          std::swap(parentNode->one, parentNode->left->one);
          std::swap(parentNode->one, parentNode->mid->one);
          std::swap(parentNode->mid->two, parentNode->mid->one);
          if (emptyIt.node_->left)
          {
            connectNodes(emptyIt, emptyIt->left, parentNode->mid->left);
            connectNodes(parentNode->mid, parentNode->mid->mid, parentNode->mid->right);
          }
          else if (emptyIt.node_->right)
          {
            connectNodes(emptyIt, emptyIt->right, parentNode->mid->left);
            connectNodes(parentNode->mid, parentNode->mid->mid, parentNode->mid->right);
          }
          parentNode->mid->type = detail::NodeType::Two;
        }
        else if (parentNode->right->type == detail::NodeType::Three)
        {
          std::swap(parentNode->one, parentNode->left->one);
          std::swap(parentNode->one, parentNode->mid->one);
          std::swap(parentNode->two, parentNode->mid->one);
          std::swap(parentNode->two, parentNode->right->one);
          std::swap(parentNode->right->two, parentNode->right->one);
          if (emptyIt.node_->left)
          {
            connectNodes(emptyIt, emptyIt->left, parentNode->mid->left);
            connectNodes(parentNode->mid, parentNode->mid->right, parentNode->right->left);
            connectNodes(parentNode->right, parentNode->right->mid, parentNode->right->right);
          }
          else if (emptyIt.node_->right)
          {
            connectNodes(emptyIt, emptyIt->right, parentNode->mid->left);
            connectNodes(parentNode->mid, parentNode->mid->right, parentNode->right->left);
            connectNodes(parentNode->right, parentNode->right->mid, parentNode->right->right);
          }
          parentNode->left->type = detail::NodeType::Two;
        }
        else
        {
          balanced = false;
        }
      }
      else if (parentNode->right->type == detail::NodeType::Three)
      {
        std::swap(parentNode->one, parentNode->left->one);
        std::swap(parentNode->one, parentNode->right->one);
        std::swap(parentNode->right->two, parentNode->right->one);
        if (emptyIt.node_->left)
        {
          connectNodes(emptyIt, emptyIt->left, parentNode->right->left);
          connectNodes(parentNode->right, parentNode->right->mid, parentNode->right->right);
        }
        else if (emptyIt.node_->right)
        {
          cconnectNodes(emptyIt, emptyIt->right, parentNode->right->left);
          connectNodes(parentNode->right, parentNode->right->mid, parentNode->right->right);
        }
        parentNode->left->type = detail::NodeType::Two;
      }
      else
      {
        balanced = false;
      }
    }
    if (balanced)
    {
      return std::make_pair(doFind(lastRemovedPair.first).first, balanced);
    }
    return std::make_pair(iterator(emptyIt, balanced));
  }

  template < class Key, class T, class Compare >
  std::pair < typename TwoThree < Key, T, Compare >::iterator, bool > TwoThree < Key, T, Compare >::balanceFromParents(iterator emptyIt)
  {
    Node *parentNode = emptyIt.node_->parent;
    Node *emptyNode = emptyIt.node_;
    auto lastRemovedIt = emptyIt;
    lastRemovedIt++;
    MapPair lastRemovedPair = *lastRemovedIt;
    if (emptyNode->parent->type == detail::NodeType::Three)
    {
      if (parentNode->left == emptyNode)
      {
        std::swap(parentNode->one, parentNode->mid->two);
        std::swap(parentNode->mid->one, parentNode->mid->two);
        std::swap(parentNode->one, parentNode->two);
        connectNodes(parentNode, parentNode->mid, parentNode->right);
        parentNode->mid->type = detail::NodeType::Three;
        delete emptyNode;
      }
      else if (parentNode->mid == emptyNode)
      {
        std::swap(parentNode->one, parentNode->left->two);
        std::swap(parentNode->one, parentNode->two);
        parentNode->left->type = detail::NodeType::Three;
        delete emptyNode;
      }
      else
      {
        std::swap(parentNode->two, parentNode->mid->two);
        parentNode->mid->type = detail::NodeType::Three;
        connectNodes(parentNode, parentNode->left, parentNode->mid);
        delete emptyNode;
      }
      parentNode->type = detail::NodeType::Two;
    }
    else
    {
      while (parentNode != head_)
      {
        auto isBalancedFromBrosPair = balanceFromBros(iterator(emptyNode, true));
        if (isBalancedFromBrosPair.second)
        {
          return std::make_pair(doFind(lastRemovedPair.first).first, true);
        }
        if (parentNode->type == detail::NodeType::Three)
        {
          if (parentNode->left == emptyNode)
          {
            std::swap(parentNode->one, emptyNode->one);
            std::swap(parentNode->mid->one, emptyNode->two);
            std::swap(parentNode->one, parentNode->two);
            if (emptyNode->left)
            {
              connectNodes(emptyNode, emptyNode->left, parentNode->mid->right, parentNode->mid->left);
            }
            else
            {
              connectNodes(emptyNode, emptyNode->right, parentNode->mid->right, parentNode->mid->left);
            }
            connectNodes(parentNode, emptyNode, parentNode->right);
            delete parentNode->mid;
            parentNode->type = detail::NodeType::Two;
            emptyNode->type = detail::NodeType::Three;
          }
          else if (parentNode->mid == emptyNode)
          {
            std::swap(parentNode->one, emptyNode->two);
            std::swap(parentNode->left->one, emptyNode->one);
            std::swap(parentNode->one, parentNode->two);
            if (emptyNode->left)
            {
              connectNodes(emptyNode, parentNode->left->left, emptyNode->left, parentNode->left->right);
            }
            else
            {
              connectNodes(emptyNode, parentNode->left->left, emptyNode->right, parentNode->left->right);
            }
            delete parentNode->left;
            connectNodes(parentNode, emptyNode, parentNode->right);
            parentNode->type = detail::NodeType::Two;
            emptyNode->type = detail::NodeType::Three;
          }
          else
          {
            std::swap(parentNode->two, emptyNode->two);
            std::swap(parentNode->mid->one, emptyNode->one);
            if (emptyNode->left)
            {
              connectNodes(emptyNode, parentNode->mid->left, emptyNode->left, parentNode->mid->right);
            }
            else
            {
              connectNodes(emptyNode, parentNode->mid->left, emptyNode->right, parentNode->mid->right);
            }
            delete parentNode->mid;
            connectNodes(parentNode, parentNode->left, emptyNode);
            parentNode->type = detail::NodeType::Two;
            emptyNode->type = detail::NodeType::Three;
          }
          return std::make_pair(doFind(lastRemovedPair.first).first, true);
        }
        if (parentNode->left == emptyNode)
        {
          std::swap(parentNode->one, parentNode->right->two);
          std::swap(parentNode->right->one, parentNode->right->two);
          if (emptyNode->left)
          {
            connectNodes(parentNode->right, emptyNode->left, parentNode->right->right, parentNode->right->left);
          }
          else if (emptyNode->right)
          {
            connectNodes(parentNode->right, emptyNode->right, parentNode->right->right, parentNode->right->left);
          }
          parentNode->right->type = detail::NodeType::Three;
          delete emptyNode;
          parentNode->left = nullptr;
          emptyNode = parentNode;
          parentNode = parentNode->parent;
        }
        else
        {
          std::swap(parentNode->one, parentNode->left->two);
          if (emptyNode->left)
          {
            connectNodes(parentNode->left, parentNode->left->left, emptyNode->left, parentNode->left->right);
          }
          else if (emptyNode->right)
          {
            connectNodes(parentNode->left, parentNode->left->left, emptyNode->right, parentNode->left->right);
          }
          parentNode->left->type = detail::NodeType::Three;
          delete emptyNode;
          parentNode->left = nullptr;
          emptyNode = parentNode;
          parentNode = parentNode->parent;
        }
      }
      Node *toConnect = emptyNode->left ? emptyNode->left : emptyNode->right;
      connectNodes(head_, nullptr, toConnect);
      return std::make_pair(doFind(lastRemovedPair.first).first, true);
    }
  }
}

#endif
