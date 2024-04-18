#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include <stdexcept>
#include <algorithm>
#include <type_traits>
#include <initializer_list>
#include <cstddef>

namespace zaitsev
{
  template< typename T >
  class ForwardList
  {
    struct Node
    {
      T value_;
      Node* next_;
      Node(const Node& other):
        value_(other.value_),
        next_(nullptr)
      {}
      template< class ... Args >
      explicit Node(Node* next, Args&&... args):
        value_(std::forward< Args >(args)...),
        next_(next)
      {}
    };
    void freeNodes(Node* head_node) noexcept
    {
      while (head_node)
      {
        Node* temp = head_node->next_;
        delete head_node;
        head_node = temp;
      }
    }

    template < class Compare >
    Node* merge(Node* first, Node* second, Compare cmp) noexcept
    {
      if (!first || !second)
      {
        return first ? first : second;
      }
      Node* res = nullptr;
      Node* res_tail = nullptr;
      res_tail = res = cmp(first->value_, second->value_) ? first : second;
      res == first ? (first = first->next_) : (second = second->next_);

      while (first || second)
      {
        if (first && second)
        {
          res_tail->next_ = cmp(first->value_, second->value_) ? first : second;
          res_tail->next_ == first ? (first = first->next_) : (second = second->next_);
        }
        else
        {
          res_tail->next_ = first ? first : second;
          break;
        }
        res_tail = res_tail->next_;
      }
      return  res;
    }

    template< bool IsConst >
    class BaseIterator
    {
      template< bool U > friend class BaseIterator;
      template< typename U > friend class ForwardList;
      using prt_t = std::conditional_t< IsConst, const T*, T* >;
      using ref_t = std::conditional_t< IsConst, const T&, T& >;
      using node_t = Node*;
    private:
      node_t node_;

    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = std::conditional_t< IsConst, const T*, T* >;
      using reference = std::conditional_t< IsConst, const T&, T& >;

      BaseIterator():
        node_(nullptr)
      {}
      explicit BaseIterator(node_t node):
        node_(node)
      {}
      template<bool cond = IsConst, std::enable_if_t<cond, bool> = true >
      BaseIterator(const BaseIterator<!cond>& other):
        node_(other.node_)
      {}
      BaseIterator& operator++()
      {
        node_ = node_->next_;
        return *this;
      }
      BaseIterator operator++(int)
      {
        BaseIterator copy = *this;
        node_ = node_->next_;
        return copy;
      }
      ref_t operator*() const
      {
        return node_->value_;
      }
      prt_t operator->() const
      {
        return std::addressof(node_->value_);
      }
      bool operator!=(const BaseIterator& other) const
      {
        return node_ != other.node_;
      }
      bool operator==(const BaseIterator& other) const
      {
        return node_ == other.node_;
      }
    };

    Node* new_list(size_t count, const T& value)
    {
      Node* new_head = nullptr;
      try
      {
        for (size_t i = 0; i < count; ++i)
        {
          Node* temp = new Node(new_head, value);
          new_head = temp;
        }
      }
      catch (...)
      {
        freeNodes(new_head);
        throw;
      }
      return new_head;
    }
    template< class InputIt >
    Node* new_list(InputIt begin, InputIt end)
    {
      if (begin == end)
      {
        return nullptr;
      }
      Node* new_head = new Node(nullptr, *(begin++));
      try
      {
        Node* new_tail = new_head;
        for (; begin != end; ++begin)
        {
          new_tail->next_ = new Node(nullptr, *begin);
          new_tail = new_tail->next_;
        }
      }
      catch (...)
      {
        freeNodes(new_head);
        throw;
      }
      return new_head;
    }

    Node* head_;

  public:
    using iterator = BaseIterator< false >;
    using const_iterator = BaseIterator< true >;
    ForwardList():
      head_(nullptr)
    {}
    ForwardList(const ForwardList& other):
      head_(nullptr)
    {
      head_ = new_list(other.cbegin(), other.cend());
    }
    ForwardList(ForwardList&& other):
      head_(other.head_)
    {
      other.head_ = nullptr;
    }
    ForwardList(const_iterator begin, const_iterator end):
      head_(nullptr)
    {
      head_ = new_list(begin, end);
    }
    ForwardList(std::initializer_list< T > init_list):
      head_(nullptr)
    {
      head_ = new_list(init_list.begin(), init_list.end());
    }
    ForwardList(size_t count, const T& value):
      head_(nullptr)
    {
      head_ = new_list(count, value);
    }
    ~ForwardList()
    {
      freeNodes(head_);
    }

