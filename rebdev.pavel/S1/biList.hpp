#ifndef BILIST_HPP
#define BILIST_HPP

#include <initializer_list>

#include "biListIterator.hpp"
#include "biListC_Iterator.hpp"
#include "biListNode.hpp"

namespace rebdev
{
  template < class T >
  class BiList
  {
    using node = biListNode< T >;
    using list = BiList< T >;
    using iter = biListIterator< T >;
    using c_iter = biListC_Iterator< T >;


    public:
    //Constructors
      BiList():
        headNode_(new node{0, nullptr, nullptr}),
        tailNode_(new node{0, nullptr, nullptr})
      {
        headNode_ -> next_ = tailNode_;
        tailNode_ -> last_ = headNode_;
      }


      BiList(size_t n): BiList(n, 0)
      {}

      BiList(size_t n, const T& val):
        headNode_(nullptr),
        tailNode_(nullptr)
      {
        assign(n, val);
      }

      template <class InputIterator>
      BiList (InputIterator first, InputIterator last):
        headNode_(nullptr),
        tailNode_(nullptr)
      {
        assign(first, last);
      }

      BiList(const list& oldList):
        headNode_(nullptr),
        tailNode_(nullptr)
      {
        *this = oldList;
      }

      BiList(list&& rList):
        headNode_(rList.headNode_),
        tailNode_(rList.tailNode_)
      {}

      BiList(const T & firstElement):
        headNode_(new node{0, nullptr, nullptr}),
        tailNode_(new node{0, nullptr, nullptr})
      {
        node* newNode = new node{firstElement, headNode_, tailNode_};
        headNode_ -> next_ = newNode;
        tailNode_ -> last_ = newNode;
      }


      BiList(std::initializer_list< T > il): BiList< decltype(il.begin()) >(il.begin(), il.end())
      {}


      ~BiList() noexcept
      {
        clear();
      }



      //Operators
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
        }

