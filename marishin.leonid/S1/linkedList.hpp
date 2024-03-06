#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <sstream>

namespace marishin
{
  template < typename T >
  class Node
  {
  public:
    T data_;
    Node* prev_;
    Node* next_;

    Node(const T& value):
      data_(value),
      prev_(nullptr),
      next_(nullptr)
    {}
    ~Node() {}
  };

  template < typename T >
  class LinkedList
  {
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  public:
    LinkedList():
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}
    ~LinkedList()
    {
      clear();
    }

    LinkedList& operator=(const LinkedList& other)
    {
      if (this == &other)
      {
        return *this;
      }
      clear();
      Node< T >* curr = other.head_;
      while (curr)
      {
        push_back(curr -> data_);
        curr = curr -> next_;
      }
      return *this;
    }

    class Iterator
    {
    private:
      Node< T >* ptr_;

    public:
      Iterator(Node< T >* node):
        ptr_(node)
      {}

      Iterator& operator++()
      {
        ptr_ = ptr_ -> next_;
        return *this;
      }

      bool operator!=(const Iterator& other) const
      {
        return ptr_ != other.ptr_;
      }

      T& operator*() const
      {
        return ptr_ -> data_;
      }

      };

    class ConstIterator
    {
    private:
      Node< T >* ptr_;

    public:
      ConstIterator(Node< T >* node):
        ptr_(node)
      {}

      ConstIterator& operator++()
      {
        ptr_ = ptr_ -> next_;
        return *this;
      }

      bool operator!=(const ConstIterator& other) const
      {
        return ptr_ != other.ptr_;
      }

      const T& operator*() const
      {
        return ptr_ -> data_;
      }
    };

    Iterator begin() const
    {
      return Iterator(head_);
    }

    Iterator end() const
    {
      return Iterator(nullptr);
    }

    ConstIterator cbegin() const
    {
      return ConstIterator(head_);
    }

    ConstIterator cend() const
    {
      return ConstIterator(nullptr);
    }

    bool empty() const
    {
      return size_ == 0;
    }

    T& front() const
    {
      return head_ -> data_;
    }

    T& back() const
    {
      return tail_ -> data_;
    }

    void assign(size_t count, const T& value)
    {
      clear();
      for (size_t i = 0; i < count; ++i)
      {
        push_back(value);
      }
    }

    void emplace_front(const T& value)
    {
      Node< T >* newNode = new Node< T >(value);
      if (empty())
      {
        head_ = tail_ = newNode;
      }
      else
      {
        newNode -> next_ = head_;
        head_ -> prev_ = newNode;
        head_ = newNode;
      }
      ++size_;
    }

    void push_front(const T& value)
    {
      emplace_front(value);
    }

    void pop_front()
    {
      if (empty())
      {
        return;
      }
      Node< T >* temp = head_;
      head_ = head_ -> next_;
      if (head_)
      {
        head_ -> prev_ = nullptr;
      }
      delete temp;
      --size_;
      if (size_ == 0)
      {
        tail_ = nullptr;
      }
    }

    void emplace_back(const T& value)
    {
      Node< T >* newNode = new Node< T >(value);
      if (empty())
      {
        head_ = tail_ = newNode;
      }
      else
      {
        tail_ -> next_ = newNode;
        newNode -> prev_ = tail_;
        tail_ = newNode;
      }
      ++size_;
    }

    void push_back(const T& value)
    {
      emplace_back(value);
    }

    void pop_back()
    {
      if (empty())
      {
        return;
      }
      Node< T >* temp = tail_;
      tail_ = tail_ -> prev_;
      if (tail_)
      {
        tail_ -> next_ = nullptr;
      }
      delete temp;
      --size_;
      if (size_ == 0)
      {
        head_ = nullptr;
      }
    }

    void emplace(const Iterator& pos, const T& value)
    {
      if (pos.ptr_ == nullptr)
      {
        emplace_back(value);
        return;
      }

      Node< T >* newNode = new Node< T >(value);
      newNode -> next_ = pos.ptr_;
      newNode -> prev_ = pos.ptr_ -> prev_;
      if (pos.ptr_ -> prev_)
      {
        pos.ptr_ -> prev_ -> next_ = newNode;
      }
      else
      {
        head_ = newNode;
      }
      pos.ptr_ -> prev_ = newNode;
      ++size_;
    }

    void insert(const Iterator& pos, size_t count, const T& value)
    {
      for (size_t i = 0; i < count; ++i)
      {
        emplace(pos, value);
      }
    }

