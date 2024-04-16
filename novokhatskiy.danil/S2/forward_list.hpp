#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include <iostream>
#include "const_forward_list_iterators.hpp"
#include "forward_list_iterators.hpp"
#include "node.hpp"

namespace novokhatskiy
{
  template < typename T >
  class ForwardIterator;

  template < typename T >
  class Node;

  template < typename T >
  class ConstForwardIterator;

  template < typename T >
  class ForwardList
  {
    friend class novokhatskiy::ForwardIterator< T >;
    friend class novokhatskiy::ConstForwardIterator< T >;
  public:
    using iter = ForwardIterator< T >;
    using constIter = ConstForwardIterator< T >;
    ForwardList():
      head_(nullptr)
    {}
    ForwardList(const T& value):
      head_(new Node< T >)
    {
      for (auto i = begin(); i < end(); i++)
      {
        push_front(value);
      }
    }
    ForwardList(ForwardList&& other) noexcept:
      head_(other.head_)
    {
      other.head_ = nullptr;
    }
    ForwardList(const ForwardList< T >& other):
      head_(nullptr)
    {
      auto iter_begin = other.begin();
      auto iter_end = other.end();
      while (iter_begin != iter_end)
      {
        try
        {
          push_front(*(iter_begin++));
        }
        catch (const std::bad_alloc&)
        {
          clear();
          throw;
        }
      }
    }
    ForwardList(size_t size, const T& value):
      head_(nullptr)
    {
      try
      {
        for (size_t i = 0; i != size; i++)
        {
          push_front(value);
        }
      }
      catch (const std::bad_alloc&)
      {
        clear();
        throw;
      }
    }
    ForwardList(std::initializer_list< T > list):
      head_(nullptr)
    {
      auto begin = list.begin();
      auto end = list.end();
      while (begin != end)
      {
        try
        {
          push_front(*(begin++));
        }
        catch (const std::bad_alloc&)
        {
          clear();
          throw;
        }
      }
    }

    ForwardList< T >& operator=(const ForwardList< T >& other)
    {
      ForwardList< T > tmp(other);
      if (std::addressof(other) != this)
      {
        swap(tmp);
      }
      return *this;
    }

    ForwardList< T >& operator=(ForwardList < T >&& other)
    {
      ForwardList< T > tmp(std::move(other));
      if (std::addressof(other) != this)
      {
        swap(tmp);
      }
      return *this;
    }

    iter begin()
    {
      return iter(head_);
    }

    iter begin() const
    {
      return iter(head_);
    }

    constIter cbegin() const
    {
      return constIter(head_);
    }

    iter end()
    {
      return iter();
    }

    iter end() const
    {
      return iter();
    }

    constIter cend() const
    {
      return constIter();
    }

    bool empty() const
    {
      return (head_ == nullptr);
    }
    const T& front() const
    {
      return head_->value_;
    }
    T& front()
    {
      return head_->value_;
    }

