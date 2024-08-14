#ifndef LIST_HPP
#define LIST_HPP
#include "iterator.hpp"
#include "const_iterator.hpp"
namespace sakovskaia
{
  template < typename T >
  class List
  {
  public:
    using iterator = fwdIterator< T >;
    using const_iterator = CFwdIterator< T >;
    List();
    ~List();
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    bool empty() const;
    void push_front(const T & value);
    void pop_front();
    void clear();
    void swap(List< T > & other);
  private:
    node_t< T > * head_;
    void copy_from(const List & other);
    void move_from(List && other) noexcept;
  };
}
#endif
