#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "list.hpp"
#include "node.hpp"

namespace novokhatskiy
{
  template <typename T>
  class List;

  template <typename T>
  class Node;

  template <typename T>
  class Iterator : public std::iterator<std::forward_iterator_tag, T > 
  {
    friend class novokhatskiy::List<T>;
  public:
    Iterator() :
      node_(nullptr)
    {}
    Iterator(const Iterator<T>&) = default;
    Iterator<T>& operator=(const Iterator<T>&) = default;

    Iterator<T>& operator++() // Prefix increment operator.
    {
      node_ = node_->next_;
      return *this;
    };
    Iterator<T> operator++(int)    // Postfix increment operator.
    {
      Iterator<T> temp = (*this);
      //node_ = node_->next_;
      ++*this;
      return temp;
    };
    bool operator==(const Iterator<T>& other) const
    {
      return node_ == other.node_;
    }
    bool operator!=(const Iterator<T>& other) const
    {
      return !(node_ == other.node_);
    }
    T& operator*()
    {
      return node_->value_;
    }
    const T& operator*() const
    {
      return node_.value_;
    }
    T* operator->() 
    {
      return std::addressof(node_.value_);
    }
    const T* operator->() const
    {
      return std::addressof(node_.value_);
    }
    ~Iterator() = default;
  private:
    Iterator(Node<T>* other) :
      node_(other)
    {}
    Node<T>* node_;
  };
}
#endif
