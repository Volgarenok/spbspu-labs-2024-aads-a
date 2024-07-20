#ifndef DEQUE_HPP
#define DEQUE_HPP
#include <cstddef>
#include <utility>
#include <forward_list.hpp>

namespace zaitsev
{
  template< typename T >
  class PseudoDeque
  {
    using list_tail = typename ForwardList< T >::const_iterator;
    ForwardList< T >list_;
    list_tail tail_;
    size_t size_;

  public:
    PseudoDeque():
      list_(),
      tail_(),
      size_(0)
    {}
    PseudoDeque(const PseudoDeque& other):
      list_(),
      tail_(),
      size_(0)
    {
      using c_it = typename ForwardList< T >::const_iterator;
      if (other.empty())
      {
        return;
      }
      push_front(*(other.list_.cbegin()));
      for (c_it i = ++other.list_.cbegin(); i != other.list_.cend(); ++i)
      {
        push_back(*i);
      }
    }
    PseudoDeque(PseudoDeque&& other):
      list_(std::move(other.list_)),
      tail_(std::move(other.tail_)),
      size_(other.size_)
    {
      other.size_ = 0;
    }
    PseudoDeque& operator=(const PseudoDeque& other)
    {
      PseudoDeque& other_cp(other);
      *this = std::move(other_cp);
      return *this;
    }
    PseudoDeque& operator=(PseudoDeque&& other)
    {
      clear();
      list_ = std::move(other.list_);
      tail_ = std::move(other.tail_);
      size_ = other.size_;

      return *this;
    }
    ~PseudoDeque() = default;

    template< class... Args >
    void emplace_front(Args&&... args)
    {
      list_.emplace_front(std::forward< Args >(args)...);
      if (!size_)
      {
        tail_ = list_.cbegin();
      }
      ++size_;
    }
    void push_front(const T& value)
    {
      emplace_front(value);
    }
    void push_front(T&& value)
    {
      emplace_front(std::move(value));
    }
    void pop_front()
    {
      list_.pop_front();
      --size_;
      if (size_ == 0)
      {
        tail_ = list_.end();
      }
    }

    template< class ... Args >
    void emplace_back(Args&&... args)
    {
      if (!size_)
      {
        list_.emplace_front(std::forward< Args >(args)...);
        tail_ = list_.begin();
      }
      else
      {
        list_.emplace_after(tail_, std::forward< Args >(args)...);
        ++tail_;
      }
      ++size_;
    }
    void push_back(const T& value)
    {
      emplace_back(value);
    }
    void push_back(T&& value)
    {
      emplace_back(std::move(value));
    }

    void clear()
    {
      list_.clear();
      tail_ = list_.end();
      size_ = 0;
    }
    T& front()
    {
      return list_.front();
    }
    const T& front() const
    {
      return list_.front();
    }
    T& back()
    {
      return *tail_;
    }
    const T& back() const
    {
      return *tail_;
    }
    bool empty() const
    {
      return !size_;
    }
    size_t size() const
    {
      return size_;
    }
  };
}
#endif
