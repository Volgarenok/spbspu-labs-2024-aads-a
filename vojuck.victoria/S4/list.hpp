#ifndef LIST_HPP
#define LIST_HPP

#include <iterator>

template <typename T>
class List {
private:
  struct Node
  {
    T data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* head;

public:
 List() : head(nullptr) {}

  ~List()
  {
    while (head)
    {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  void push_front(const T& value)
  {
    Node* new_node = new Node(value);
    new_node->next = head;
    head = new_node;
  }

  void pop_front()
  {
    if (head)
    {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  const T& front() const
  {
    if (!head)
    {
      throw std::runtime_error("List is empty");
    }
      return head->data;
  }

  bool empty() const
  {
    return head == nullptr;
  }

  bool operator==(const List& other) const
  {
    Node* current1 = head;
    Node* current2 = other.head;

    while (current1 && current2)
    {
      if (current1->data != current2->data)
      {
        return false;
      }
        current1 = current1->next;
        current2 = current2->next;
    }

    return current1 == nullptr && current2 == nullptr;
  }

};

#endif
