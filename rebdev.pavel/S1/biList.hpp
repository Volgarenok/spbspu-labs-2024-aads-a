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
        tailNode_(nullptr),
        size_(0)
      {
        createHeadTail();
      }

      BiList(size_t n): BiList(n, T{})
      {}

      BiList(size_t n, const T & val):
        headNode_(nullptr),
        tailNode_(nullptr),
        size_(n)
      {
        assign(n, val);
      }

      template < class InputIterator >
      BiList (InputIterator first, InputIterator last):
        headNode_(nullptr),
        tailNode_(nullptr),
        size_(0)
      {
        assign< InputIterator >(first, last);
      }

      BiList(const list & oldList):
        headNode_(nullptr),
        tailNode_(nullptr),
        size_(oldList.size_)
      {
        *this = oldList;
      }

      BiList(list && rList):
        headNode_(rList.headNode_),
        tailNode_(rList.tailNode_),
        size_(rList.size_)
      {
        rList.headNode_ = nullptr;
        rList.tailNode_ = nullptr;
      }

      BiList(const T & firstElement):
        headNode_(nullptr),
        tailNode_(nullptr),
        size_(0)
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
        size_ = originalList.size_;

        originalList.headNode_ = nullptr;
        originalList.tailNode_ = nullptr;

        return *this;
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
        return (size_ == 0);
      }

      size_t size() const noexcept
      {
        return size_;
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

        while ((first++) != last)
        {
          try
          {
            push_back(*first);
            ++size_;
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

        size_ = n;
      }

      void assign(std::initializer_list< T > il)
      {
        assign< decltype(il.begin()) >(il.begin(), il.end());
      }

      void push_back(const T & newElement)
      {
        if (headNode_ == nullptr) createHeadTail();

        node * newNode = new node{newElement, tailNode_->last_, tailNode_};

        if (tailNode_->last_ != nullptr)
        {
          tailNode_->last_->next_ = newNode;
        }

        tailNode_->last_ = newNode;

        if (tailNode_ == headNode_)
        {
          headNode_ = newNode;
        }

        ++size_;
      }

      void push_front(const T & newElement)
      {
        if (headNode_ == nullptr) createHeadTail();

        node * newNode = new node{newElement, nullptr, headNode_};

        headNode_->last_ = newNode;
        headNode_ = newNode;

        ++size_;
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
        node * preLast = tailNode_->last_->last_;

        delete tailNode_->last_;

        if (preLast != nullptr)
        {
          preLast->next_ = tailNode_;
          tailNode_->last_ = preLast;
        }
        else
        {
          tailNode_->last_ = nullptr;
        }
        --size_;
      }

      void pop_front()
      {
        node * newHead = headNode_->next_;
        delete headNode_;
        newHead->last_ = nullptr;
        headNode_ = newHead;
        --size_;
      }

      iter insert(const_iter position, const T & val)
      {
        node * lastNode = position.node_;
        node * nextNode = position.node_->next_;
        node * newNode = new node(val, lastNode, nextNode);
        lastNode->next_ = newNode;
        nextNode->last_ = newNode;
        ++size_;

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

        while (first != last)
        {
          ++first;
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
        node * lastNode = deleteNode->last_;
        node * nextNode = deleteNode->next_;

        if (lastNode != nullptr)
        {
          lastNode->next_ = nextNode;
        }
        if (nextNode != nullptr)
        {
          nextNode->last_ = lastNode;
        }

        delete deleteNode;
        --size_;

        return iter(nextNode);
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
        size_t secondSize = secondList.size_;

        secondList.headNode_ = headNode_;
        secondList.tailNode_ = tailNode_;
        secondList.size_ = size_;

        headNode_ = secondHead.node_;
        tailNode_ = secondTail.node_;
        size_ = secondSize;
      }

      void clear() noexcept
      {
        while (headNode_ != tailNode_)
        {
          node * next = headNode_->next_;
          delete headNode_;
          headNode_ = next;
        }

        size_ = 0;
        delete headNode_;
      }

      void splice(const_iter position, list & x)
      {
        iter beg = x.begin();
        const_iter iterNow = position;

        while (beg != x.end())
        {
          insert(iterNow, *beg);

          ++iterNow;
          ++beg;
        }

        x.clear();
      }

      void splice(const_iter position, list && x)
      {
        splice(position, x);
      }

      void splice(const_iter position, list & x, const_iter i)
      {
        insert(position, *i);
        x.erase(i);
      }

      void splice(const_iter position, list && x, const_iter i)
      {
        splice(position, x, i);
      }

      void splice(const_iter position, list & x, const_iter first, const_iter last)
      {
        const_iter iterNow = first;
        const_iter pos = position;

        while (iterNow != last)
        {
          splice(pos, x, iterNow);
          ++pos;
          ++iterNow;
        }
      }

      void splice(const_iter position, list && x, const_iter first, const_iter last)
      {
        splice(position, x, first, last);
      }

      void remove(const T & val)
      {
        iter iterNow = begin();

        while (iterNow++ != end())
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
        while (iterNow++ != end())
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
      size_t size_;

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
