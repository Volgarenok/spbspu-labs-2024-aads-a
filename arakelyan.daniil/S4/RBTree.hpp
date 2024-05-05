#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <functional>
#include <ios>
#include <iostream>
#include <memory>
#include <initializer_list>
#include <utility>

#include "node.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"

namespace arakelyan
{
  template < class Key, class Value, class Comparator = std::less< Key > >
  struct RBTree
  {
  public:
    using iterator = Iterator< Key, Value, Comparator >;
    using const_iterator = ConstIterator< Key, Value, Comparator >;
    using value_t = std::pair< Key, Value >;

    RBTree();
    RBTree(const RBTree &otherT);//fine
    // RBTree(RBTree &&otherT);
    RBTree(std::initializer_list< value_t > otherT);//fine
    template < class Iterator_t >
    RBTree(Iterator_t it_start, Iterator_t it_end);//fine
    ~RBTree();//fine

    RBTree &operator=(const RBTree &otherT);//fine
    RBTree &operator=(RBTree &&otherT);//fine
    RBTree &operator=(std::initializer_list< value_t > otherT);//fine

    size_t getSize() const noexcept;
    bool empty() const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    void insert(const value_t &val); // fine?
    // void remove()

    void swap(RBTree &otherT) noexcept;

    void printInOrder() const noexcept;

  // private:
    using Node = detail::Node< Key, Value >;

    Node *root_;
    size_t size_;
    Comparator comp;

    void leftRotate(Node *nodeParent); //work
    void rightRotate(Node *nodeParent); //work
    //void leftRightRotate(Node *node);
    //void rightLeftRotate(Node *node);
    void balanceAfterInsert(Node *node); //parent black
    void balanceAfterInsertOne(Node *node); // parent black and root
    void balanceAfterInsertTwo(Node *node); // red parent and red uncle
    void balanceAfterInsertThree(Node *node); //red parent and black uncle. new node is external or new node is internal

    // void fixInput(Node *node)
    // {
    //   while (node->parent_->color_ == detail::color_t::RED)
    //   {
    //     if (node->getGrandparent()->left_ == node->parent_)
    //     {
    //       if (node->getUncle()->color_ == detail::color_t::RED)
    //       {
    //         node->parent_->color_ = detail::color_t::BLACK;
    //         node->getUncle()->color_ = detail::color_t::BLACK;
    //         node->getGrandparent()->color_ = detail::color_t::RED;
    //         node = node->getGrandparent();
    //       }
    //       else
    //       {
    //         if (node->parent_->right_ == node)
    //         {
    //           node = node->parent_;
    //           leftRotate(node->parent_);
    //         }
    //         node->parent_->color_ = detail::color_t::BLACK;
    //         node->getGrandparent()->color_ = detail::color_t::RED;
    //         rightRotate(node->parent_);
    //       }
    //     }
    //     else
    //     {
    //       if (node->getUncle()->color_ == detail::color_t::RED)
    //       {
    //         node->parent_->color_ = detail::color_t::BLACK;
    //         node->getUncle()->color_ = detail::color_t::BLACK;
    //         node->getGrandparent()->color_ = detail::color_t::RED;
    //         node = node->getGrandparent();
    //       }
    //       else
    //       {
    //         if (node->parent_->left_ == node)
    //         {
    //           node = node->parent_;
    //           rightRotate(node);
    //         }
    //         node->parent_->color_ = detail::color_t::BLACK;
    //         node->getGrandparent()->color_ = detail::color_t::RED;
    //         leftRotate(node->parent_);
    //       }
    //     }
    //   }
    //   // root_->color_ = detail::color_t::BLACK;
    // }

    void clear(Node *node);
    void traversal(Node *node) const noexcept;
    template < class Iterator_t >
    void copyFromRange(Iterator_t it_start, Iterator_t it_end);
  };

  template < class Key, class Value, class Comparator >
  RBTree< Key, Value, Comparator >::RBTree():
    root_(nullptr),
    size_(0)
  {}

  template < class Key, class Value, class Comparator >
  RBTree< Key, Value, Comparator >::RBTree(const RBTree< Key, Value, Comparator > &otherT):
    RBTree()
  {
    if (!otherT.empty())
    {
      copyFromRange(otherT.cbegin(), otherT.cend());
    }
  }

  template < class Key, class Value, class Comparator >
  RBTree< Key, Value, Comparator >::RBTree(std::initializer_list< std::pair< Key, Value > > otherT):
    RBTree(otherT.begin(), otherT.end())
  {}

  template < class Key, class Value, class Comparator >
  template < class Iterator_t >
  RBTree< Key, Value, Comparator >::RBTree(Iterator_t it_start, Iterator_t it_end):
    RBTree()
  {
    copyFromRange(it_start, it_end);
  }

