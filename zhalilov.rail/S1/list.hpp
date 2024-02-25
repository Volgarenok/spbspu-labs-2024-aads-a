#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

namespace zhalilov
{
  template < typename T >
  struct Node {
    T value;
    Node *prev;
    Node *next;
  };

  class List {
  public:
    List():
      m_size(0),
      m_head(nullptr),
      m_tail(nullptr)
    {}

    void push_back(T &&value)
    {
      Node < T > *newTail = nullptr;
      try
      {
        newTail = new Node < T >;
        newTail->value = value;
        newTail->prev = m_tail;
        newTail->next = nullptr;
        m_tail->next = newTail;
        m_tail = newTail;
      }
      catch (...)
      {
        delete newTail;
        throw;
      }
    }

    void push_front(T &&value)
    {
      Node < T > *newTail = nullptr;
      try
      {
        newTail = new Node < T >;
        newTail->value = value;
        newTail->prev = nullptr;
        newTail->next = m_head;
        m_head->prev = newTail;
        m_head = newTail;
      }
      catch (...)
      {
        delete newTail;
        throw;
      }
    }

  private:
    size_t m_size;
    Node < T > *m_head {};
    Node < T > *m_tail {};
  };
}
#endif
