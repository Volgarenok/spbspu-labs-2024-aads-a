#ifndef LIST_HPP
#define LIST_HPP

namespace skurtov
{
  template <typename T>
  class list
  {
  public:
    List();
    ~List();
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}

#endif
