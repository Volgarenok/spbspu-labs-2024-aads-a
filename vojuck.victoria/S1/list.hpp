#ifndef LIST_HPP
#define LIST_HPP

namespace vojuck
{
  template< typename T >
  class List
  {
  public:
    List();
    List(const List< T > & other);
    List(List && other) noexcept;
    ~List();

    List & operator=(const List< T > & other);
    List & operator=(List && other) noexcept;

    IteratorList< T > begin() noexcept;
    IteratorList< T > end() noexcept;
    ConstIteratorList< T > cbegin() const noexcept;
    ConstIteratorList< T > cend() const noexcept;

    bool empty() const noexcept;
    void clear() noexcept;
    void push_back(const T&);
    void push_front(const T&);
    void pop_back();
    void pop_front();
    void swap(List< T >&) noexcept;

  private:
    Node< T >* head_;
    Node< T >* tail_;
  };
}


#endif
