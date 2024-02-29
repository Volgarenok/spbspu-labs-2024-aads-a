#ifndef BILIST_HPP
#define BILIST_HPP

#include "biListIterator.hpp"
#include "biListNode.hpp"

namespace rebdev
{
  template < class T >
  class BiList
  {
    public:
    BiList():
      headNode_(nullptr),
      tailNode_(nullptr)
    {};
    BiList(const BiList< T >& oldList):
      headNode_(oldList.headNode_),
      tailNode_(oldList.tailNode_)
    {};
    BiList(BiList< T >&& rList):
      headNode_(rList.headNode_),
      tailNode_(rList.tailNode_)
    {};
    BiList(const T & firstElement):
    headNode_(new biListNode< T >{firstElement, nullptr, nullptr}),
    tailNode_(headNode_)
    {};

    ~BiList() noexcept
    {
      while (headNode_)
      {
        biListNode< T > * next = headNode_ -> next_;
        delete headNode_;
        headNode_ = next;
      }
      delete headNode_;
    };

    BiList< T >& operator = (const BiList< T >& oldList) noexcept
    {
      headNode_ = oldList.headNode_;
      tailNode_ = oldList.tailNode_;

      return *this;
    };
    BiList< T >& operator = (const BiList< T >&& oldList) noexcept
    {
      headNode_ = oldList.headNode_;
      tailNode_ = oldList.tailNode_;

      return *this;
    };

    T front() const
    {
      return headNode_ -> data_;
    };
    T back() const
    {
      return tailNode_ -> data_;
    };

    void push_back(const T & newElement)
    {
      biListNode< T > * newNode = new biListNode< T >{newElement, nullptr, nullptr};

      newNode -> last_ = tailNode_;
      tailNode_ -> next_ = newNode;

      tailNode_ = newNode;
      newNode = nullptr;
    };
    void push_front(const T & newElement)
    {
      biListNode< T > * newNode = new biListNode< T >{newElement, nullptr, nullptr};

      newNode -> next_ = headNode_;
      headNode_ -> last_ = newNode;

      headNode_ = newNode;
      newNode = nullptr;
    };
    void pop_back() noexcept
    {
      biListNode< T > * newTail = tailNode_ -> last_;

      delete tailNode_;
      newTail -> next_ = nullptr;
      tailNode_ = newTail;
      newTail = nullptr;
    };
    void pop_front() noexcept
    {
      biListNode< T > * newHead = headNode_ -> next_;

      delete headNode_;
      newHead -> last_ = nullptr;
      headNode_ = newHead;
      newHead = nullptr;

    };
    void clear()
    {
      while (headNode_)
      {
        biListNode< T > * next = headNode_ -> next_;
        delete headNode_;
        headNode_ = next;
      }
      delete headNode_;

    };
    void swap(BiList< T >* secondList)
    {
      biListNode< T > secondHead = secondList.begin(), secondTail = secondList.end();
      secondTail.headNode_ = headNode_;
      secondList.tailNode_ = tailNode_;
      headNode_ = secondHead;
      tailNode_ = secondTail;
    };

    biListIterator< T > begin() const noexcept
    {
      return biListIterator< T >(headNode_);
    };
    biListIterator< T > end() const noexcept
    {
      return biListIterator< T >(tailNode_);
    };

    bool capacity()
    {
      return ((headNode_ -> next_) == nullptr);
    };

    private:
    biListNode< T >* headNode_;
    biListNode< T >* tailNode_;
  };
}
#endif
