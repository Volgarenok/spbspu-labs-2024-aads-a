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
      headNode_(new biListNode< T >{0, nullptr, nullptr}),
      tailNode_(new biListNode< T >{0, nullptr, nullptr})
    {
      headNode_ -> next_ = tailNode_;
      tailNode_ -> last_ = headNode_;
    };
    BiList(const BiList< T >& oldList):
      headNode_(nullptr),
      tailNode_(nullptr)
    {
      this = oldList;
    };
    BiList(BiList< T >&& rList):
      headNode_(nullptr),
      tailNode_(nullptr)
    {
      this = std::move(rList);
    };
    BiList(const T & firstElement):
    headNode_(nullptr),
    tailNode_(nullptr)
    {
      BiList();
      biListNode< T >* newNode = new biListNode< T >{firstElement, headNode_, tailNode_};
      headNode_ -> next_ = newNode;
      tailNode_ -> last_ = newNode;
    };

    ~BiList() noexcept
    {
      clear();
    };

    BiList< T >& operator = (const BiList< T >& originalList)
    {
      clear();
      using node = biListNode< T >;

      node* nodePointer = originalList.headNode_;

      headNode_ = new node{nodePointer -> data_, nullptr, nullptr};

      nodePointer = nodePointer -> next_;

      tailNode_ = new node{nodePointer -> data_, headNode_, nullptr};
      headNode_ -> next_ = tailNode_;

      while (nodePointer != (originalList.tailNode_))
      {
        nodePointer = nodePointer -> next_;
        node * newNode = new node{nodePointer -> data_, tailNode_, nullptr};

        tailNode_ -> next_ = newNode;
        tailNode_ = newNode;

        newNode = nullptr;
      }

      return *this;
    };
    BiList< T >& operator = (const BiList< T >&& originalList)
    {
      return operator = (originalList);
    };

    T front() const
    {
      return headNode_ -> next_ -> data_;
    };
    T back() const
    {
      return tailNode_ -> last_ -> data_;
    };

    void push_back(const T & newElement)
    {
      biListNode< T > * newNode = new biListNode< T >{0, tailNode_, nullptr};
      tailNode_ -> data_ = newElement;
      tailNode_ -> next_ = newNode;
      tailNode_ = newNode;
      newNode = nullptr;

    };
    void push_front(const T & newElement)
    {
      biListNode< T >* newNode = new biListNode< T >{0, nullptr, headNode_};
      headNode_ -> data_ = newElement;
      headNode_ -> last_ = newNode;
      headNode_ = newNode;
      newNode = nullptr;
    };
    void pop_back() noexcept
    {
      biListNode< T >* newTail = tailNode_ -> last_;

      delete tailNode_;
      newTail -> next_ = nullptr;
      tailNode_ = newTail;
      newTail = nullptr;
    };
    void pop_front() noexcept
    {
      biListNode< T >* newHead = headNode_ -> next_;

      delete headNode_;
      newHead -> last_ = nullptr;
      headNode_ = newHead;
      newHead = nullptr;
    };
    void clear() noexcept
    {
      while (headNode_)
      {
        biListNode< T >* next = headNode_ -> next_;
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
      return ((headNode_ -> next_) == tailNode_);
    };

    private:
    biListNode< T >* headNode_;
    biListNode< T >* tailNode_;

    bool headIsFull, tailIsFull;
  };
}
#endif
