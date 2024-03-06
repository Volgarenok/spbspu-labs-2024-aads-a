#ifndef FORWARD_SEQUENCE_HPP
#define FORWARD_SEQUENCE_HPP

namespace spiridonov
{

  template <typename T>
  class Node
  {
  public:
    T data;
    Node<T>* next;

    Node(T value) : data(value), next(nullptr)
    {
    }
  };

  template <typename T>
  class Sequence
  {
  private:
    Node<T>* head;
    Node<T>* tail;
    int size;

  public:
    Sequence();
    ~Sequence();

    void push_back(T value);

    class Iterator
    {
    private:
      Node<T>* current;

    public:
      Iterator(Node<T>* node) : current(node)
      {
      }

      Iterator& operator++()
      {
        current = current->next;
        return *this;
      }

      T& operator*()
      {
        return current->data;
      }

      bool operator!=(const Iterator& other) const
      {
        return current != other.current;
      }
    };

    Iterator begin();
    Iterator end();
  };

  const int max_sequence_len = 100;

  template <typename T>
  class NamedSequence
  {
  public:
    char name[30];
    int length;
    T sequence[max_sequence_len];
  };

}

#endif
