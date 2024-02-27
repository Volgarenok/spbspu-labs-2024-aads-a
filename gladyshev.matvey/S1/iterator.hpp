#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "node.hpp"

template <typename T>
class Iterator
{
public:
  Iterator():
    node_(nullptr)
  {}
  Iterator(Node<T>* node):
    node_(node)
  {}
  Iterator(const Iterator<T>&) = default;
  Iterator<T>& operator=(const Iterator<T>&) = default;
  Iterator(Iterator&& other) noexcept:
    node_(other.node_)
  {
    other.node_ = nullptr;
  }
  ~Iterator() = default;
  Iterator<T>& operator++()
  {
    node_ = node_->next;
    return *this;
  }
  Iterator<T> operator++(int)
  {
    Iterator<T> result(*this);
    ++(*this);
    return result;
  }
  bool operator!=(const Iterator<T>& other) const
  {
    return !(node_ == other.node_);
  }
  bool operator==(const Iterator<T>& other) const
  {
    return (node_ == other.node_);
  }
  T& operator*()
  {
    return node_->data;
  }
  T* operator->()
  {
    return std::addressof(node_->data);
  }
private:
  Node<T>* node_;
};

#endif