        return *this;
      }
      list& operator = (const list&& originalList)
      {
        clear();

        headNode_ = originalList.headNode_;
        tailNode_ = originalList.tailNode_;
        return *this;
      }



      //Iterators
      iter begin() noexcept
      {
        return iter(*headNode_);
      }

      iter end() noexcept
      {
        return iter(*tailNode_);
      }

      c_iter begin() const noexcept
      {
        return c_iter(*headNode_);
      }

      c_iter end() const noexcept
      {
        return c_iter(*tailNode_);
      }



      //Capacity
      bool empty() const noexcept
      {
        return ((headNode_ -> next_) == tailNode_);
      }



      //Element access
      T front()
      {
        return headNode_ -> next_ -> data_;
      }
      T back()
      {
        return tailNode_ -> last_ -> data_;
      }

      const T front() const
      {
        return headNode_ -> next_ -> data_;
      }
      const T back() const
      {
        return tailNode_ -> last_ -> data_;
      }



      //Modifiers
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
        }
      }
      void assign (size_t n, const T& val)
      {
        clear();
        headNode_ = new node{0, nullptr, nullptr};
        tailNode_ = new node{0, headNode_, nullptr};
        headNode_ -> next_ = tailNode_;

        for (size_t i = 0; i < n; ++i)
        {
          push_back(val);
        }
      }
      void assign (std::initializer_list< T > il)
      {
        assign< decltype(il.begin()) >(il.begin(), il.end());
      }

      void push_back(const T & newElement)
      {
        node* newNode = new node{0, tailNode_, nullptr};
        tailNode_ -> data_ = newElement;
        tailNode_ -> next_ = newNode;
        tailNode_ = newNode;
      }
      void push_front(const T & newElement)
      {
        node* newNode = new node{0, nullptr, headNode_};
        headNode_ -> data_ = newElement;
        headNode_ -> last_ = newNode;
        headNode_ = newNode;
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
      }
      void pop_front()
      {
        node* newHead = headNode_ -> next_;
        delete headNode_;
        newHead -> last_ = nullptr;
        headNode_ = newHead;
      }

      iter insert(c_iter position, const T& val)
      {
        node* last = position.getNode();
        node* next = position.getNode() -> next_;
        node* newNode = new node(val, last, next);
        last.next_ = newNode;
        next.last_ = newNode;
        last = nullptr;
        next = nullptr;
        return iter(newNode);
      }
      iter insert(c_iter position, size_t n, const T& val)
      {
        c_iter firstIter(insert(position, val));
        c_iter iterNow = firstIter;

        for (size_t i = 1; i < n; ++i)
        {
          iterNow = insert(iterNow, val);
        }

        return firstIter;
      }
      template <class InputIterator>
      iter insert(c_iter position, InputIterator first, InputIterator last)
      {
        iter firstIter(insert(position, *first));
        c_iter iterNow = firstIter;

        while (first != last)
        {
          ++first;
          iterNow = insert(iterNow, *first);
        }

        return firstIter;
      }
      iter insert(c_iter position, T&& val)
      {
        return insert(position, val);
      }
      iter insert(c_iter position, std::initializer_list< T > il)
      {
        return insert< decltype(il.begin()) >(position, il.begin(), il.end());
      }

      iter erase (c_iter position)
      {
        node* deleteNode = position.getNode();
        node* last = deleteNode -> last_;
        node* next = deleteNode -> next_;
        last -> next_ = next;
        next -> last_ = last;
        delete deleteNode;
        return iter(next);
      }
      iter erase (c_iter first, c_iter last)
      {
        iter nextEl = erase(first);
        ++first;
        while (first != last)
        {
          nextEl = erase(first);
          ++first;
        }
        return nextEl;
      }

      void swap(list& secondList)
      {
        node secondHead = secondList.begin(), secondTail = secondList.end();

        secondTail.headNode_ = headNode_;
        secondList.tailNode_ = tailNode_;
        headNode_ = secondHead.getNode();
        tailNode_ = secondTail.getNode();
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



      //Operations
      void splice (c_iter position, list& x)
      {
        node* nodeNow = position.getNode();

        nodeNow -> next_ -> last_ = x.tailNode_;
        x.tailNode_ -> next_ = nodeNow -> next_;

        nodeNow -> next_ = x.headNode_;
        x.headNode_ -> last_ = nodeNow;

        x.tailNode_ = nullptr;
        x.headNode_ = nullptr;
      }
      void splice (c_iter position, list&& x)
      {
        splice(position, x);
      }
      void splice (c_iter position, list& x, c_iter i)
      {
        node* nodeNow = position.getNode();
        node* spliceNode = i.getNode();
        node* last = spliceNode -> last_;
        node* next = spliceNode -> next_;

        last -> next_ = next;
        next -> last_ = last;

        nodeNow -> next_ -> last_ = i;
        i -> next_ = nodeNow -> next_;

        nodeNow -> next_ = i;
        i -> last_ = nodeNow;

      }
      void splice (c_iter position, list&& x, c_iter i)
      {
        splice(position, x, i);
      }
      void splice (c_iter position, list& x, c_iter first, c_iter last)
      {
        c_iter iterNow = first;
        do
        {
          splice(position, x, iterNow);
          ++iterNow;
        } while (iterNow != last);
      }
      void splice (c_iter position, list&& x, c_iter first, c_iter last)
      {
        splice(position, x, first, last);
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

      void reverse() noexcept
      {
        iter tail = end();
        iter head = begin();
        while (tail != head)
        {
          reverseTwoNode(*tail.getNode(), *head.getNode());
          ++head;
          if(head == tail) break;
          --tail;
        }
      }

    private:
      node* headNode_;
      node* tailNode_;

      void reverseTwoNode(node& first, node& second) noexcept
      {
        first.last_ -> next_ = second;
        first.next_ -> last_ = second;
        second.next_ -> last_ = first;
        second.last_ -> next_ = first;

        node* nodePointer = first.next_;
        first.next_ = second.next_;
        second.next_ = nodePointer;

        nodePointer = first.last_;
        first.last_ = second.last_;
        second.last_ = nodePointer;
      }
  };
}
#endif
