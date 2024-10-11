#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

namespace stepanov
{
  template <typename T>
  class List
  {
  private:
    struct Node
    {
      T data;
      Node* next;
    };

  Node* head;
  Node* tail;
  size_t size;

  void clear();

  public:
    List();
    List(const List& other);
    List& operator=(const List& other);
    List(List&& other) noexcept;
    List& operator=(List&& other) noexcept;
    ~List();

    void push_back();
    size_t get_size() const;
  };
}


#endif

