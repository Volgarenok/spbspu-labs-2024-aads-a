#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include <iostream>
#include "forward_list_iterators.hpp"
#include "node.hpp"

namespace novokhatskiy
{
  template <typename T >
  class ForwardIterator;

  template <typename T >
  class Node;

  template <typename T >
  class ForwardList
  {
    friend class novokhatskiy::ForwardIterator<T>;
  public:
    using iter = ForwardIterator<T>;
    ForwardList():
      head_(nullptr)
    {}
    ForwardList(const T& value) :
      head_(new Node< T >)
    {
      for (auto i = begin(); i < end(); i++)
      {
        push_front(value);
      }
    }
    ForwardList(ForwardList&& other) noexcept :
      head_(other.head_)
    {
      other.head_ = nullptr;
    }
    ForwardList(const ForwardList<T>& other):
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
    ForwardList(size_t size, const T& value) :
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
    ForwardList(std::initializer_list< T > list) :
      head_(nullptr)
    {
      auto begin = list.begin();
      auto end = list.end();
      while (begin != end)
      {
        try
        {
          push_front(*(begin++)); //--end(), use to change the order
        }
        catch (const std::bad_alloc&)
        {
          clear();
          throw;
        }
      }
    }
    iter begin() //const
    {
      return iter(head_);
    }
    iter begin() const
    {
      return iter(head_);
    }
    iter end()
    {
      return iter();
    }
    iter end() const
    {
      return iter();
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
    void push_front(const T& value)
    {
      Node<T>* ptr = new Node<T>(value);
      ptr->next_ = head_;
      head_ = ptr;
    }
    void push_front(T& value)
    {
      Node<T>* ptr = new Node<T>(value);
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
      Node<T>* temp = head_;
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
          Node< T >* temp = new Node<T>(value);
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
    void swap(ForwardList<T>& other)
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
        Node< T >* rofl = temp->next_;
        temp->next_ = result;
        result = temp;
        temp = rofl;
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

    void print()
    {
      while (head_ != nullptr) {
        std::cout << head_->value_ << " ";
        head_ = head_->next_;
      }
      std::cout << std::endl;
    }
    ~ForwardList()
    {
      clear();
    }
  private:
    Node<T>* head_;
  };
}

#endif
