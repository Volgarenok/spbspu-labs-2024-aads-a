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
    using iter = BidirectionalIterator< T >;
    using c_iter = ConstBidirectionalIterator< T >;

    public:
      BiList() = default;
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
      ~BiList noexcept
      {
        clear();
      }

      BiList & operator=(const BiList & list)
      {
        node * headCopy = headNode_;
        node * tailCopy = tailNode_;

        createHeadTail();
        c_iter it = list.begin();

        while (it != list.end())
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
            throw;
          }
          ++size_;
          ++it;
        }

        return *this;
      }
      BiList & operator=(BiList && list)
      {
        headNode_ = list.headNode_;
        tailNode_ = list.tailNode_;
        size_ = list.size_;

        list.headNode_ = nullptr;
        list.tailNode_ = nullptr;

        return *this;
      }

    private:
      node * headNode_;
      node * tailNode_;
      size_t size_;

      void createHeadTail()
      {
        headNode_ = new node{T{}, nullptr, nullptr};
        tailNode_ = headNode;
      }
  }
}

#endif