    iter insert_after(constIter pos, const T& value)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert");
      }
      auto goToPos = this->begin();
      while (pos.operator!=(goToPos))
      {
        goToPos++;
      }
      Node< T >* node = new Node< T >(value);
      node->next_ = goToPos.node_->next_;
      goToPos.node_->next_ = node;
      return goToPos++;
    }

    iter insert_after(constIter pos, size_t count, const T& value)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert");
      }
      auto goToPos = this->begin();
      while (pos.operator!=(goToPos))
      {
        goToPos++;
      }
      for (size_t i = 0; i < count; i++)
      {
        Node< T >* node = new Node< T >(value);
        node->next_ = goToPos.node_->next_;
        goToPos.node_->next_ = node;
      }
      return goToPos++;
    }

    iter insert_after(constIter pos, std::initializer_list< T > list)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert");
      }
      auto goToPos = this->begin();
      while (pos.operator!=(goToPos))
      {
        goToPos++;
      }
      for (T value : list)
      {
        Node< T >* node = new Node< T >(value);
        node->next_ = goToPos.node_->next_;
        goToPos.node_->next_ = node;
      }
      return goToPos++;
    }

    iter erase_after(constIter pos)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert");
      }
      auto goToPos = this->begin();
      while (pos.operator!=(goToPos))
      {
        goToPos++;
      }
      if (goToPos.node_->next_)
      {
        ForwardIterator< T > next(goToPos.node_->next_->next_);
        delete goToPos.node_->next_;
        goToPos.node_->next_ = next.node_;
        return next;
      }
      else
      {
        return end();
      }
    }

    iter erase_after(constIter first, constIter last)
    {
      if (first == cend())
      {
        throw std::out_of_range("Can not insert");
      }
      auto goToPos = begin();
      while (goToPos.operator!=(first))
      {
        goToPos++;
      }
      while (goToPos != last)
      {
        if (goToPos.node_->next_)
        {
          ForwardIterator< T > next(goToPos.node_->next_->next_);
          delete goToPos.node_->next_;
          goToPos.node_->next_ = next.node_;
          return next;
        }
        else
        {
          return end();
        }
      }
      return goToPos++;
    }

    void splice_after(constIter& pos, ForwardList< T >& other)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert");
      }
      Node< T >* next = pos.node_->next_;
      pos.node_->next_ = other.head_;
      while (other.head_)
      {
        other.head_ = other.head_->next_;
        pos.node_ = pos.node_->next_;
        pos.node_->next_ = other.head_;
      }
      pos.node_->next_ = next;
      other.head_ = nullptr;
    }

    void push_front(const T& value)
    {
      Node< T >* ptr = new Node< T >(value);
      ptr->next_ = head_;
      head_ = ptr;
    }
    void push_front(T& value)
    {
      Node< T >* ptr = new Node< T >(value);
      ptr->next_ = head_;
      head_ = ptr;
    }
    void pop_front()
    {
      if (empty())
      {
        std::cerr << "The forward_list is empty\n";
        return;
      }
      Node< T >* temp = head_;
      head_ = head_->next_;
      delete temp;
    }
    size_t max_size() const
    {
      size_t count{};
      if (head_ == nullptr)
      {
        return 0;
      }
      Node< T >* curr = head_;
      while (curr)
      {
        count++;
        curr = curr->next_;
      }
      return count;
    }
    void clear()
    {
      while (!empty())
      {
        pop_front();
      }
    }
    void assign(size_t count, const T& value)
    {
      Node< T >* otherHead = nullptr;
      try
      {
        for (size_t i = 0; i < count; i++)
        {
          Node< T >* temp = new Node< T >(value);
          temp->next_ = otherHead;
          otherHead = temp;
        }
      }
      catch (const std::bad_alloc&)
      {
        while (head_)
        {
          Node< T >* temp = head_->next_;
          delete head_;
          head_ = temp;
        }
      }
      head_ = otherHead;
    }

    void assign(std::initializer_list< T > list)
    {
      try
      {
        clear();
        for (T data : list)
        {
          push_front(data);
        }
        reverse();
      }
      catch (const std::bad_alloc&)
      {
        clear();
        throw;
      }
    }

    void assign(iter first, iter last)
    {
      clear();
      while (first != last)
      {
        push_front(*first++);
      }
      reverse();
    }

    void swap(ForwardList< T >& other)
    {
      std::swap(head_, other.head_);
    }
    void reverse()
    {
      if (!head_)
      {
        return;
      }
      Node< T >* result = head_;
      Node< T >* temp = head_->next_;
      result->next_ = nullptr;
      while (temp)
      {
        Node< T >* prev = temp->next_;
        temp->next_ = result;
        result = temp;
        temp = prev;
      }
      head_ = result;
    }
    void remove(const T& value)
    {
      Node< T >* curr = head_;
      Node< T >* firstStep = head_;
      while (curr != nullptr)
      {
        if (curr->value_ == value)
        {
          head_ = curr->next_;
          delete curr;
          curr = head_;
        }
        else
        {
          curr = curr->next_;
          head_ = curr;
        }
      }
      head_ = firstStep;
    }
    template< typename P >
    size_t remove_if(P predicate)
    {
      size_t removedElement{};
      Node< T >* curr = head_;
      Node< T >* prev = nullptr;
      while (curr)
      {
        if (predicate(curr->value_))
        {
          if (head_ == curr)
          {
            prev->next_ = curr->next_;
            delete curr;
          }
          else
          {
            head_ = curr->next_;
          }
          Node< T >* temp = curr;
          curr = curr->next_;
          ++removedElement;
          delete temp;
        }
        else
        {
          prev = curr;
          curr = curr->next_;
        }
      }
      return removedElement;
    }

    bool operator==(ForwardList< T >& other) const
    {
      size_t maxPossibleSize = std::min(this->max_size(), other.max_size());
      Node< T >* curr = head_;
      Node< T >* otherHead = other.head_;
      for (size_t i = 0; i < maxPossibleSize; i++)
      {
        if (curr->value_ != otherHead->value_)
        {
          return false;
        }
        curr = curr->next_;
        otherHead = otherHead->next_;
      }
      return true;
    }
    bool operator!=(ForwardList< T >& other) const
    {
      return !(*this == other);
    }
    bool operator<(const ForwardList< T >& other) const
    {
      size_t maxPossibleSize = std::min(this->max_size(), other.max_size());
      Node< T >* curr = head_;
      Node< T >* otherHead = other.head_;
      for (size_t i = 0; i < maxPossibleSize; i++)
      {
        if (curr->value_ != otherHead->value_)
        {
          return curr->value_ < otherHead->value_;
        }
        curr = curr->next_;
        otherHead = otherHead->next_;
      }
      return false;
    }

    bool operator>(const ForwardList< T >& other) const
    {
      return (other < *this);
    }
    bool operator<=(const ForwardList< T >& other) const
    {
      return (*this < other || *this == other);
    }
    bool operator>=(const ForwardList< T >& other) const
    {
      return (other < *this || *this == other);
    }
    void print()
    {
      while (head_ != nullptr) {
        std::cout << head_->value_ << " ";
        head_ = head_->next_;
      }
      std::cout << std::endl;
    }

    void push_back(const T& value)
    {
      Node< T >* new_node = new Node< T >{ value, nullptr };
      if (head_ == nullptr)
      {
        head_ = new_node;
      }
      else
      {
        Node< T >* curr = head_;
        while (curr->next_ != nullptr)
        {
          curr = curr->next_;
        }
        curr->next_ = new_node;
      }
    }
    
    ~ForwardList()
    {
      clear();
    }
  private:
    Node< T >* head_;
  };
}

#endif