  template < class Key, class Value, class Comparator >
  RBTree< Key, Value, Comparator >::~RBTree()
  {
    clear(root_);
  }

  template < class Key, class Value, class Comparator  >
  RBTree< Key, Value, Comparator > &RBTree< Key, Value, Comparator >::operator=(const RBTree< Key, Value, Comparator > &otherT)
  {
    RBTree temp(otherT);
    if (this != std::addressof(temp))
    {
      swap(temp);
    }
    return *this;
  }

  template < class Key, class Value, class Comparator  >
  RBTree< Key, Value, Comparator > &RBTree< Key, Value, Comparator >::operator=(RBTree< Key, Value, Comparator > &&otherT)
  {
    RBTree temp(std::move(otherT));
    if (this != std::addressof(temp))
    {
      clear(root_);
      swap(temp);
    }
    return *this;
  }

  template < class Key, class Value, class Comparator >
  RBTree< Key, Value, Comparator > &RBTree< Key, Value, Comparator >::operator=(std::initializer_list< std::pair< Key, Value > > otherT)
  {
    clear(root_);
    copyFromRange(otherT.begin(), otherT.end());
    return *this;
  }

  template < class Key, class Value, class Comparator >
  size_t RBTree< Key, Value, Comparator >::getSize() const noexcept
  {
    return size_;
  }

  template < class Key, class Value, class Comparator >
  bool RBTree< Key, Value, Comparator >::empty() const noexcept
  {
    return root_ == nullptr;
  }

  template < class Key, class Value, class Comparator  >
  Iterator< Key, Value, Comparator > RBTree< Key, Value, Comparator >::begin() noexcept
  {
    return Iterator< Key, Value, Comparator >(root_);
  }

  template < class Key, class Value, class Comparator  >
  Iterator< Key, Value, Comparator > RBTree< Key, Value, Comparator >::end() noexcept
  {
    return Iterator< Key, Value, Comparator >(nullptr);
  }

  template < class Key, class Value, class Comparator  >
  ConstIterator< Key, Value, Comparator > RBTree< Key, Value, Comparator >::cbegin() const noexcept
  {
    return ConstIterator< Key, Value, Comparator >(root_);
  }

  template < class Key, class Value, class Comparator  >
  ConstIterator< Key, Value, Comparator > RBTree< Key, Value, Comparator >::cend() const noexcept
  {
    return ConstIterator< Key, Value, Comparator >(nullptr);
  }

  template < class Key, class Value, class Comparator  >
  void RBTree< Key, Value, Comparator >::insert(const std::pair< Key, Value > &val)
  {
    Node *newNode = new Node(val);
    if (empty())
    {
      root_ = newNode;
    }
    else
    {
      Node *parent = nullptr;
      Node *currNode = root_;
      while (currNode)
      {
        parent = currNode;
        if (val.first < currNode->data_.first)
        {
          currNode = currNode->left_;
        }
        else if (val.first > currNode->data_.first)
        {
          currNode = currNode->right_;
        }
      }
      newNode->parent_ = parent;
      if (comp(parent->data_.first, newNode->data_.first))
      {
        parent->right_ = newNode;
      }
      else
      {
        parent->left_ = newNode;
      }
    }
    ++size_;
    balanceAfterInsert(newNode);
  }

  template < class Key, class Value, class Comparator >
  void RBTree< Key, Value, Comparator >::leftRotate(detail::Node< Key, Value > *nodeParent)
  {
    Node *grandP = nodeParent->parent_;
    nodeParent->parent_ = grandP->parent_;
    if (!grandP->parent_)
    {
      root_ = nodeParent;
    }
    else if (grandP->parent_)
    {
      if (grandP->parent_->left_ == grandP)
      {
        grandP->parent_->left_ = nodeParent;
      }
      else
      {
        grandP->parent_->right_ = nodeParent;
      }
    }
    grandP->right_ = nodeParent->left_;
    if (grandP->right_)
    {
      grandP->right_->parent_ = grandP;
    }
    grandP->parent_ = nodeParent;
    nodeParent->left_ = grandP;
  }

  template < class Key, class Value, class Comparator >
  void RBTree< Key, Value, Comparator >::rightRotate(detail::Node< Key, Value > *nodeParent)
  {
    Node *grandP = nodeParent->parent_;
    nodeParent->parent_ = grandP->parent_;
    if (!grandP->parent_)
    {
      root_ = nodeParent;
    }
    else if (grandP->parent_)
    {
      if (grandP->parent_->left_ == grandP)
      {
        grandP->parent_->left_ = nodeParent;
      }
      else
      {
        grandP->parent_->right_ = nodeParent;
      }
    }
    grandP->left_ = nodeParent->right_;
    if (grandP->left_)
    {
      grandP->left_->parent_ = grandP;
    }
    grandP->parent_ = nodeParent;
    nodeParent->right_ = grandP;
  }

