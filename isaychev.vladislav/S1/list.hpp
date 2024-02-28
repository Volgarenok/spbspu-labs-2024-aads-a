#ifndef LIST_HPP
#define LIST_HPP

namespace isaychev
{
  template < typename T >
  struct node_t
  {
    T data;
    node_t< T > * next;
  };

  template < typename T >
  class List
  {
   public:
    List();
    ~List();

    //iterator
    //constIterator

    T & front();
    const T & front() const;
    bool empty();
    void push(const T & obj);
    void pop();
    void clear();
    void swap(List< T > & rhs);

   private:
    node_t< T > * head_;
  };
}

#endif
