#ifndef BIDIRECTIONAL_LIST_HPP
#define BIDIRECTIONAL_LIST_HPP
#include <utility>
#include <cstddef>
#include <bidirectional_iterator.hpp>
#include <const_bidirectional_iterator.hpp>
#include <bidirectional_node.hpp>

namespace namestnikov
{
  template< class T >
  class List
  {
  public:
    using base_node_t = detail::BaseListNode;
    using node_t = detail::ListNode< T >;
    using iterator = ListIterator< T >;
    using const_iterator = ConstListIterator< T >;

    List():
      size_(0),
      fakeNode_(new base_node_t())
    {}
    List(size_t count, const T & value):
      size_(count),
      fakeNode_(new base_node_t())
    {
      try
      {
        for (size_t i = 0; i < count; ++i)
        {
          push_back(value);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    List(const List& other):
      size_(0)
    {
      try
      {
        fakeNode_ = new base_node_t();
        for (auto it = other.cbegin(); it != other.cend(); ++it)
        {
          pushBack(*it);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    List & operator=(const List & other)
    {
      if (this != std::addressof(other))
      {
        List< T > temp(other);
        swap(temp);
      }
      return *this;
    }
    List(List && other) noexcept:
      size_(other.size_),
      fakeNode_(other.fakeNode_)
    {
      other.size_ = 0;
      other.fakeNode_ = nullptr;
    }
    List & operator=(List && other) noexcept
    {
      if (this != std::addressof(other))
      {
        List< T > temp(std::move(other));
        swap(temp);
      }
      return *this;
    }
    bool empty() const noexcept
    {
      return size_ == 0;
    }
    size_t size() const noexcept
    {
      return size_;
    }
    iterator begin() const
    {
      if (!size_)
      {
        return iterator(fakeNode_);
      }
      return iterator(fakeNode_->next);
    }
    const_iterator cbegin() const
    {
      if (!size_)
      {
        return const_iterator(fakeNode_);
      }
      return const_iterator(fakeNode_->next);
    }
    iterator end() const
    {
      return iterator(fakeNode_);
    }
    const_iterator cend() const
    {
      return const_iterator(fakeNode_);
    }
    T & front()
    {
      if (size_ == 0)
      {
        throw std::invalid_argument("There aren't any elements in list");
      }
      return *begin();
    }
    const T & front() const
    {
      if (size_ == 0)
      {
        throw std::invalid_argument("There aren't any elements in list");
      }
      return *begin();
    }
    T & back()
    {
      if (size_ == 0)
      {
        throw std::invalid_argument("There aren't any elements in list");
      }
      return *std::prev(end());
    }
    const T & back() const
    {
      if (size_ == 0)
      {
        throw std::invalid_argument("There aren't any elements in list");
      }
      return *std::prev(end());
    }
    void push_front(const T & value)
    {
      try
      {
        insert(begin(), value);
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    void push_back(const T & value)
    {
      try
      {
        insert(end(), value);
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    void pop_front()
    {
      try
      {
        erase(begin());
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    void pop_back()
    {
      try
      {
        erase(std::prev(end()));
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    iterator insert(iterator pos, const T & value)
    {
      try
      {
        node_t * newNode = new node_t(value);
        base_node_t* currentNode = pos.node_;
        newNode->next = currentNode;
        if (size_)
        {
          currentNode->prev->next = newNode;
          newNode->prev = currentNode->prev;
        }
        else
        {
          newNode->prev = currentNode;
          currentNode->next = newNode;
        }
        currentNode->prev = newNode;
        ++size_;
        return iterator(newNode);
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    iterator erase(iterator pos)
    {
      if (size_ == 0)
      {
        throw std::invalid_argument("There aren't any elements in list");
      }
      try
      {
        base_node_t * node = pos.node_;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        ++pos;
        delete node;
        --size_;
        return pos;
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    void clear()
    {
      if (!size_)
      {
        return;
      }
      base_node_t * cur = fakeNode_->next;
      while (cur != fakeNode_)
      {
        cur = cur->next;
        delete cur->prev;
      }
      size_ = 0;
      delete fakeNode_;
    }
    void swap(List & other) noexcept
    {
      std::swap(size_, other.size_);
      std::swap(fakeNode_, other.fakeNode_);
    }
    ~List()
    {
      clear();
    }
  private:
    size_t size_;
    base_node_t * fakeNode_;
  };
}

#endif
