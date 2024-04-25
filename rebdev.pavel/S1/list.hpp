#ifndef LIST_HPP
#define LIST_HPP

#include "BidirectionalIterator.hpp"
#include "constBidirectionalIterator.hpp"

namespace rebdev
{
  template < class T >

  class BiList
  {
    using node = BiListNode< T >;

    public:
      using iterator = BidirectionalIterator< T >;
      using const_iterator = ConstBidirectionalIterator< T >;

      BiList():
        headNode_(new node{T{}, nullptr, nullptr}),
        tailNode_(nullptr),
        size_(0)
      {
        tailNode_ = headNode_;
      }
      BiList(size_t n, const T & val):
        headNode_(new node{T{}, nullptr, nullptr}),
        tailNode_(nullptr),
        size_(0)
      {
        tailNode_ = headNode_;
        assign(n, val);
      }
      BiList(size_t n):
        BiList(n, T{})
      {}
      BiList(const BiList & list):
        headNode_(new node{T{}, nullptr, nullptr}),
        tailNode_(nullptr),
        size_(0)
      {
        tailNode_ = headNode_;
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
            throw;
          }
          ++it;
        }
      }
      BiList(BiList && list):
        headNode_(list.headNode_),
        tailNode_(list.tailNode_),
        size_(0)
      {
        size_ = list.size_;

        list.headNode_ = nullptr;
        list.tailNode_ = nullptr;
      }
      ~BiList() noexcept
      {
        clear();
        delete headNode_;
      }

      BiList & operator=(const BiList & list)
      {
        node * headCopy = headNode_;
        node * tailCopy = tailNode_;
        size_t sizeCopy = size_;
        try
        {
          *this = BiList(list);
        }
        catch (...)
        {
          delete headNode_;
          headNode_ = headCopy;
          tailNode_ = tailCopy;
          size_ = sizeCopy;
          throw;
        }

        node * newHeadCopy = headNode_;
        node * newTailCopy = tailNode_;
        sizeCopy = size_;

        headNode_ = headCopy;
        tailNode_ = tailCopy;
        clear();
        delete headNode_;

        headNode_ = newHeadCopy;
        tailNode_ = newTailCopy;
        size_ = sizeCopy;

        return *this;
      }
      BiList & operator=(BiList && list)
      {
        clear();
        delete headNode_;
        *this = BiList(std::move(list));
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

      void assign(size_t n, const T & val)
      {
        node * headCopy = headNode_;
        node * tailCopy = tailNode_;
        size_t sizeCopy = size_;

        *this = BiList();

        for (size_t i = 0; i < n; ++i)
        {
          try
          {
            push_back(val);
          }
          catch (...)
          {
            clear();
            delete headNode_;
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
        delete headNode_;
        headNode_ = newHeadCopy;
        tailNode_ = newTailCopy;
        size_ = n;
      }
      void push_front(const T & val)
      {
        push_front(new node{val, nullptr, headNode_});
      }
      void push_front(T && val)
      {
        push_front(new node{std::move(val), nullptr, headNode_});
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
        push_back(new node{val, tailNode_->last, tailNode_});
      }
      void push_back(T && val)
      {
        push_back(new node{std::move(val), tailNode_->last, tailNode_});
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
        std::swap< BiList< T > >(*this, x);
      }
      void clear() noexcept
      {
        while (headNode_ != tailNode_)
        {
          node * nextNode = headNode_->next;
          delete headNode_;
          headNode_ = nextNode;
        }
      }

      void remove(const T & val)
      {
        remove_if(
        [&](const T & current)
        {
          return (current == val);
        });
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

      void push_back(node * n)
      {
        if (tailNode_ == nullptr)
        {
          *this = BiList();
        }
        if ((tailNode_->last) != nullptr)
        {
          tailNode_->last->next = n;
        }
        else
        {
          headNode_ = n;
        }
        tailNode_->last = n;
        ++size_;
      }
      void push_front(node * n)
      {
        if (headNode_ == nullptr)
        {
          *this = BiList();
        }
        headNode_->last = n;
        headNode_ = n;
        ++size_;
      }
  };
}

#endif
