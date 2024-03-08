#ifndef NODE_HPP
#define NODE_HPP

namespace skuratov
{
  template <typename T>
  class Node
  {
  public:
    ~Node() = default;
    size_t data{};
    Node<T>* prev;
    Node<T>* next;
    T value;
  private:
    Node(size_t data)
    {
      this->data = data;
      this->prev = this->next = NULL;
    }
  };
}
#endif
