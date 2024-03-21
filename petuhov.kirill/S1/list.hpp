#ifndef LIST_HPP
#define LIST_HPP

namespace petuhov
{
  template <typename T>
  class List
  {
    List();
    T &front();
    const T &front();
    bool empty() const;
    void push_front(const T &value);
    void pop_front();
    void clear();
    void swapt(List &other);
    ~List();

  private:
    struct Node
    {
      T value;
      Node *next;
    } Node *head_;
  };
}

#endif
