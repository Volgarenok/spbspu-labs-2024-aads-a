#ifndef LIST_HPP
#define LIST_HPP

#include "iterator.hpp"
#include "constiterator.hpp"
//help

namespace vojuck
{
  template< typename T >
  class List
  {
  public:
    using iterator = IteratorList< T >;
    using constiterator = ConstIteratorList< T >;

    List():
      head_(nullptr),
      size_(0)
    {}
    List(const List< T > & other):
      List()
    {
      detail::Node< T >* current = other.head_;
      while (current)
      {
        push_back(current->data_);
        current = current->next;
      }
      size_ = other.size_;
    }
    List(List && other) noexcept :
      head_(other.head_),
      size_(other.size_)
    {
      other->clear();
    }
    ~List()
    {
      clear();
    }

    List & operator=(const List< T > & other)
    {
      assert(this != &other);
      detail::Node< T >* current = other.head_;
      while (current)
      {
        push_back(current->data);
        current = current->next;
      }
      size_ = other.size_;
      return *this;
    }
    List & operator=(List && other) noexcept
    {
      assert(this != &other);
      head_ = other.head_;
      size_ = other.size_;
      other->clear();
    }

    iterator begin() noexcept;
    iterator end() noexcept;
    constiterator cbegin() const noexcept;
    constiterator cend() const noexcept;

    bool empty() const noexcept;
    void clear() noexcept;

    void push_back(const T&);
    void push_front(const T&);
    void pop_back();
    void pop_front();
    void swap(List< T >&) noexcept;

  private:
    size_t size_;
    Node< T >* head_;
  };
}


#endif
