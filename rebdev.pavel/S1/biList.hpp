#ifndef BILIST_HPP
#define BILIST_HPP

#include <initializer_list>

#include "BidirectionalIterator.hpp"
#include "constBidirectionalIterator.hpp"
#include "biListNode.hpp"

namespace rebdev
{

  template < class T >
  class BiList
  {
    using node = biListNode< T >;
    using list = BiList< T >;
    using iter = BidirectionalIterator< T >;
    using const_iter = ConstBidirectionalIterator< T >;

    public:
      BiList():
        headNode_(nullptr),
        tailNode_(nullptr)
      {
        createHeadTail();5
      }


      BiList(size_t n): BiList(n, T{})
      {}

      BiList(size_t n, const T & val):
        headNode_(nullptr),
        tailNode_(nullptr)
      {
        assign(n, val);
      }

      template < class InputIterator >
      BiList (InputIterator first, InputIterator last):
        headNode_(nullptr),
        tailNode_(nullptr)
      {
        assign< InputIterator >(first, last);
      }

      BiList(const list & oldList):
        headNode_(nullptr),
        tailNode_(nullptr)
      {
        *this = oldList;
      }

      BiList(list && rList):
        headNode_(nullptr),
        tailNode_(nullptr);
      {
        *this = std::move(rList);
      }

      BiList(const T & firstElement):
        headNode_(nullptr),
        tailNode_(nullptr)
      {
        createHeadTail();
        try
        {
          push_back(firstElement);
        }
        catch (...)
        {
          if (headNode_ != tailNode_) delete headNode_;
          delete tailNode_;
          throw;
        }
      }

      BiList(std::initializer_list< T > il): BiList< decltype(il.begin()) >(il.begin(), il.end())
      {}

      ~BiList() noexcept
      {
        clear();
      }

      list & operator=(const list & originalList)
      {
        assign< const_iter >(originalList.begin(), originalList.end());
        return *this;
      }

      list & operator=(list && originalList)
      {
        headNode_ = originalList.headNode_;
        tailNode_ = originalList.tailNode_;
        originalList.headNode_ = nullptr;
        originalList.tailNode_ = nullptr;
      }

      iter begin() noexcept
      {
        return iter(headNode_);
      }

      iter end() noexcept
      {
        return iter(tailNode_);
      }

      const_iter begin() const noexcept
      {
        return const_iter(headNode_);
      }

      const_iter end() const noexcept
      {
        return const_iter(tailNode_);
      }

      bool empty() const noexcept
      {
        return (headNode_ == tailNode_);
      }

      T & front()
      {
        return headNode_->data_;
      }

      T & back()
      {
        return tailNode_->last_->data_;
      }

      const T & front() const
      {
        const T & ref = headNode_->data_;
        return ref;
      }

      const T & back() const
      {
        const T & ref = tailNode_->last_->data_;
        return ref;
      }

      template < class InputIterator >
      void assign (InputIterator first, InputIterator last)
      {
        node * headCopy = headNode_;
        node * tailCopy = tailNode_;

        headNode_ = nullptr;
        tailNode_ = nullptr;

        try
        {
          createHeadTail();
        }
        catch (...)
        {
          headNode_ = headCopy;
          tailNode_ = tailCopy;
          throw;
        }
        headNode_->next_ = tailNode_;

        while (++first != last)
        {
          try
          {
            push_back(*first);
          }
          catch (...)
          {
            clear();
            headNode_ = headCopy;
            tailNode_ = tailCopy;
            throw;
          }
        }
      }

      void assign (size_t n, const T & val)
      {
        node * headCopy = headNode_;
        node * tailCopy = tailNode_;

        headNode_ = nullptr;
        tailNode_ = nullptr;

        try
        {
          createHeadTail();
        }
        catch (...)
        {
          headNode_ = headCopy;
          tailNode_ = tailCopy;
          throw;
        }
        headNode_->next_ = tailNode_;

        for (size_t i = 0; i < n; ++i)
        {
          try
          {
            push_back(val);
          }
          catch (...)
          {
            clear();
            headNode_ = headCopy;
            tailNode_ = tailCopy;
            throw;
          }
        }
      }

      void assign (std::initializer_list< T > il)
      {
        assign< decltype(il.begin()) >(il.begin(), il.end());
      }

      void push_back(const T & newElement)
      {
        if (empty()) createHeadTail();

        node * newNode = new node{T{}, tailNode_, nullptr};
        try
        {
          tailNode_->data_ = newElement;
        }
        catch (...)
        {
          delete newNode;
          throw;
        }
        tailNode_->next_ = newNode;
        tailNode_ = newNode;
      }

      void push_front(const T & newElement)
      {
        if (empty()) createHeadTail();

        node * newNode = new node{T{}, nullptr, headNode_};
        try
        {
          headNode_->data_ = newElement;
        }
        catch (...)
        {
          delete newNode;
          throw;
        }
        headNode_->last_ = newNode;
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
        node * newTail = tailNode_->last_;
        delete tailNode_;
        newTail->next_ = nullptr;
        tailNode_ = newTail;
      }

      void pop_front()
      {
        node * newHead = headNode_->next_;
        delete headNode_;
        newHead->last_ = nullptr;
        headNode_ = newHead;
      }

      iter insert(const_iter position, const T & val)
      {
        node * last = position.node_;
        node * next = position.node_->next_;
        node * newNode = new node(val, last, next);
        last.next_ = newNode;
        next.last_ = newNode;
        return iter(newNode);
      }

