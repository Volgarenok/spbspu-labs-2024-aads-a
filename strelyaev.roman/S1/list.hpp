#ifndef LIST_HPP
#define LIST_HPP
#include <initializer_list>
#include "node.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"

namespace strelyaev
{
  template< typename T >
  class List
  {
    public:
      List(); //!
      //List(const List&);
      //List(List< T >&&) noexcept;
      //List(size_t n, const T&);
      //~List();

      //List< T >& operator=(const List< T >&) noexcept;
      //List< T >& operator=(List< T >&&) noexcept;

      //void assign(size_t n, const T& value);
      //void swap(List& other) noexcept;

      Iterator< T > insert(ConstIterator< T >, const T&); //!
      ConstIterator< T > erase(Iterator< T >); //!

      bool empty() noexcept; //!
      void push_back(const T&);
      void push_front(const T&); //!
      //void pop_front() noexcept;
      //void pop_back() noexcept;
      //void clear() noexcept;
      //void remove(const T& value);
      //template< class Predicate >
      //void remove_if (Predicate) noexcept;

      size_t size() noexcept; //!
      T& back() const; //!
      T& front() const; //!
      Iterator< T > begin() noexcept; //!
      Iterator< T > end() noexcept; //!
      ConstIterator< T > cbegin() const noexcept; //!
      ConstIterator< T > cend() const noexcept; //!

    private:
      detail::Node< T > imaginary_node;
      detail::Node< T >* head_;
      detail::Node< T >* tail_;
      size_t size_;
  };

  template< typename T >
  List< T >::List():
    imaginary_node(nullptr, nullptr, T()),
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template< typename T >
  Iterator< T > List< T >::insert(ConstIterator< T > it, const T& value)
  {
    if (size_ == 0)
    {
      detail::Node< T >* node = new detail::Node< T >{nullptr, std::addressof(imaginary_node), value};
      imaginary_node.prev_ = node;
      head_ = node;
      tail_ = node;
      size_++;
      return Iterator< T >(head_);
    }
    detail::Node< T >* node = new detail::Node< T >{it.node_->prev_, it.node_, value};
    it.node_->prev_ = node;
    if (it.node_ == head_)
    {
      head_ = node;
    }
    if (it.node_ == tail_->next_)
    {
      tail_ = node;
      node->prev_->next_ = node;
    }
    else
    {
      node->prev_->next_ = node;
    }
    size_++;
    return Iterator< T >(node);
  }

  template< typename T >
  ConstIterator< T > List< T >::erase(Iterator< T > it)
  {
    ConstIterator< T > result(it.node_->next_);
    it.node_->next_->prev_ = it.node_->prev_;
    if (it.node_ == head_)
    {
      head_ = head_->next_;
    }
    else if (it.node_ == tail_)
    {
      tail_ = tail_->prev_;
    }
    else
    {
      it.node->prev_->next_ = it.node_->next_;
    }
    delete it.node_;
    size_--;
    return result;
  }

  template< typename T >
  bool List< T >::empty() noexcept
  {
    return size_ == 0;
  }

  template< typename T >
  void List< T >::push_back(const T& value)
  {
    if (!tail_)
    {
      push_front(value);
    }
    else
    {
      insert(cend(), value);
    }
  }

  template< typename T >
  void List< T >::push_front(const T& value)
  {
    insert(cbegin(), value);
  }


  template< typename T >
  size_t List< T >::size() noexcept
  {
    return size_;
  }

  template< typename T >
  T& List< T >::back() const
  {
    return tail_->value_;
  }

  template< typename T >
  T& List< T >::front() const
  {
    return head_->value_;
  }

  template< typename T >
  Iterator< T > List< T >::begin() noexcept
  {
    return Iterator< T >(head_);
  }

  template< typename T >
  Iterator< T > List< T >::end() noexcept
  {
    return Iterator< T >(std::addressof(imaginary_node));
  }

  template< typename T >
  ConstIterator< T > List< T >::cbegin() const noexcept
  {
    return ConstIterator< T >(head_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cend() const noexcept
  {
    return ConstIterator< T >(const_cast< detail::Node< T >* >(std::addressof(imaginary_node)));
  }
}
#endif