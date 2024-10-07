#ifndef STACK_HPP
#define STACK_HPP

namespace vojuck
{
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack& other) = default;
    Stack(Stack&& other) noexcept = default;
    Stack& operator=(const Stack& other) = default;
    Stack& operator=(Stack&& other) noexcept = default;
    ~Stack() = default;struct Stack
  private:
    List<T> data_;
  };
}
