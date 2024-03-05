#ifndef NODE_HPP
#define NODE_HPP

namespace skuratov
{
  template <typename T>
  class Node
  {
  public:
    int data{};
    Node<T> prev_;
    Node<T> next_;
    T value_;
  private:
    Node(int data)
    {
      this->data = data;
      this->prev_ = this->next_ = NULL;
    }
  };
}
#endif