    friend bool operator==(const ForwardList& first, const ForwardList& second)
    {
      return std::equal(first.cbegin(), first.cend(), second.cbegin(), second.cend());
    }
    friend bool operator!=(const ForwardList& first, const ForwardList& second)
    {
      return !std::equal(first.cbegin(), first.cend(), second.cbegin(), second.cend());
    }
    friend bool operator<(const ForwardList& first, const ForwardList& second)
    {
      return std::lexicographical_compare(first.cbegin(), first.cend(), second.cbegin(), second.cend());
    }
    friend bool operator>=(const ForwardList& first, const ForwardList& second)
    {
      return !std::lexicographical_compare(first.cbegin(), first.cend(), second.cbegin(), second.cend());
    }
    friend bool operator>(const ForwardList& first, const ForwardList& second)
    {
      return std::lexicographical_compare(second.cbegin(), second.cend(), first.cbegin(), first.cend());
    }
    friend bool operator<=(const ForwardList& first, const ForwardList& second)
    {
      return !std::lexicographical_compare(second.cbegin(), second.cend(), first.cbegin(), first.cend());
    }

    iterator begin()
    {
      return iterator(head_);
    }
    iterator end()
    {
      return iterator();
    }
    const_iterator cbegin() const
    {
      return const_iterator(head_);
    }
    const_iterator cend() const
    {
      return const_iterator();
    }

    bool empty() const noexcept
    {
      return !head_;
    }
    T& front()
    {
      return head_->value_;
    }
    const T& front() const
    {
      return head_->value_;
    }
    void push_front(const T& value)
    {
      emplace_front(value);
    }
    void push_front(T&& value)
    {
      emplace_front(std::move(value));
    }
    void pop_front()
    {
      if (!head_)
      {
        throw std::runtime_error("List is empty");
      }
      Node* temp = head_;
      head_ = head_->next;
      delete head_;
    }
    void assign(size_t count, const T& value)
    {
      Node* new_head = new_list(count, value);
      freeNodes(head_);
      head_ = new_head;
    }
    void assign(const_iterator begin, const_iterator end)
    {
      Node* new_head = new_list(begin, end);
      freeNodes(head_);
      head_ = new_head;
    }
    void assign(std::initializer_list< T > init_list)
    {
      Node* new_head = new_list(init_list.begin(), init_list.end());
      freeNodes(head_);
      head_ = new_head;
    }
    void clear() noexcept
    {
      freeNodes(head_);
      head_ = nullptr;
    }
    void swap(ForwardList& other)
    {
      std::swap(head_, other.head_);
    }

