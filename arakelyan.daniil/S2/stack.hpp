#ifndef STACK_HPP
#define STACK_HPP

#include <utility>
#include <list/binList.hpp>

namespace arakelyan
{
  template < class T, class Container = BinList< T > >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack &otherS);
    Stack(Stack &&otherS) noexcept;
    ~Stack() = default;

    //operators= ??

    bool empty() const;
    size_t size() const;

    T &top();
    const T &top() const;

    void push(const T &val);
    void push(T &&val);

    // template <class... Args >
    // void emplace(Args&&... args); // no emplace in my BiList =(

    void pop();

    void swap(Stack &otherS) noexcept;
  private:
    Container data_;
  };

  template < class T, class Container >
  Stack< T, Container >::Stack():
    data_()
  {}

  template < class T, class Container >
  Stack< T, Container >::Stack(const Stack &otherS):
    data_(otherS.data_)
  {}

  template < class T, class Container >
  Stack< T, Container >::Stack(Stack &&otherS) noexcept:
    data_(std::move(otherS.data_))
  {}

  template < class T, class Container >
  bool Stack< T, Container >::empty() const
  {
    return data_.empty();
  }

  template < class T, class Container >
  size_t Stack< T, Container >::size() const
  {
    return data_.get_size();
  }

  template < class T, class Container >
  T &Stack< T, Container >::top()
  {
    return data_.front();
  }

  template < class T, class Container >
  const T &Stack< T, Container >::top() const
  {
    return data_.front();
  }

  template < class T, class Container >
  void Stack< T, Container >::push(const T &val)
  {
    data_.push_front(val);
  }

  template < class T, class Container >
  void Stack< T, Container >::push(T &&val)
  {
    data_.push_front(std::move(val));
  }

  template < class T, class Container >
  void Stack< T, Container >::pop()
  {
    data_.pop_front();
  }

  template < class T, class Container >
  void Stack< T, Container >::swap(Stack &otherS) noexcept
  {
    std::swap(data_, otherS.data_);
  }
}
#endif
