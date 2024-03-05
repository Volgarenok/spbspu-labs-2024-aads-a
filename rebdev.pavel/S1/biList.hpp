#ifndef BILIST_HPP
#define BILIST_HPP

#include "biListIterator.hpp"
#include "biListNode.hpp"

namespace rebdev
{
  template < class T >
  class BiList
  {
    using node = biListNode< T >;
    using list = BiList< T >;

    public:
      BiList():
        headNode_(new node{0, nullptr, nullptr}),
        tailNode_(new node{0, nullptr, nullptr})
      {
        headNode_ -> next_ = tailNode_;
        tailNode_ -> last_ = headNode_;
      }
      BiList(const list& oldList):
        headNode_(nullptr),
        tailNode_(nullptr)
      {
        this -> operator = (oldList);
      }
      BiList(list&& rList):
        headNode_(headNode_),
        tailNode_(tailNode_)
      {}
      BiList(const T & firstElement):
      headNode_(nullptr),
      tailNode_(nullptr)
      {
        BiList();
        node* newNode = new node{firstElement, headNode_, tailNode_};
        headNode_ -> next_ = newNode;
        tailNode_ -> last_ = newNode;
      }

      ~BiList() noexcept
      {
        clear();
      }

      list& operator = (const list& originalList)
      {
        clear();

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
      }
      list& operator = (const list&& originalList)
      {
        headNode_ = originalList.headNode_;
        tailNode_ = originalList.tailNode_;
        return *this;
      }

      T front() const
      {
        return headNode_ -> next_ -> data_;
      }
      T back() const
      {
        return tailNode_ -> last_ -> data_;
      }

      void push_back(const T & newElement)
      {
        node* newNode = new node{0, tailNode_, nullptr};
        tailNode_ -> data_ = newElement;
        tailNode_ -> next_ = newNode;
        tailNode_ = newNode;
        newNode = nullptr;
      }
      void push_front(const T & newElement)
      {
        node* newNode = new node{0, nullptr, headNode_};
        headNode_ -> data_ = newElement;
        headNode_ -> last_ = newNode;
        headNode_ = newNode;
        newNode = nullptr;
      }
      void pop_back()
      {
        node* newTail = tailNode_ -> last_;
        delete tailNode_;
        newTail -> next_ = nullptr;
        tailNode_ = newTail;
        newTail = nullptr;
      }
      void pop_front()
      {
        node* newHead = headNode_ -> next_;
        delete headNode_;
        newHead -> last_ = nullptr;
        headNode_ = newHead;
        newHead = nullptr;
      }
      void clear() noexcept
      {
        while (headNode_)
        {
          node* next = headNode_ -> next_;
          delete headNode_;
          headNode_ = next;
        }
        delete headNode_;
      }
      void swap(BiList< T >* secondList)
      {
        node secondHead = secondList.begin(), secondTail = secondList.end();
        secondTail.headNode_ = headNode_;
        secondList.tailNode_ = tailNode_;
      }

      biListIterator< T > begin() const noexcept
      {
        return biListIterator< T >(headNode_);
      }
      biListIterator< T > end() const noexcept
      {
        return biListIterator< T >(tailNode_);
      }

      bool capacity()
      {
        return ((headNode_ -> next_) != tailNode_);
      }

    private:
      node* headNode_;
      node* tailNode_;
  };
}
#endif
