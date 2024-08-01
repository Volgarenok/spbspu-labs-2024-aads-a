#ifndef LIST_HPP
#define LIST_HPP
namespace sakovskaia
{
  template < typename T >
  class List
  {
  public:
    List() = default;
    using iterator = typename std::forward_list<T>::iterator;
    using const_iterator = typename std::forward_list<T>::const_iterator;
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
