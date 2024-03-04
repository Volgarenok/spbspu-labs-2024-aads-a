#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "node.hpp"
#include <memory>

namespace zakozhurnikova
{
  template <typename T>
  struct Iterator
  {
    using this_t = Iterator<T>;
    Iterator();
    Iterator(Node< T >* node);
    Iterator(const this_t&) = default;
    ~Iterator() = default;

    this_t& operator=(const this_t&) = default;
    this_t& operator++();
    this_t operator++(int);
    this_t& operator--();
    this_t operator--(int);
    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;
    T& operator*();
    T* operator->();
    T& operator*() const;
    T* operator->() const;

    this_t operator+(size_t);
    this_t operator-(size_t);

  private:
    Node< T >* node_;
  };

  template <typename T>
  Iterator<T> Iterator<T>::operator+(size_t k)
  {
    Iterator<T> result(*this);
    for (size_t i = 0; i < k; ++i)
    {
      ++result;
    }
    return result;
  }

  template <typename T>
  Iterator<T> Iterator<T>::operator-(size_t k)
  {
    Iterator<T> result(*this);
    for (size_t i = 0; i < k; ++i)
    {
      --result;
    }
    return result;
  }

  template <typename T>
  Iterator<T>::Iterator() :
    node_(nullptr)
  {}

  template <typename T>
  Iterator<T>::Iterator(Node< T >* node) :
    node_(node)
  {}

  template <typename T>
  Iterator<T>& Iterator<T>::operator++()
  {
    node_ = node_->next;
    return *this;
  }

  template <typename T>
  Iterator<T> Iterator<T>::operator++(int rhs)
  {
    Iterator<T> result(*this);
    ++(*this);
    return result;
  }

  template <typename T>
  Iterator<T>& Iterator<T>::operator--()
  {
    node_ = node_->prev;
    return *this;
  }


  template <typename T>
  Iterator<T> Iterator<T>::operator--(int rhs)
  {
    Iterator<T> result(*this);
    --(*this);
    return result;
  }

  template <typename T>
  bool Iterator<T>::operator==(const Iterator<T>& rhs) const
  {
    return node_ == rhs.node_;
  }

  template <typename T>
  bool Iterator<T>::operator!=(const Iterator<T>& rhs) const
  {
    return !(*this == rhs);
  }

  template <typename T>
  T& Iterator<T>::operator*()
  {
    return node_->data;
  }

  template <typename T>
  T& Iterator<T>::operator*() const
  {
    return node_->data;
  }

  template <typename T>
  T* Iterator<T>::operator->()
  {
    return std::addressof(node_->data);
  }

  template <typename T>
  T* Iterator<T>::operator->() const
  {
    return std::addressof(node_->data);
  }
}

#endif
