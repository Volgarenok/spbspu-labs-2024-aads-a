#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>

namespace piyavkin
{
  template< class T >
  class List
  {
  public:
    List():
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}
  private:
    struct Node
    {
      Node(const T& value) :
        val(value),
        next(nullptr),
        prev(nullptr)
      {}
      ~Node() = default;
      T val;
      Node* next;
      Node* prev;
    };
    Node* head_;
    Node* tail_;
    size_t size_;
  };
}
#endif
