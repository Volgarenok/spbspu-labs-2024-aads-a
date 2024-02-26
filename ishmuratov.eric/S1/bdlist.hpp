#ifndef BDLIST_HPP
#define BDLIST_HPP

namespace ishmuratov
{
  template< class T >
  class List
  {
    public:
      Node * head;
      Node * tail;
      List()
      {
        head = nullptr;
        tail = nullptr;
      }
      Node * pushFront(T data)
      {
        Node * ptr = new Node(data);
        ptr->next = head;
        if (head != nullptr)
        {
          head->prev = ptr;
        }
        if (tail == nullptr)
        {
          tail = ptr;
        }
        head = ptr;
        return ptr;
      }
      Node * pushBack(T data)
      {
        Node * ptr = new Node(data);
        ptr->prev = tail;
        if (tail != nullptr)
        {
          tail->next = ptr;
        }
        if (head == nullptr)
        {
          head = ptr;
        }
        tail = ptr;
        return ptr;
      }
    private:
      struct Node
      {
        T data;
        Node * prev;
        Node * next;
        Node(T data)
        {
          this->data = data;
          this->prev = nullptr;
          this->next = nullptr;
        }
      };
  };
}

#endif
