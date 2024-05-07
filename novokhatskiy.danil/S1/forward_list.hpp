#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include "const_forward_list_iterators.hpp"
#include "forward_list_iterators.hpp"
#include "node.hpp"

namespace novokhatskiy
{
  template < typename T >
  class ForwardIterator;

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
    using node_t = detail::Node< T >;
    ForwardList():
      head_(nullptr)
    {}
    ForwardList(const T& value) noexcept:
      head_(make_list(1, value))
    {}
    ForwardList(ForwardList&& other) noexcept:
      head_(other.head_)
    {
      other.head_ = nullptr;
    }
    ForwardList(const ForwardList< T >& other) noexcept:
      head_(make_list(other.cbegin(), other.cend()))
    {}
    ForwardList(size_t size, const T& value) noexcept:
      head_(make_list(size, value))
    {}
    ForwardList(std::initializer_list< T > list) noexcept:
      head_(make_list(list.begin(), list.end()))
    {}

    ForwardList< T >& operator=(const ForwardList< T >& other)
    {
      if (std::addressof(other) != this)
      {
        ForwardList< T > tmp(other);
        swap(tmp);
      }
      return *this;
    }

    ForwardList< T >& operator=(ForwardList< T >&& other) noexcept
    {
      if (std::addressof(other) != this)
      {
        ForwardList< T > tmp(other);
        swap(tmp);
      }
      return *this;
    }

    iter begin()
    {
      return iter(head_);
    }

    constIter begin() const
    {
      return constIter(head_);
    }

    constIter cbegin() const
    {
      return constIter(head_);
    }

    iter end()
    {
      return iter();
    }

    constIter end() const
    {
      return constIter();
    }

    constIter cend() const
    {
      return constIter();
    }

    bool empty() const noexcept
    {
      return !head_;
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
      auto goToPos = this->begin();
      while (pos.operator!=(goToPos))
      {
        goToPos++;
      }
      node_t* node = new node_t(value);
      node->next_ = goToPos.node_->next_;
      goToPos.node_->next_ = node;
      return goToPos++;
    }

    iter insert_after(constIter pos, size_t count, const T& value)
    {
      auto result = insert_after(pos, value);
      for (size_t i = 1; i < count; i++)
      {
        result = insert_after(pos, value);
      }
      return result;
    }

    iter insert_after(constIter pos, T&& value) noexcept
    {
      auto res = insert_after(pos, value);
      return res;
    }

    iter insert_after(constIter pos, std::initializer_list< T > list)
    {
      node_t* node = make_list(list.begin(), list.end());
      auto res = insert_after(pos, node->value_);
      node = node->next_;
      pos++;
      while (node != nullptr)
      {
        res = insert_after(pos, node->value_);
        node = node->next_;
        pos++;
      }
      return res;
    }

    iter erase_after(constIter pos)
    {
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
      while (std::next(first) != last)
      {
        erase_after(first);
      }
      return iter(const_cast< node_t* >(last.node_));
    }

    void splice_after(constIter pos, ForwardList< T >& other)
    {
      splice_after(pos, std::move(other));
    }

    void splice_after(constIter pos, ForwardList< T >&& other)
    {
      constIter otherBegin = other.cbegin();
      constIter nextIt = pos;
      nextIt++;
      pos.node_->next_ = otherBegin.node_;
      while (otherBegin.node_->next_ != nullptr)
      {
        otherBegin++;
      }
      otherBegin.node_->next_ = nextIt.node_;
      other.head_ = nullptr;
    }

    void splice_after(constIter pos, ForwardList< T >& other, constIter iter)
    {
      splice_after(pos, ForwardList< T >(other), iter);
    }

    void splice_after(constIter pos, ForwardList< T >&& other, constIter iter)
    {
      if (pos == std::next(iter) || pos == iter)
      {
        return;
      }
      splice_after(pos, std::move(other), other.cend());
    }

    void splice_after(constIter pos, ForwardList< T >& other, constIter first, constIter last)
    {
      splice_after(pos, std::move(other), first, last);
    }

