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
    using iter = biListIterator< T >;

    public:
      BiList(): BiList(0, 0)
      {}
      BiList(const list& oldList):
        headNode_(nullptr),
        tailNode_(nullptr)
      {
        *this = oldList;
      }

      BiList(list&& rList):
        headNode_(headNode_),
        tailNode_(tailNode_)
      {}
      BiList(const T & firstElement):
      headNode_(new node{0, nullptr, nullptr}),
      tailNode_(new node{0, nullptr, nullptr})
      {
        node* newNode = new node{firstElement, headNode_, tailNode_};
        headNode_ -> next_ = newNode;
        tailNode_ -> last_ = newNode;
      }

      BiList(size_t n): BiList(n, 0)
      {}
      BiList(size_t n, const T& val):
      headNode_(new node{0, nullptr, nullptr}),
      tailNode_(new node{0, nullptr, nullptr})
      {
        headNode_ -> next_ = tailNode_;
        tailNode_ -> last_ = headNode_;
        for (size_t i = 0; i < n; ++i)
        {
          push_back(val);
        }
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


      iter begin() const noexcept
      {
        return iter(*headNode_);
      }
      iter end() const noexcept
      {
        return iter(*tailNode_);
      }


      bool empty() const noexcept
      {
        return ((headNode_ -> next_) == tailNode_);
      }


      T front() const
      {
        return headNode_ -> next_ -> data_;
      }
      T back() const
      {
        return tailNode_ -> last_ -> data_;
      }

      template <class InputIterator>
      void assign (InputIterator first, InputIterator last)
      {
        clear();

        headNode_ = new node{*first, nullptr, nullptr};

        ++first;

        tailNode_ = new node{*first, headNode_, nullptr};
        headNode_ -> next_ = tailNode_;

        while (first != last)
        {
          ++first;
          node * newNode = new node{*first, tailNode_, nullptr};

          tailNode_ -> next_ = newNode;
          tailNode_ = newNode;

          newNode = nullptr;
        }
      }
      void assign (size_t n, const T& val)
      {
        clear();
        BiList(n, val);
      }
      void assign (list il)
      {
        clear();
        *this = il;
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

      void push_back(T && newElement)
      {
        push_back(newElement);
      }
      void push_front(T && newElement)
      {
        pushFront(newElement);
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

      void swap(list* secondList)
      {
        node secondHead = secondList.begin(), secondTail = secondList.end();
        secondTail.headNode_ = headNode_;
        secondList.tailNode_ = tailNode_;
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


      void remove (const T& val)
      {
        iter iterNow = begin();
        while ((++iterNow) != end())
        {
          if (*iterNow == val)
          {
            node* lastNode = iterNow.getNode() -> last_;
            node* nextNode = iterNow.getNode() -> next_;
            lastNode -> next_ = nextNode;
            nextNode -> last_ = lastNode;
            delete iterNow.getNode();
          }
        }
      }

      template < class Predicate >
      void remove_if (Predicate pred)
      {
        iter iterNow = begin();
        while ((++iterNow) != end())
        {
          if (pred(iterNow))
          {
            node* lastNode = iterNow.getNode() -> last_;
            node* nextNode = iterNow.getNode() -> next_;
            lastNode -> next_ = nextNode;
            nextNode -> last_ = lastNode;
            delete iterNow.getNode();
          }
        }
      }

    private:
      node* headNode_;
      node* tailNode_;
  };
}
#endif
