#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <forward_list_iterators.hpp>
#include <forward_list.hpp>

namespace novokhatskiy
{
  template < class T >
  class Queue
  {
  public:
    void push(const T& value)
    {
      if (data_.cbegin() == data_.cend())
      {
        data_.push_front(value);
        return;
      }
      auto it = data_.cbegin();
      for (auto it2 = ++(data_.cbegin()); it2 != data_.cend(); it++, it2++);
      data_.insert_after(it, value);
    }
    bool empty() const noexcept
    {
      return data_.empty();
    }
    size_t size() const noexcept
    {
      return data_.size();
    }
    void pop()
    {
      data_.pop_front();
    }
    T& front()
    {
      if (empty())
      {
        throw std::invalid_argument("Queue is empty");
      }
      return data_.front();
    }

  private:
    ForwardList< T > data_;
  };
}

#endif
