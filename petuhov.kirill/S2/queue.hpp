#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <common/list.hpp>

namespace petuhov {

  template < typename T >
  class Queue {
  public:
    Queue(const Queue & other);
    Queue(Queue && other) noexcept;
    Queue & operator=(const Queue & other);
    Queue & operator=(Queue && other) noexcept;

    void push(const T & value);
    void push(T && value);
    void pop();
    T & front();
    const T & front() const;
    T & back();
    const T & back() const;
    bool empty() const noexcept;
    std::size_t size() const noexcept;

  private:
    List < T > list_;
  };

  template < typename T >
  Queue < T >::Queue(const Queue < T > & other) : list_(other.list_) {}

  template < typename T >
  Queue < T >::Queue(Queue < T > && other) noexcept : list_(std::move(other.list_)) {}

  template < typename T >
  Queue < T > & Queue < T >::operator=(const Queue < T > & other) {
    if (this != &other) {
      list_ = other.list_;
    }
    return *this;
  }

  template < typename T >
  Queue < T > & Queue < T >::operator=(Queue < T > && other) noexcept {
    if (this != &other) {
      list_ = std::move(other.list_);
    }
    return *this;
  }

  template < typename T >
  void Queue < T >::push(const T & value) {
    list_.push_back(value);
  }

  template < typename T >
  void Queue < T >::push(T && value) {
    list_.push_back(std::move(value));
  }

  template < typename T >
  void Queue < T >::pop() {
    if (list_.empty()) {
      throw std::out_of_range("Queue is empty");
    }
    list_.pop_front();
  }

  template < typename T >
  T & Queue < T >::front() {
    if (list_.empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return list_.front();
  }

  template < typename T >
  const T & Queue < T >::front() const {
    if (list_.empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return list_.front();
  }

  template < typename T >
  T & Queue < T >::back() {
    if (list_.empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return list_.back();
  }

  template < typename T >
  const T & Queue < T >::back() const {
    if (list_.empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return list_.back();
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
