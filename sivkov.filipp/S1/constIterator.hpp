#include <iostream>
#include "node.hpp"

template <typename T>
class ConstIterator
{
public:
  ConstIterator() :
    node_(nullptr)
  {}
  ConstIterator(Node<T>* node) :
    node_(node)
  {}

  ConstIterator<T>& operator=(const ConstIterator<T>&) = default;
  ConstIterator(const ConstIterator<T>&) = default;
  ~ConstIterator() = default;

  T& operator*();
  T* operator->();

  bool operator!=(const ConstIterator<T>& other) const;
  bool operator==(const ConstIterator<T>& other) const;
  const T& operator*() const;
  const T* operator->() const;
  ConstIterator<T>& operator++();
  ConstIterator<T> operator++(int);

private:
  Node<T>* node_;
};

template<typename T>
T& ConstIterator<T>::operator*()
{
  return node_->data;
}

template<typename T>
T* ConstIterator<T>::operator->()
{
  return std::addressof(node_->data);
}

template<typename T>
bool ConstIterator<T>::operator!=(const ConstIterator<T>& other) const
{
  return !(node_ == other.node_);
}

template<typename T>
bool ConstIterator<T>::operator==(const ConstIterator<T>& other) const
{
  return (node_ == other.node_);
}

template<typename T>
const T& ConstIterator<T>::operator*() const
{
  return node_->data;
}

template<typename T>
const T* ConstIterator<T>::operator->() const
{
  return std::addressof(node_->data);
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator++()
{
  node_ = node_->next;
  return *this;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator++(int)
{
  ConstIterator<T> result(*this);
  ++(*this);
  return result;
}