    void splice_after(constIter pos, ForwardList< T >&& other, constIter first, constIter last) noexcept
    {
      constIter nextIt = pos.node_->next_;
      constIter curr = first.node_->next_;
      pos.node_->next_ = curr.node_;
      while (curr.node_->next_ != last.node_)
      {
        curr++;
      }
      curr.node_->next_ = nextIt.node_;
      constIter del = other.cbegin();
      del.node_->next_ = nullptr;
    }

    void push_front(const T& value)
    {
      node_t* ptr = new node_t(value);
      ptr->next_ = head_;
      head_ = ptr;
    }

    void push_front(T&& value)
    {
      node_t* ptr = new node_t(std::move(value));
      ptr->next_ = head_;
      head_ = ptr;
    }

    void pop_front()
    {
      if (empty())
      {
        return;
      }
      node_t* temp = head_;
      head_ = head_->next_;
      delete temp;
    }
    size_t size() const
    {
      size_t count{};
      if (head_ == nullptr)
      {
        return count;
      }
      node_t* curr = head_;
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
      node_t* node = make_list(count, value);
      clear();
      head_ = node;
    }

    void assign(std::initializer_list< T > list)
    {
      node_t* node = make_list(list.begin(), list.end());
      clear();
      head_ = node;
    }

    void assign(iter first, iter last)
    {
      node_t* node = make_list(first, last);
      clear();
      head_ = node;
    }

    void swap(ForwardList< T >& other)
    {
      std::swap(head_, other.head_);
    }
    void reverse() noexcept
    {
      if (!head_)
      {
        return;
      }
      node_t* result = head_;
      node_t* temp = head_->next_;
      result->next_ = nullptr;
      while (temp)
      {
        node_t* prev = temp->next_;
        temp->next_ = result;
        result = temp;
        temp = prev;
      }
      head_ = result;
    }
    size_t remove(const T& value)
    {
      return remove_if(
        [&value](const T& tmp) -> bool
        {
          return tmp = value;
        }
      );
    }
    template < typename P >
    size_t remove_if(P predicate)
    {
      size_t removedElement = {};
      node_t* curr = head_;
      node_t* prev = nullptr;
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
          node_t* temp = curr;
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
      if (size() == other.size())
      {
        auto otherIt = other.cbegin();
        for (auto myIt = cbegin(); myIt != cend(); myIt++)
        {
          if (*myIt != *otherIt)
          {
            return false;
          }
          otherIt++;
        }
      }
      else
      {
        return false;
      }
      return true;
    }
    bool operator!=(ForwardList< T >& other) const
    {
      return !(*this == other);
    }
    bool operator<(const ForwardList< T >& other) const
    {
      auto otherIt = other.cbegin();
      for (auto myIt = cbegin(); myIt != cend(); myIt++)
      {
        if (*myIt < *otherIt)
        {
          return true;
        }
        else if (*myIt > *otherIt)
        {
          return false;
        }
        otherIt++;
      }
      return false;
    }

    bool operator>(const ForwardList< T >& other) const
    {
      return (other < *this);
    }
    bool operator<=(const ForwardList< T >& other) const
    {
      return (*this < other);
    }
    bool operator>=(const ForwardList< T >& other) const
    {
      return !(*this < other);
    }

    ~ForwardList()
    {
      clear();
    }

  private:
    detail::Node< T >* head_;
    template < class It >
    static node_t* make_list(It first, It last)
    {
      if (first == last)
      {
        return nullptr;
      }
      node_t* new_head = new node_t(nullptr, *(first++));
      try
      {
        node_t* tail = new_head;
        for (; first != last; ++first)
        {
          tail->next_ = new node_t(nullptr, *first);
          tail = tail->next_;
        }
      }
      catch (...)
      {
        novokhatskiy::detail::freeNode(new_head);
        throw;
      }
      return new_head;
    }

    static node_t* make_list(size_t count, const T& value)
    {
      node_t* new_node = nullptr;
      try
      {
        for (size_t i = 0; i < count; i++)
        {
          node_t* tmp = new node_t(new_node, value);
          new_node = tmp;
        }
      }
      catch (...)
      {
        novokhatskiy::detail::freeNode(new_node);
        throw;
      }
      return new_node;
    }
  };
}

#endif