    Iterator erase(const Iterator& pos)
    {
      if (pos.ptr_ == nullptr)
      {
        return end();
      }

      Node< T >* toDelete = pos.ptr_;
      Iterator nextIter(toDelete -> next_);
      if (toDelete -> prev_)
      {
        toDelete -> prev_ -> next_ = toDelete -> next_;
      }
      else
      {
        head_ = toDelete -> next_;
      }
      if (toDelete -> next_)
      {
        toDelete -> next_ -> prev_ = toDelete -> prev_;
      }
      else
      {
        tail_ = toDelete -> prev_;
      }
      delete toDelete;
      --size_;
      return nextIter;
    }

    void swap(LinkedList& other)
    {
      std::swap(head_, other.head_);
      std::swap(tail_, other.tail_);
      std::swap(size_, other.size_);
    }

    void clear()
    {
      while (!empty())
      {
        pop_back();
      }
    }

    void splice(const Iterator& pos, LinkedList& other)
    {
      if (other.empty())
      {
        return;
      }

      if (pos.ptr_ == nullptr)
      {
        tail_ -> next_ = other.head_;
        other.head_ -> prev_ = tail_;
        tail_ = other.tail_;
      }
      else
      {
        Node< T >* posNode = pos.ptr_;
        Node< T >* beforePos = posNode -> prev_;

        if (beforePos)
        {
          beforePos -> next_ = other.head_;
        }
        other.head_ -> prev_ = beforePos;

        posNode -> prev_ = other.tail_;
        other.tail_ -> next_ = posNode;

        if (pos.ptr_ == head_)
        {
          head_ = other.head_;
        }
      }

      size_ += other.size_;
      other.head_ = other.tail_ = nullptr;
      other.size_ = 0;
    }

    void remove(const T& value)
    {
      Node< T >* curr = head_;
      while (curr)
      {
        if (curr -> data_ == value)
        {
          Node< T >* toDelete = curr;
          curr = curr -> next_;
          erase(Iterator(toDelete));
        }
        else
        {
          curr = curr -> next_;
        }
      }
    }

    template < typename Predicate >
    void remove_if(Predicate pred)
    {
      Node< T >* curr = head_;
      while (curr)
      {
        if (pred(curr -> data_))
        {
          Node< T >* toDelete = curr;
          curr = curr -> next_;
          erase(Iterator(toDelete));
        }
        else
        {
          curr = curr -> next_;
        }
      }
    }

    void unique()
    {
      Node< T >* curr = head_;
      while (curr && curr -> next_)
      {
        if (curr -> data_ == curr -> next_ -> data_)
        {
          Node< T >* toDelete = curr -> next_;
          curr -> next_ = curr -> next_ -> next_;
          if (curr -> next_)
          {
            curr -> next_ -> prev_ = curr;
          }
          delete toDelete;
          --size_;
        }
        else
        {
          curr = curr -> next_;
        }
      }
    }

    void merge(LinkedList& other)
    {
      if (this == &other)
      {
        return;
      }

      Node< T >* thisCurr = head_;
      Node< T >* otherCurr = other.head_;

      while (thisCurr && otherCurr)
      {
        if (thisCurr -> data_ > otherCurr -> data_)
        {
          Node< T >* temp = otherCurr;
          otherCurr = otherCurr -> next_;
          temp -> next_ = thisCurr;
          temp -> prev_ = thisCurr -> prev_;
          if (thisCurr -> prev_)
          {
            thisCurr -> prev_ -> next_ = temp;
          }
          thisCurr -> prev_ = temp;
          if (thisCurr == head_)
          {
             head_ = temp;
          }
          ++size_;
        }
        else
        {
          thisCurr = thisCurr -> next_;
        }
      }

      if (otherCurr)
      {
        if (!head_)
        {
          head_ = other.head_;
        }
        if (tail_)
        {
          tail_ -> next_ = other.head_;
        }
        other.head_ -> prev_ = tail_;
        tail_ = other.tail_;
        size_ += other.size_;
      }

      other.head_ = other.tail_ = nullptr;
      other.size_ = 0;
    }

    void sort()
    {
      if (size_ < 2)
      {
        return;
      }

      bool swapped = true;
      while (swapped)
      {
        swapped = false;
        Node< T >* curr = head_;
        while (curr -> next_)
        {
          if (curr -> data_ > curr -> next_ -> data_)
          {
            std::swap(curr -> data_, curr -> next_ -> data_);
            swapped = true;
          }
          curr = curr -> next_;
        }
      }
    }

    void reverse()
    {
      Node<T>* curr = head_;
      while (curr)
      {
        std::swap(curr->prev_, curr->next_);
        curr = curr->prev_;
        if (curr && curr->prev_ == nullptr)
        {
          head_ = curr;
        }
      }
      std::swap(head_, tail_);
    }
  };
}

#endif
