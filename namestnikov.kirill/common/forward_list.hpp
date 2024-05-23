#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <node.hpp>
#include <iterators.hpp>
#include <const_iterators.hpp>

namespace namestnikov
{
  template < class T >
  class ForwardIterator;

  template < class T >
  class ConstForwardIterator;

  template < class T >
  class ForwardList
  {
    friend class ForwardIterator< T >;
    friend class ConstForwardIterator< T >;
    using iterator = ForwardIterator< T >;
    using const_iterator = ConstForwardIterator< T >;
    using node_t = detail::Node< T >;
  public:
    ForwardList():
      head_(nullptr)
    {}
    ForwardList(size_t count, const T & value):
      head_(nullptr)
    {
      try
      {
        for (size_t i = 0; i < count; ++i)
        {
          push_front(value);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    ForwardList(const ForwardList< T > & other):
      head_(nullptr)
    {
      try
      {
        iterator begin = other.begin();
        iterator end = other.end();
        for (; begin != end; ++begin)
        {
          push_front(begin.node_->data_);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    ForwardList(std::initializer_list< T > list):
      head_(nullptr)
    {
      auto rbegin = list.end() - 1;
      auto rend = list.begin() - 1;
      while (rbegin != rend)
      {
        try
        {
          push_front(*rbegin);
          --rbegin;
        }
        catch (...)
        {
          clear();
          throw;
        }
      }
    }
    ForwardList<T> & operator=(const ForwardList< T > & other)
    {
      ForwardList<T> temp(other);
      if (std::addressof(other) != this)
      {
        swap(temp);
      }
      return *this;
    }
    ForwardList(ForwardList< T > && other) noexcept:
      head_(other.head_)
    {
      other.head_ = nullptr;
    }
    ForwardList<T> & operator=(ForwardList< T > && other)
    {
      ForwardList<T> temp(std::move(other));
      if (std::addressof(other) != this)
      {
        swap(temp);
      }
      return *this;
    }
    void clear()
    {
      while (!empty())
      {
        pop_front();
      }
    }
    bool empty() const noexcept
    {
      return head_ == nullptr;
    }
    void reverse()
    {
      if (head_)
      {
        node_t * newHead = head_;
        node_t * tail = head_->next_;
        newHead->next_ = nullptr;
        while (tail)
        {
          node_t * temp = tail->next_;
          tail->next_ = newHead;
          newHead = tail;
          tail = temp;
        }
        head_ = newHead;
      }
    }
    void push_front(const T & data)
    {
      node_t * newHead = new node_t(data);
      newHead->next_ = head_;
      head_ = newHead;
    }
    void push_front(T && data)
    {
      push_front(data);
    }
    void push_back(const T & value)
    {
      if (!head_)
      {
        push_front(value);
      }
      else
      {
        node_t * new_node = new node_t(value);
        node_t * curr = head_;
        while (curr->next_ != nullptr)
        {
          curr = curr->next_;
        }
        curr->next_ = new_node;
      }
    }
    void push_back(T && data)
    {
      push_back(data);
    }
    T & front()
    {
      return head_->data_;
    }
    const T & front() const
    {
      return head_->data_;
    }
    void swap(ForwardList< T > & other) noexcept
    {
      std::swap(head_, other.head_);
    }
    size_t get_size()
    {
      size_t size = 0;
      node_t * temp = head_;
      while (head_)
      {
        ++size;
        head_ = head_->next_;
      }
      head_ = temp;
      return size;
    }
    void pop_front()
    {
      if (empty())
      {
        throw std::runtime_error("ForwardList is empty");
      }
      node_t * oldHead = head_;
      head_ = head_->next_;
      delete oldHead;
    }
    void remove(const T & value)
    {
      auto pred = [=](const T & number)
      {
        return number == value;
      };
      remove_if(pred);
    }
    template < class Predicate >
    void remove_if(Predicate p)
    {
      node_t * prev = nullptr;
      node_t * temp = head_;
      while (temp)
      {
        if (p(temp->data_))
        {
          node_t * todel = temp;
          if (prev)
          {
            prev->next_ = temp->next_;
          }
          else
          {
            head_ = temp->next_;
          }
          temp = temp->next_;
          delete todel;
        }
        else
        {
          prev = temp;
          temp = temp->next_;
        }
      }
    }
    void assign(size_t count, const T & value)
    {
      ForwardList< T > temp(count, value);
      assign(temp.begin(), temp.end());
      temp.clear();
    }
    void assign(std::initializer_list< T > list)
    {
      ForwardList< T > temp(list);
      assign(temp.begin(), temp.end());
      temp.clear();
    }
    void assign(iterator begin, iterator end)
    {
      try
      {
        ForwardList< T > temp;
        for (; begin != end; ++begin)
        {
          temp.push_front(*begin);
        }
        clear();
        temp.reverse();
        push_front(temp.front());
        temp.pop_front();
        splice_after(cbegin(), temp);
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    iterator insert_after(const_iterator pos, const T & value)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert here");
      }
      else
      {
        auto position = begin();
        while (position != pos)
        {
          ++position;
        }
        node_t * node = new node_t(value);
        node->next_ = position.node_->next_;
        position.node_->next_ = node;
        ++position;
        return position;
      }
    }
    iterator insert_after(const_iterator pos, T && value)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert here");
      }
      else
      {
        auto position = begin();
        while (position != pos)
        {
          ++position;
        }
        node_t * node = new node_t(value);
        node->next_ = position.node_->next_;
        position.node_->next_ = node;
        ++position;
        return position;
      }
    }
    iterator insert_after(const_iterator pos, size_t count, const T & value)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert here");
      }
      else
      {
        auto position = begin();
        while (position != pos)
        {
          ++position;
        }
        if (count == 0)
        {
          return position;
        }
        try
        {
          for (size_t i = 0; i < count; ++i)
          {
            node_t * node = new node_t(value);
            node->next_ = position.node_->next_;
            position.node_->next_ = node;
            ++position;
          }
        }
        catch (...)
        {
          clear();
          throw;
        }
        return position;
      }
    }
    iterator insert_after(const_iterator pos, std::initializer_list< T > list)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert here");
      }
      else
      {
        auto position = begin();
        while (position != pos)
        {
          ++position;
        }
        auto begin = list.begin();
        auto end = list.end();
        try
        {
          for (; begin != end; ++begin)
          {
            node_t * node = new node_t(*begin);
            node->next_ = position.node_->next_;
            position.node_->next_ = node;
            ++position;
          }
        }
        catch (...)
        {
          clear();
          throw;
        }
        return position;
      }
    }
    iterator erase_after(const_iterator pos)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not erase from here");
      }
      else
      {
        auto position = begin();
        while (pos != position)
        {
          ++position;
        }
        if (position.node_->next_)
        {
          iterator temp = position.node_->next_->next_;
          auto todel = position.node_->next_;
          delete todel;
          position.node_->next_ = temp.node_;
          return temp;
        }
        else
        {
          return end();
        }
      }
    }
    iterator erase_after(const_iterator first, const_iterator last)
    {
      if (first == cend())
      {
        throw std::out_of_range("Can not erase from here");
      }
      else
      {
        auto position = begin();
        while (position != first)
        {
          ++position;
        }
        iterator res = position;
        for (; position != last; ++position)
        {
          if (position.node_->next_)
          {
            iterator temp = position.node_->next_->next_;
            auto todel = position.node_->next_;
            delete todel;
            position.node_->next_ = temp.node_;
          }
          else
          {
            return end();
          }
        }
        return res;
      }
    }
    void splice_after(const_iterator pos, ForwardList< T > & other)
    {
      splice_after(pos, std::move(other));
    }
    void splice_after(const_iterator pos, ForwardList< T > && other)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not splice here");
      }
      if (other.head_)
      {
        auto position = begin();
        while (position != pos)
        {
          ++position;
        }
        node_t * temp = position.node_->next_;
        position.node_->next_ = other.head_;
        while (other.head_->next_)
        {
          other.head_ = other.head_->next_;
        }
        other.head_->next_ = temp;
        other.head_ = nullptr;
      }
    }
    void splice_after(const_iterator pos, ForwardList< T > & other, const_iterator it)
    {
      splice_after(pos, std::move(other), it);
    }
    void splice_after(const_iterator pos, ForwardList< T > && other, const_iterator it)
    {
      splice_after(pos, std::move(other), it, other.cend());
    }
    void splice_after(const_iterator pos, ForwardList< T > & other, const_iterator first, const_iterator last)
    {
      splice_after(pos, std::move(other), first, last);
    }
    void splice_after(const_iterator pos, ForwardList< T > && other, const_iterator first, const_iterator last)
    {
      const_iterator nextIt = pos.node_->next_;
      const_iterator currentIt = first.node_->next_;
      pos.node_->next_ = currentIt.node_;
      while (currentIt.node_->next_ != last.node_)
      {
        ++currentIt;
      }
      currentIt.node_->next_ = nextIt.node_;
      const_iterator del = other.cbegin();
      del.node_->next_ = nullptr;
    }
    bool operator==(const ForwardList< T > & other) const
    {
      bool check = true;
      auto otherIterator = other.cbegin();
      auto myIterator = cbegin();
      for (; myIterator != cend(); ++myIterator)
      {
        check = check && (*myIterator == *otherIterator);
        ++otherIterator;
      }
      return check;
    }
    bool operator<(const ForwardList< T > & other) const
    {
      bool check = true;
      auto otherIterator = other.cbegin();
      auto myIterator = cbegin();
      for (; myIterator != cend(); ++myIterator)
      {
        check = check && (*myIterator < *otherIterator);
        ++otherIterator;
      }
      return check;
    }
    bool operator!=(const ForwardList< T > & other) const
    {
      return !(*this == other);
    }
    bool operator>(const ForwardList< T > & other) const
    {
      bool check = true;
      auto otherIterator = other.cbegin();
      auto myIterator = cbegin();
      for (; myIterator != cend(); ++myIterator)
      {
        check = check && (*myIterator > *otherIterator);
        ++otherIterator;
      }
      return check;
    }
    bool operator<=(const ForwardList< T > & other) const
    {
      return !(*this > other);
    }
    bool operator>=(const ForwardList< T > & other) const
    {
      return !(*this < other);
    }
    iterator begin() const
    {
      return iterator(head_);
    }
    const_iterator cbegin() const
    {
      return const_iterator(head_);
    }
    iterator end() const
    {
      return iterator(nullptr);
    }
    const_iterator cend() const
    {
      return const_iterator(nullptr);
    }
    ~ForwardList()
    {
      clear();
    }
  private:
    node_t * head_;
  };
}

#endif
