#ifndef STACK_HPP
#define STACK_HPP

#include <list.hpp>

namespace petuhov {

  template < typename T >
  class Stack {
  public:
    Stack();
    Stack(const Stack & other);
    Stack(Stack && other) noexcept;
    Stack & operator=(const Stack & other);
    Stack & operator=(Stack && other) noexcept;
    ~Stack();

    void push(const T & value);
    void push(T && value);
    void pop();
    T & top();
    const T & top() const;
    bool empty() const noexcept;
    std::size_t size() const noexcept;

  private:
    List < T > list_;
  };

  template < typename T >
  Stack < T >::Stack() : list_() {}

  template < typename T >
  Stack < T >::Stack(const Stack < T > & other) : list_(other.list_) {}

  template < typename T >
  Stack < T >::Stack(Stack < T > && other) noexcept : list_(std::move(other.list_)) {}

  template < typename T >
  Stack < T > & Stack < T >::operator=(const Stack < T > & other) {
    if (this != &other) {
      list_ = other.list_;
    }
    return *this;
  }

  template < typename T >
  Stack < T > & Stack < T >::operator=(Stack < T > && other) noexcept {
    if (this != &other) {
      list_ = std::move(other.list_);
    }
    return *this;
  }

  template < typename T >
  Stack < T >::~Stack() {}

  template < typename T >
  void Stack < T >::push(const T & value) {
    list_.push_front(value);
  }

  template < typename T >
  void Stack < T >::push(T && value) {
    list_.push_front(std::move(value));
  }

  template < typename T >
  void Stack < T >::pop() {
    if (list_.empty()) {
      throw std::out_of_range("Stack is empty");
    }
    list_.pop_front();
  }

  template < typename T >
  T & Stack < T >::top() {
    if (list_.empty()) {
      throw std::out_of_range("Stack is empty");
    }
    return list_.front();
  }

  template < typename T >
  const T & Stack < T >::top() const {
    if (list_.empty()) {
      throw std::out_of_range("Stack is empty");
    }
    return list_.front();
  }

  template < typename T >
  bool Stack < T >::empty() const noexcept {
    return list_.empty();
  }

  template < typename T >
  std::size_t Stack < T >::size() const noexcept {
    std::size_t count = 0;
    for (auto it = list_.cbegin(); it != list_.cend(); ++it) {
      ++count;
    }
    return count;
  }

}

#endif
