#ifndef LIST_HPP
#define LIST_HPP

#include "BidirectionalIterator.hpp"
#include "constBidirectionalIterator.hpp"

namespace rebdev
{
  template < class T >

  class BiList
  {
    using node = biListNode< T >;

    public:
      using iterator = BidirectionalIterator< T >;
      using const_iterator = ConstBidirectionalIterator< T >;

      BiList():
        headNode_(nullptr),
        tailNode_(nullptr),
        size_(0)
      {
        createHeadTail();
      }
      BiList(size_t n, const T & val)
      {
        createHeadTail();
        assign(n, val);
      }
      BiList(size_t n): BiList(n, T{}){};
      BiList(const BiList & list):
        headNode_(nullptr),
        tailNode_(nullptr),
        size_(0)
      {
        *this = list;
      }
      BiList(BiList && list):
        headNode_(nullptr),
        tailNode_(nullptr),
        size_(0)
      {
        *this = std::move(list);
      }
      ~BiList() noexcept
      {
        clear();
      }

      BiList & operator=(const BiList & list)
      {
        node * headCopy = headNode_;
        node * tailCopy = tailNode_;
        size_t sizeCopy = size_;

        createHeadTail();
        const_iterator it = list.cbegin();

        while (it != list.cend())
        {
          try
          {
            push_back(*it);
          }
          catch (...)
          {
            clear();
            headNode_ = headCopy;
            tailNode_ = tailCopy;
            size_ = sizeCopy;
            throw;
          }
          ++it;
        }

        node * newHeadCopy = headNode_;
        node * newTailCopy = tailNode_;
        sizeCopy = size_;

        headNode_ = headCopy;
        tailNode_ = tailCopy;
        clear();

        headNode_ = newHeadCopy;
        tailNode_ = newTailCopy;
        size_ = sizeCopy;

        return *this;
      }
      BiList & operator=(BiList && list)
      {
        clear();

        headNode_ = list.headNode_;
        tailNode_ = list.tailNode_;
        size_ = list.size_;

        list.headNode_ = nullptr;
        list.tailNode_ = nullptr;

        return *this;
      }

      iterator begin()
      {
        return iterator(headNode_);
      }
      const_iterator cbegin() const
      {
        return const_iterator(headNode_);
      }
      iterator end()
      {
        return iterator(tailNode_);
      }
      const_iterator cend() const
      {
        return const_iterator(tailNode_);
      }

      bool empty() const noexcept
      {
        return (headNode_ == tailNode_);
      }
      size_t size() const noexcept
      {
        return size_;
      }

      T & front()
      {
        return headNode_->data;
      }
      T & back()
      {
        return tailNode_->last->data;
      }
      const T & front() const
      {
        const T & ref = headNode_->data;
        return ref;
      }
      const T & back() const
      {
        const T & ref = tailNode_->last->data;
        return ref;
      }

      void assign (size_t n, const T & val)
      {
        node * headCopy = headNode_;
        node * tailCopy = tailNode_;
        size_t sizeCopy = size_;

        createHeadTail();

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
            size_ = sizeCopy;
            throw;
          }
        }

        node * newHeadCopy = headNode_;
        node * newTailCopy = tailNode_;

        headNode_ = headCopy;
        tailNode_ = tailCopy;
        clear();

        headNode_ = newHeadCopy;
        tailNode_ = newTailCopy;
        size_ = n;
      }
      void push_front(const T & val)
      {
        if (headNode_ == nullptr)
        {
          createHeadTail();
        }
        node * newNode = new node{val, nullptr, headNode_};
        headNode_->last = newNode;
        headNode_ = newNode;
        ++size_;
      }
      void push_front(T && val)
      {
        if (headNode_ == nullptr)
        {
          createHeadTail();
        }
        node * newNode = new node{std::move(val), nullptr, headNode_};
        headNode_->last = newNode;
        headNode_ = newNode;
        ++size_;
      }
      void pop_front()
      {
        node * headCopy = headNode_->next;
        delete headNode_;
        headNode_ = headCopy;
        --size_;
      }
      void push_back(const T & val)
      {
        if (tailNode_ == nullptr)
        {
          createHeadTail();
        }
        node * newNode = new node{val, tailNode_->last, tailNode_};
        if ((tailNode_->last) != nullptr)
        {
          tailNode_->last->next = newNode;
        }
        else
        {
          headNode_ = newNode;
        }
        tailNode_->last = newNode;
        ++size_;
      }
      void push_back(T && val)
      {
        if (tailNode_ == nullptr)
        {
          createHeadTail();
        }
        node * newNode = new node{std::move(val), tailNode_->last, tailNode_};
        if ((tailNode_->last) != nullptr)
        {
          tailNode_->last->next = newNode;
        }
        else
        {
          headNode_ = newNode;
        }
        tailNode_->last = newNode;
        ++size_;
      }
      void pop_back()
      {
        node * tailCopy = tailNode_->last->last;
        delete tailCopy->last;
        tailNode_->last = tailCopy;
        tailCopy->next = tailNode_;
        --size_;
      }
      void swap(BiList & x)
      {
        node * thisHeadCopy = headNode_;
        node * thisTailCopy = tailNode_;
        size_t thisSizeCopy = size_;

        headNode_ = x.headNode_;
        tailNode_ = x.tailNode_;
        size_ = x.size_;

        x.headNode_ = thisHeadCopy;
        x.tailNode_ = thisTailCopy;
        x.size_ = thisSizeCopy;
      }
      void clear() noexcept
      {
        while (headNode_ != tailNode_)
        {
          node * nextNode = headNode_->next;
          delete headNode_;
          headNode_ = nextNode;
        }
        delete headNode_;

        headNode_ = nullptr;
        tailNode_ = nullptr;
        size_ = 0;
      }

      void remove(const T & val)
      {
        remove_if([& val](const T & valNow)
        {
          return (valNow == val);
        }
        );
      }
      template < class Predicate >
      void remove_if(Predicate pred)
      {
        iterator it = begin();
        while (it != end())
        {
          if (pred(*it))
          {
            node * lastNode = it.node_->last;
            node * nextNode = it.node_->next;
            delete it.node_;

            if (lastNode == nullptr)
            {
              headNode_ = nextNode;
            }
            else
            {
              lastNode->next = nextNode;
            }
            nextNode->last = lastNode;
            it = iterator(nextNode);
            --size_;
          }
          else
          {
            ++it;
          }
        }
      }
    private:
      node * headNode_;
      node * tailNode_;
      size_t size_;

      void createHeadTail()
      {
        headNode_ = new node{T{}, nullptr, nullptr};
        tailNode_ = headNode_;
      }
  };
}

#endif