  template < class Key, class Value, class Comparator >
  void RBTree< Key, Value, Comparator >::balanceAfterInsert(detail::Node< Key, Value > *node) // parent == root or parent red and go next 
  {
    std::cout << node->data_.first << " im in balance\n";
    if (node->parent_ == nullptr)
    {
      std::cout << node->data_.first << " node black\n";
      node->color_ = detail::color_t::BLACK;
    }
    else if (node->parent_->color_ == detail::color_t::RED)
    {
      balanceAfterInsertOne(node);
    }
    else if (node->parent_->color_ == detail::color_t::BLACK)
    {
      return;
    }
  }

  template < class Key, class Value, class Comparator >
  void RBTree< Key, Value, Comparator >::balanceAfterInsertOne(detail::Node< Key, Value > *node) //parent red
  {
    std::cout << node->data_.first << " balance when have uncle and parent red\n";
    if (node->parent_->color_ == detail::color_t::RED && node->getUncle())
    {
      balanceAfterInsertTwo(node);
    }
    else // fine
    {
      std::cout << node->data_.first << " parent black + grandParent + rotations\n";
      node->parent_->color_ = detail::color_t::BLACK;
      node->getGrandparent()->color_ = detail::color_t::RED;
      if (node->parent_->right_ == node)
      {
        leftRotate(node->parent_);
      }
      else
      {
        rightRotate(node->parent_);
      }
    }
  }

  template < class Key, class Value, class Comparator >
  void RBTree< Key, Value, Comparator >::balanceAfterInsertTwo(detail::Node< Key, Value > *node) // red parent and red uncle
  {
    std::cout << node->data_.first << " fix red parent and red uncle\n";
    Node *grandP = node->getGrandparent();
    if (grandP->parent_ == nullptr && node->getUncle()->color_ == detail::color_t::RED)
    {
      grandP->color_ = detail::color_t::RED;
      node->parent_->color_ = detail::color_t::BLACK;
      node->getUncle()->color_ = detail::color_t::BLACK;
      // leftRotate(node->parent_);
    }
    else if (grandP->parent_ && grandP->getUncle()->color_ == detail::color_t::RED)
    {
      balanceAfterInsertTwo(grandP);
    }
    else if (grandP->parent_ && grandP->getUncle()->color_ == detail::color_t::BLACK)
    {
      balanceAfterInsertThree(grandP);
    }
  }

  template < class Key, class Value, class Comparator >
  void RBTree< Key, Value, Comparator >::balanceAfterInsertThree(detail::Node< Key, Value > *node) //red parent and black uncle. new node is external
  {
    std::cout << node->data_.first << " red parent and black uncle in or ex\n";
    if (node->parent_->left_ == node && node->parent_->color_ == detail::color_t::RED)
    {
      node->parent_->color_ = detail::color_t::BLACK;
      rightRotate(node->parent_);
    }
    else if (node->parent_->right_ == node && node->parent_->color_ == detail::color_t::RED)
    {
      leftRotate(node->parent_);
      rightRotate(node);
    }
  }

  template < class Key, class Value, class Comparator  >
  void RBTree< Key, Value, Comparator >::swap(RBTree< Key, Value, Comparator > &otherT) noexcept
  {
    std::swap(root_, otherT.root_);
  }

  template < class Key, class Value, class Comparator  >
  void RBTree< Key, Value, Comparator >::printInOrder() const noexcept
  {
    traversal(root_);
  }

  template < class Key, class Value, class Comparator >
  void RBTree< Key, Value,Comparator >::clear(detail::Node< Key, Value > *node)
  {
    if (node)
    {
      clear(node->left_);
      clear(node->right_);
      delete node;
    }
  }

  template < class Key, class Value, class Comparator >
  void RBTree< Key, Value, Comparator >::traversal(detail::Node< Key, Value > *node) const noexcept
  {
    if (node)
    {
      traversal(node->left_);
      std::cout << node->data_.first << ":" << node->data_.second << " col:" << node->color_ << " -> ";
      traversal(node->right_);
    }
  }

  template < class Key, class Value, class Comparator >
  template < class Iterator_t >
  void RBTree< Key, Value, Comparator >::copyFromRange(Iterator_t it_start, Iterator_t it_end)
  {
    for (auto it = it_start; it != it_end; ++it)
    {
      insert(*it);
    }
  }
}
#endif
