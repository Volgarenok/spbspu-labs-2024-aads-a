#ifndef BIDIRECTIONAL_NODE_HPP
#define BIDIRECTIONAL_NODE_HPP

namespace namestnikov
{
  namespace detail
  {
    struct BaseListNode
    {
      BaseListNode * next;
      BaseListNode * prev;
      BaseListNode():
        next(nullptr),
        prev(nullptr)
      {}
      virtual ~BaseListNode() = default;
    };

    template< class T >
    struct ListNode: BaseListNode
    {
      T data;
      ListNode(const T& newData):
        BaseListNode(),
        data(newData)
      {}
    };
  }
}

#endif
