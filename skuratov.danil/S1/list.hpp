#ifndef LIST_HPP
#define LIST_HPP

namespace skurtov
{
  template <class T>
  class list
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