    size_t remove(const T& value)
    {
      return remove_if(
        [&value](const T& val) -> bool
        {
          return val == value;
        }
      );
    }
    template< class UnaryPredicate >
    size_t remove_if(UnaryPredicate p)
    {
      size_t removed = 0;
      Node* prev = nullptr;
      Node* cur = head_;
      while (cur)
      {
        if (p(cur->value_))
        {
          Node* temp = cur;
          if (prev)
          {
            prev->next_ = cur->next_;
          }
          else
          {
            head_ = cur->next_;
          }
          cur = cur->next_;
          delete temp;
          ++removed;
        }
        else
        {
          prev = cur;
          cur = cur->next_;
        }
      }
      return removed;
    }
    iterator insert_after(const_iterator pos, const T& value)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Iterator is out of range");
      }
      Node* new_node = new Node(value);
      new_node->next_ = pos.node_->next_;
      pos.node_->next_ = new_node;
      return ++iterator(pos.node_);
    }
    iterator insert_after(const_iterator pos, size_t count, const T& value)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Iterator is out of range");
      }
      if (!count)
      {
        return iterator(pos.node_);
      }
      Node* next = pos.node_->next_;
      Node* new_range = new_list(count, value);
      pos.node_->next_ = new_range;
      std::advance(pos, count);
      pos.node_->next_ = next;

      return iterator(pos.node_);
    }
    iterator insert_after(const_iterator pos, T&& value)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Iterator is out of range");
      }
      Node* new_node = new Node(std::move(value));
      new_node->next_ = pos.node_->next_;
      pos.node_->next_ = new_node;

      return ++iterator(pos.node_);
    }
    template< class InputIt,
        std::enable_if_t< std::is_same< typename std::iterator_traits< InputIt >::value_type, T >::value, bool >
        = true >
    iterator insert_after(const_iterator pos, InputIt first, InputIt last)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Iterator is out of range");
      }
      if (first == last)
      {
        return iterator(pos.node_);
      }
      Node* next = pos.node_->next_;
      Node* new_range = new_list(first, last);
      pos.node_->next_ = new_range;
      iterator last_added(new_range);
      while (last_added.node_->next_ != nullptr)
      {
        ++last_added;
      }
      last_added.node_->next_ = next;
      return last_added;
    }
    iterator insert_after(const_iterator pos, std::initializer_list< T > init_list)
    {
      return insert_after(pos,init_list.begin(),init_list.end());
    }
    iterator erase_after(const_iterator pos)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Iterator is out of range");
      }
      if (pos.node_->next_)
      {
        iterator ret(pos.node_->next_->next_);
        delete pos.node_->next_;
        pos.node_->next_ = ret.node_;
        return ret;
      }
      else
      {
        return end();
      }
    }
    iterator erase_after(const_iterator first, const_iterator last)
    {
      if (first == end())
      {
        return end();
      }
      const_iterator temp = first;
      for (; temp.node_->next_ != last.node_; ++temp);
      temp.node_->next_ = nullptr;
      freeNodes(first.node_->next_);
      first.node_->next_ = last.node_;
      return iterator(last.node_);
    }
    void splice_after(const_iterator pos, ForwardList& other)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Iterator is out of range");
      }
      if (!other.head_)
      {
        return;
      }

      Node* temp = pos.node_->next_;
      pos.node_->next_ = other.head_;
      for (; pos.node_->next_; ++pos);
      pos.node_->next_ = temp;
      other.head_ = nullptr;
    }
    template< class... Args >
    void emplace_front(Args&&... args)
    {
      Node* new_head = new Node(head_, std::forward< Args >(args)...);
      head_ = new_head;
    }
    template< class... Args >
    iterator emplace_after(const_iterator pos, Args&&... args)
    {
      pos.node_->next_ = new Node(pos.node_->next_, std::forward< Args >(args)...);
      return iterator((++pos).node_);
    }

    void reverse()
    {
      if (!head_)
      {
        return;
      }
      Node* new_head = head_;
      Node* tail = head_->next_;
      new_head->next_ = nullptr;
      while (tail)
      {
        Node* temp = tail->next_;
        tail->next_ = new_head;
        new_head = tail;
        tail = temp;
      }
      head_ = new_head;
    }
    template< class Compare >
    void merge(ForwardList& other, Compare cmp)
    {
      head_ = merge(head_, other.head_, cmp);
      other.head_ = nullptr;
    }
    void merge(ForwardList& other)
    {
      merge(other, std::less< T >());
    }
    size_t unique()
    {
      if (!head_)
      {
        return 0;
      }
      size_t removed = 0;
      Node* cur = head_;
      while (cur->next_)
      {
        if (cur->value_ == cur->next_->value_)
        {
          Node* temp = cur->next_;
          cur->next_ = cur->next_->next_;
          delete temp;
          ++removed;
        }
        else
        {
          cur = cur->next_;
        }
      }
      return removed;
    }
    template< class Compare >
    void sort(Compare cmp)
    {
      if (!head_ || !head_->next_)
      {
        return;
      }
      size_t sz = 0;
      const Node* cur = head_;
      while (cur)
      {
        ++sz;
        cur = cur->next_;
      }
      for (size_t ord_sec_sz = 1; ord_sec_sz < sz; ord_sec_sz *= 2)
      {
        Node* global_head = nullptr;
        Node* head_tail = nullptr;
        Node* global_tail = head_;
        while (global_tail)
        {
          Node* sec1_head = global_tail;
          Node* sec1_tail = global_tail;
          global_tail = global_tail->next_;
          sec1_tail->next_ = nullptr;
          for (size_t j = 1; j < ord_sec_sz && global_tail; ++j)
          {
            sec1_tail->next_ = global_tail;
            sec1_tail = sec1_tail->next_;
            global_tail = global_tail->next_;
            sec1_tail->next_ = nullptr;
          }
          if (!global_tail)
          {
            !head_tail ? global_head = sec1_head : head_tail->next_ = sec1_head;
            break;
          }
          Node* sec2_head = global_tail;
          Node* sec2_tail = global_tail;
          global_tail = global_tail->next_;
          sec2_tail->next_ = nullptr;
          for (size_t j = 1; j < ord_sec_sz && global_tail; ++j)
          {
            sec2_tail->next_ = global_tail;
            sec2_tail = sec2_tail->next_;
            global_tail = global_tail->next_;
            sec2_tail->next_ = nullptr;
          }
          if (!global_head)
          {
            global_head = merge(sec1_head, sec2_head, cmp);
          }
          else
          {
            head_tail->next_ = merge(sec1_head, sec2_head, cmp);
          }
          head_tail = (cmp(sec1_tail->value_, sec2_tail->value_) ? sec2_tail : sec1_tail);
        }
        head_ = global_head;
      }
    }
    void sort()
    {
      sort(std::less< T >{});
    }
  };
}
#endif
