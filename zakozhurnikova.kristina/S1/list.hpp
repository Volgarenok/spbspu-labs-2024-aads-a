#ifndef LIST_HPP
#define LIST_HPP

namespace zakozhurnikova
{
  template <typename T>
  class List
  {
  public:
    List() :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}

    List(const List& rhs) :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {
      Node< T >* temp = rhs.head_;
      while (temp)
      {
        push(temp->data);
        temp = temp->next;
      }
    }

    List(List&& rhs) noexcept :
      head_(rhs.head_),
      tail_(rhs.tail_),
      size_(size_)
    {
      rhs.head_ = nullptr;
      rhs.tail_ = nullptr;
    }

    List& operator=(const List& rhs)
    {
      if (this != &rhs)
      {
        List temp(rhs);
        clear();
        head_ = temp.head_;
        tail_ = temp.tail_;
      }
      return *this;
    }

    List operator=(List&& rhs) noexcept
    {
      if (this != &rhs)
      {
        swap(rhs);
      }
      return this;
    }

    ~List()
    {
      clear();
    }

  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}
