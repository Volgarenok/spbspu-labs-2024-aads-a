#ifndef LIST_HPP
#define LIST_HPP

namespace isaychev
{
  template < typename T >
  struct node_t
  {
    T data;
    node_t * next;
  };

  class List
  {
   public:
    List();
    ~List();
    List(const List & rhs);
    List(const List && rhs);

    //iterator
    //constIterator

    T & front();
    const T & front() const;
    bool empty();
    void push();
    void pop();
    void clear();
    void swap(List & rhs);

   private:
    node_t * head;
  };
}

#endif
