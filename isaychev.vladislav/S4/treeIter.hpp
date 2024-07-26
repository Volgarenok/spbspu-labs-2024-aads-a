#ifndef CONSTITER_HPP
#define CONSTITER_HPP

#include <iterator>
#include "treeNode.hpp"

namespace isaychev
{
  template < class Key, class Value, class Compare >
  class BSTree;

  template < class Key, class Value >
  class ConstTreeIter: public std::iterator< bidirectional_iterator_tag, Key, Value >
  {
    using this_t = ConstTreeIter< Key, Value >;
    using node_t = detail::TreeNode< Key, Value >;
   public:
    ConstTreeIter();

    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);

    bool operator==(const this_t & rhs);
    bool operator!=(const this_t & rhs);

    const  & operator*() const; //неверно
    const T * operator->() const; //неверно

   private:
    node_t * current_;
    node_t * previous_;

    template < class Key, class Value, class Compare >
    friend class BSTree< Key, Value, Compare >;

    //node_t * traverse_left(node_t * ptr);
    explicit ConstIterTree(node_t * node);
  };

  template < class Key, class Value >
  ConstTreeIter< Key, Value >::ConstTreeIter():
   current_(nullptr),
   previous_(nullptr)
  {}

  template < class Key, class Value >
  ConstTreeIter< Key, Value >::ConstIterTree(node_t * node):
   current_(node),
   previous_(nullptr)
  {}

  template < class Key, class Value >
  detail::TreeNode< Key, Value > * ConstTreeIter< Key, Value >::traverse_left(node_t * root)
  {
    if (root)
    {
      while (root->left)
      {
        root = root->left;
      }
    }
    return root;
  }

  template < class Key, class Value >
  void ConstTreeIter< Key, Value >::go_RL()
  {
    previous_ = current_;
    current_= traverse_left(current_->right);
  }

  template < class Key, class Value >
  void ConstTreeIter< Key, Value >::go_up()
  {
    previous_ = current_;
    current_ = current_->parent;
  }

  template < class Key, class Value >
  ConstTreeIter< Key, Value > & ConstTreeIter< Key, Value >::operator++()
  {
//    do_increment();
    if (!current_->left && !current_->right && current_ == current_->parent->left)
    {
      go_up();
    }
    else if (previous_ == current_->left && current_->right)
    {
      go_RL();
    }
    else if (!current_->left && current_->right)
    {
      go_RL();
    }
    else if (current_ == current_->parent->right)
    {
      while (current_ == current_->parent->right)
      {
        go_up();
      }
      if (parent)
      {
        go_up();
      }
      else
      {
        current_ = nullptr;
      }
    }
    return *this;
  }

  template < class Key, class Value >
  ConstTreeIter< Key, Value > ConstTreeIter< Key, Value >::operator++(int)
  {
    auto iter = *this;
//    do_increment();
    if (!current_->left && !current_->right && current_ == current_->parent->left)
    {
      go_up();
    }
    else if (previous_ == current_->left && current_->right)
    {
      go_RL();
    }
    else if (!current_->left && current_->right)
    {
      go_RL();
    }
    else if (current_ == current_->parent->right)
    {
      while (current_ == current_->parent->right)
      {
        go_up();
      }
      if (parent)
      {
        go_up();
      }
      else
      {
        current_ = nullptr;
      }
    }
    return iter;
  }

  template < class Key, class Value >
  ConstTreeIter< Key, Value > & ConstTreeIter< Key, Value >::operator--()
  {
    return *this;
  }

  template < class Key, class Value >
  ConstTreeIter< Key, Value > ConstTreeIter< Key, Value >::operator--(int)
  {
    return *this;
  }

  template < class Key, class Value >
  bool ConstTreeIter< Key, Value >::operator==(const this_t & rhs)
  {
    return current_ == rhs.current_;
  }

  template < class Key, class Value >
  bool ConstTreeIter< Key, Value >::operator!=(const this_t & rhs)
  {
    return current_ != rhs.current_;
  }

  template < class Key, class Value >
  const T & ConstTreeIter< Key, Value >::operator*() const
  {
    return current_->data;
  }

  template < class Key, class Value >
  const T * ConstTreeIter< Key, Value >::operator->() const
  {
    return std::addresof(current_->data);
  }
}

#endif
