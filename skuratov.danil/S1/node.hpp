#ifndef NODE_HPP
#define NODE_HPP

namespace skuratov
{
  template <typename T>
  class Node
  {
  public :
    Node();
    ~Node()
  private:
    Node<T> prew_;
    Node<T> next_;
    T value_;
  };
}

#endif