      iter insert(const_iter position, size_t n, const T & val)
      {
        const_iter firstIter(insert(position, val));
        const_iter iterNow = firstIter;

        for (size_t i = 1; i < n; ++i)
        {
          iterNow = insert(iterNow, val);
        }

        return firstIter;
      }

      template < class InputIterator >
      iter insert(const_iter position, InputIterator first, InputIterator last)
      {
        iter firstIter(insert(position, *first));
        const_iter iterNow = firstIter;

        while (++first != last)
        {
          iterNow = insert(iterNow, *first);
        }

        return firstIter;
      }

      iter insert(const_iter position, T && val)
      {
        return insert(position, val);
      }

      iter insert(const_iter position, std::initializer_list< T > il)
      {
        return insert< decltype(il.begin()) >(position, il.begin(), il.end());
      }

      iter erase (const_iter position)
      {
        node * deleteNode = position.node_;
        node * last = deleteNode->last_;
        node * next = deleteNode->next_;
        last->next_ = next;
        next->last_ = last;
        delete deleteNode;
        return iter(next);
      }

      iter erase (const_iter first, const_iter last)
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

      void swap(list & secondList)
      {
        iter secondHead = secondList.begin(), secondTail = secondList.end();

        secondTail.headNode_ = headNode_;
        secondList.tailNode_ = tailNode_;
        headNode_ = secondHead.node_;
        tailNode_ = secondTail.node_;
      }

      void clear() noexcept
      {
        while (headNode_)
        {
          node * next = headNode_->next_;
          delete headNode_;
          headNode_ = next;
        }
        delete headNode_;
      }

      void splice(const_iter position, list & x)
      {
        node * nodeNow = position.node_;

        nodeNow->next_->last_ = x.tailNode_;
        x.tailNode_->next_ = nodeNow->next_;

        nodeNow->next_ = x.headNode_;
        x.headNode_->last_ = nodeNow;

        x.tailNode_ = nullptr;
        x.headNode_ = nullptr;
      }

      void splice(const_iter position, list && x)
      {
        splice(position, x);
      }

      void splice(const_iter position, list & x, const_iter i)
      {
        node * nodeNow = position.node_;
        node * spliceNode = i.node_;
        node * last = spliceNode->last_;
        node * next = spliceNode->next_;

        last->next_ = next;
        next->last_ = last;

        nodeNow -> next_->last_ = i;
        i->next_ = nodeNow->next_;

        nodeNow->next_ = i;
        i->last_ = nodeNow;
      }

      void splice(const_iter position, list && x, const_iter i)
      {
        splice(position, x, i);
      }

      void splice(const_iter position, list & x, const_iter first, const_iter last)
      {
        const_iter iterNow = first;
        do
        {
          splice(position, x, iterNow);
          ++iterNow;
        } while (iterNow != last);
      }

      void splice(const_iter position, list && x, const_iter first, const_iter last)
      {
        splice(position, x, first, last);
      }

      void remove(const T & val)
      {
        iter iterNow = begin();
        while ((++iterNow) != end())
        {
          if (*iterNow == val)
          {
            erase(iterNow);
          }
        }
      }

      template < class Predicate >
      void remove_if(Predicate pred)
      {
        iter iterNow = begin();
        while ((++iterNow) != end())
        {
          if (pred(iterNow))
          {
            erase(iterNow);
          }
        }
      }

      void reverse() noexcept
      {
        iter tail = end();
        iter head = begin();
        while (tail != head)
        {
          reverseTwoNode(*tail.node_, *head.node_);
          ++head;
          if(head == tail) break;
          --tail;
        }
      }

      bool operator>(const list & rhl) const
      {
        const_iter thisIterNow = begin();
        const_iter rhlIterNow = rhl.begin();

        while ((thisIterNow != end()) && (rhlIterNow != rhl.end()))
        {
          if (*(thisIterNow++) != *(rhlIterNow++))
          {
            return (*(thisIterNow++) > *(rhlIterNow++));
          }
        }

        return ((thisIterNow != end()) && (rhlIterNow == rhl.end()));
      }

      bool operator==(const list & rhl) const
      {
        const_iter thisIterNow = begin();
        const_iter rhlIterNow = rhl.begin();

        while ((thisIterNow != end()) && (rhlIterNow != rhl.end()))
        {
          if (*(thisIterNow++) != *(rhlIterNow++)) return false;
        }

        return (thisIterNow != end()) && (rhlIterNow != rhl.end());
      }

      bool operator<(const list & rhl) const
      {
        return (rhl > *this);
      }

      bool operator!=(const list & rhl) const
      {
        return !(*this == rhl);
      }

      bool operator>=(const list & rhl) const
      {
        return (*this > rhl) || (*this == rhl);
      }

      bool operator<=(const list & rhl) const
      {
        return (*this < rhl) || (*this == rhl);
      }

    private:
      node * headNode_;
      node * tailNode_;

      void reverseTwoNode(node & first, node & second) noexcept
      {
        first.last_->next_ = second;
        first.next_->last_ = second;
        second.next_->last_ = first;
        second.last_->next_ = first;

        node* nodePointer = first.next_;
        first.next_ = second.next_;
        second.next_ = nodePointer;

        nodePointer = first.last_;
        first.last_ = second.last_;
        second.last_ = nodePointer;
      }

      void createHeadTail()
      {
        headNode_ = new node{T{}, nullptr, nullptr};
        tailNode_ = headNode_;
      }
  };
}
#endif
