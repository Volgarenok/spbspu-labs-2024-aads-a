#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace petuhov {

  template < typename T >
  class Queue {
  public:
    Queue() = default;
    void push(const T & value);
    void push(T && value);
    void pop();
    T & front();
    const T & front() const;
    bool empty() const noexcept;
    std::size_t size() const noexcept;

  private:
    List < T > list_;
  };

  template < typename T >
  void Queue < T >::push(const T & value) {
    list_.insert(list_.end(), value);
  }

  template < typename T >
  void Queue < T >::push(T && value) {
    list_.insert(list_.end(), std::move(value));
  }

  template < typename T >
  void Queue < T >::pop() {
    list_.erase(list_.begin());
  }

  template < typename T >
  T & Queue < T >::front() {
    return list_.front();
  }

  template < typename T >
  const T & Queue < T >::front() const {
    return list_.front();
  }

  template < typename T >
  bool Queue < T >::empty() const noexcept {
    return list_.empty();
  }

  template < typename T >
  std::size_t Queue < T >::size() const noexcept {
    std::size_t count = 0;
    for (auto it = list_.cbegin(); it != list_.cend(); ++it) {
      ++count;
    }
    return count;
  }
}

#endif
