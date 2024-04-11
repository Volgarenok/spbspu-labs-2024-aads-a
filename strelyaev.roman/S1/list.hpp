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
      List();
      List(const List&);
      List(List< T >&&);
      List(size_t n, const T&);
      ~List();

      List< T >& operator=(const List< T >&);
      List< T >& operator=(List< T >&&);

      void assign(size_t n, const T& value);
      void swap(List< T >& other) noexcept;

      Iterator< T > insert(ConstIterator< T >, const T&);
      ConstIterator< T > erase(ConstIterator< T >);

      bool empty() noexcept;
      void push_back(const T&);
      void push_front(const T&);
      void pop_front();
      void pop_back();
      void clear() noexcept;
      void remove(const T& value);
      template< class Predicate >
      void remove_if(Predicate);

      size_t size() noexcept;
      T& back();
      T& front();
      const T& back() const;
      const T& front() const;
      Iterator< T > begin() noexcept;
      Iterator< T > end() noexcept;
      ConstIterator< T > cbegin() const noexcept;
      ConstIterator< T > cend() const noexcept;

    private:
      detail::Node< T >* imaginary_node;
      detail::Node< T >* head_;
      detail::Node< T >* tail_;
      size_t size_;
  };

  template< typename T >
  List< T >::List():
    imaginary_node(new detail::Node< T >(nullptr, nullptr, T())),
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template< typename T >
  List< T >::List(const List& other):
    List()
  {
    imaginary_node = new detail::Node< T >(tail_, nullptr, T());
    detail::Node< T >* node = other.head_;
    while (size_ != other.size_)
    {
      push_back(node->value_);
      node = node->next_;
    }
  }

  template< typename T >
  List< T >::List(List< T >&& other):
    imaginary_node(new detail::Node< T >(tail_, nullptr, T())),
    head_(other.head_),
    tail_(other.tail_),
    size_(other.size_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  template< typename T >
  List< T >::List(size_t n, const T& value):
    List()
  {
    assign(n, value);
  }

  template< typename T >
  List< T >::~List()
  {
    clear();
    delete imaginary_node;
  }

  template< typename T >
  List< T >& List< T >::operator=(const List< T >& other)
  {
    if (this != std::addressof(other))
    {
      swap(other);
    }
    return *this;
  }

  template< typename T >
  void List< T >::assign(size_t n, const T& value)
  {
    List< T > temp{};
    for (size_t i = 0; i < n; i++)
    {
      temp.push_front(value);
    }
    swap(temp);
  }

  template< typename T >
  void List< T >::swap(List< T >& other) noexcept
  {
    std::swap(other.imaginary_node, imaginary_node);
    std::swap(other.head_, head_);
    std::swap(other.tail_, tail_);
    std::swap(other.size_, size_);
  }

  template< typename T >
  Iterator< T > List< T >::insert(ConstIterator< T > it, const T& value)
  {
    if (size_ == 0)
    {
      detail::Node< T >* node = new detail::Node< T >{nullptr, imaginary_node, value};
      imaginary_node->prev_ = node;
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
  ConstIterator< T > List< T >::erase(ConstIterator< T > it)
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
      it.node_->prev_->next_ = it.node_->next_;
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
  void List< T >::pop_front()
  {
    erase(cbegin());
  }

  template< typename T >
  void List< T >::pop_back()
  {
    erase(--cend());
  }

  template< typename T >
  void List< T >::clear() noexcept
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template< typename T >
  void List< T >::remove(const T& value)
  {
    for (auto it = cbegin(); it != cend(); it++)
    {
      if (*it == value)
      {
        auto prev_it = it;
        prev_it--;
        erase(it);
        it = prev_it;
      }
    }
  }

  template< typename T >
  template< typename P >
  void List< T >::remove_if(P predicate)
  {
    for (auto it = cbegin(); it != cend(); it++)
    {
      if (predicate(*it))
      {
        auto temp_it = it;
        temp_it--;
        erase(it);
        it = temp_it;
      }
    }
  }

  template< typename T >
  size_t List< T >::size() noexcept
  {
    return size_;
  }

  template< typename T >
  T& List< T >::back()
  {
    return tail_->value_;
  }

  template< typename T >
  const T& List< T >::back() const
  {
    return tail_->value_;
  }

  template< typename T >
  T& List< T >::front()
  {
    return head_->value_;
  }

  template< typename T >
  const T& List< T >::front() const
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
    return Iterator< T >(imaginary_node);
  }

  template< typename T >
  ConstIterator< T > List< T >::cbegin() const noexcept
  {
    return ConstIterator< T >(head_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cend() const noexcept
  {
    return ConstIterator< T >(const_cast< detail::Node< T >* >(imaginary_node));
  }
}
#endif
