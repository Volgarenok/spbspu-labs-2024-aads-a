#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

namespace zhalilov
{
  template < typename T >
  struct Node
  {
    T value;
    Node *prev;
    Node *next;
  };

  class List
  {
  public:
    List():
      m_size(0),
      m_head(nullptr),
      m_tail(nullptr)
    {}

  private:
    size_t m_size;
    Node < T > *m_head{};
    Node < T > *m_tail{};
  };
}
#endif
