#ifndef LIST_HPP
#define LIST_HPP

template<typename T>
class List
{
public:
  List();
  ~List();

  void push_back(T data);
  void delete_front();
  int getSize() { return size; }
  T& operator[](const int index);

private:
  class Node
  {
  public:
    Node* pNext;
    T data;

    Node(T data = T(), Node* pNext = nullptr)
    {
      this->data = data;
      this->pNext = pNext;
    }
  };
  int size;
  Node* head;
};

#endif
