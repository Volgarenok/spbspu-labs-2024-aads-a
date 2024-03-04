#ifndef NODE_HPP
#define NODE_HPP

namespace skuratov
{
  template <typename T>
  class Node
  {
  public:
    Node();
    ~Node();

    T& value();
    const T& value() const;
    Node<T>* next();
    const Node<T>* next() const;
    Node<T>* prev();
    const Node<T>* prev() const;

    void set_value(const T& value);
    void set_next(Node<T>* next);
    void set_prev(Node<T>* prev);

  private:
    Node<T>* prev_;
    Node<T>* next_;
    T value_;
  };
}

#endif
