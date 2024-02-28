# include "list.hpp"

template < typename T >
isaychev::List< T >::List():
  head_(nullptr)
{}

template < typename T >
isaychev::List< T >::~List()
{
  while (!empty())
  {
    pop();
  }
}

template < typename T >
T & isaychev::List< T >::front()
{
  return head_->data;
}

template < typename T >
const T & isaychev::List< T >::front() const
{
  return head_->data;
}

template < typename T >
bool isaychev::List< T >::empty()
{
  return (head_ == nullptr);
}

template < typename T >
void isaychev::List< T >::push(const T & obj)
{
  if (empty())
  {
    head_ = new node_t< T >{obj, nullptr};
  }
  else
  {
    node_t< T > * temp = head_->next;
    while (temp != nullptr)
    {
      temp = temp->next;
    }
    temp = new node_t< T >{obj, nullptr};
  }
}

template < typename T >
void isaychev::List< T >::pop()
{
  if (!empty())
  {
    node_t< T > * temp = head_->next;
    delete head_;
    head_ = temp;
  }
}

template < typename T >
void isaychev::List< T >::clear()
{
  while (!empty())
  {
    pop();
  }
}

template < typename T >
void isaychev::List< T >::swap(List< T > & rhs)
{
  node_t< T > * tempHead = head_;
  head_ = rhs.head_;
  rhs.head_ = tempHead;
}
