#ifndef LIST_HPP
#define LIST_HPP

namespace nikitov
{
  template< typename T >
  class List
  {
  public:
    List();
    ~List();
  private:
    T value_;
    List< T >* next_;
    List< T >* prev_;
  };
}
#endif
