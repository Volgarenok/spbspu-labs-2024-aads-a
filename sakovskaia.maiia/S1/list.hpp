#ifndef LIST_HPP
#define LIST_HPP
#include "iterator.hpp"
#include "const_iterator.hpp"
namespace sakovskaia
{
  template < typename T >
  class List
  {
    using iterator = fwdIterator< T >;
    using const_iterator = CFwdIterator< T >;
  public:
    List() = default;
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    T& front();
    const T & front() const;
    bool empty() const;
    void push_back(const T & value);
    void pop_front();
    void clear();
    void swap(List<T>& other);
  private:
    std::forward_list<T> data;
    typename std::forward_list<T>::iterator before_end();
  };
}
#endif
