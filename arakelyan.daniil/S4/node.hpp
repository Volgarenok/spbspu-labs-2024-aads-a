#ifndef NODE_HPP
#define NODE_HPP

#include <__config>
#include <utility>
namespace arakelyan
{
  namespace detail
  {
    enum color_t
    {
      RED = 0,
      BLACK = 1
    };

    template < class Key, class Value >
    struct Node
    {
      using value_t = std::pair< Key, Value >;

      value_t data_;
      color_t color_ = color_t::BLACK;
      Node *right_;
      Node *left_;
      Node *parent_;

      Node() = delete;
      explicit Node(const value_t &val);
      Node(const Key &key, const Value &value);
      Node *getGrandparent();
      Node *getUncle();
      Node *getBrother();
    };

    template < class Key, class Value >
    Node< Key, Value >::Node(const std::pair< Key, Value > &val):
      data_(val),
      color_(color_t::RED),
      right_(nullptr),
      left_(nullptr),
      parent_(nullptr)
    {}

    template < class Key, class Value >
    Node< Key, Value >::Node(const Key &key, const Value &value):
      color_(color_t::RED),
      right_(nullptr),
      left_(nullptr),
      parent_(nullptr)
    {
      data_.first = key;
      data_.second = value;
    }

    template < class Key, class Value >
    Node< Key, Value > *Node< Key, Value >::getGrandparent()
    {
      if (parent_ != nullptr && parent_->parent_ != nullptr)
      {
        return parent_->parent_;
      }
      else
      {
        return nullptr;
      }
    }

    template < class Key, class Value >
    Node< Key, Value > *Node< Key, Value >::getUncle()
    {
      Node *grandP = getGrandparent();
      if (!grandP)
      {
        return nullptr;
      }
      if (grandP->left_ == parent_)
      {
        return grandP->right_;
      }
      else
      {
        return grandP->left_;
      }
    }

    template < class Key, class Value >
    Node< Key, Value > *Node< Key, Value >::getBrother()
    {
      if (!parent_)
      {
        return nullptr;
      }
      if (parent_->right_ == this)
      {
        return parent_->left_;
      }
      else
      {
        return parent_->right_;
      }
    }
  }
}
#endif
