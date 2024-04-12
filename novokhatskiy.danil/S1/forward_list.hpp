#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include <iostream>
#include "const_forward_list_iterators.hpp"
#include "forward_list_iterators.hpp"
#include "node.hpp"

namespace novokhatskiy
{
  template <typename T>
  class ForwardIterator;

  template <typename T>
  class ConstForwardIterator;

  template <typename T>
  class ForwardList
  {
    friend class novokhatskiy::ForwardIterator<T>;
    friend class novokhatskiy::ConstForwardIterator<T>;

  public:
    using iter = ForwardIterator<T>;
    using constIter = ConstForwardIterator<T>;
    using node_t = novokhatskiy::detail::Node<T>;
    ForwardList() : head_(nullptr)
    {
    }

    // iter before_begin()
    // {
    //   iter *before_begin = new iter(nullptr);
    //   before_begin->node_->next_ = head_;
    //   return before_begin.node_;
    // }

    ForwardList(ForwardList &&other) noexcept : head_(other.head_)
    {
      other.head_ = nullptr;
    }
    ForwardList(const ForwardList<T> &other) : head_(nullptr)
    {
      auto iter_begin = other.begin();
      auto iter_end = other.end();
      while (iter_begin != iter_end)
      {
        try
        {
          push_front(*(iter_begin++));
        }
        catch (...)
        {
          clear();
          throw;
        }
      }
    }
    ForwardList(size_t size, const T &value) : head_(nullptr)
    {
      try
      {
        for (size_t i = 0; i < size; i++)
        {
          push_front(value);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    ForwardList(std::initializer_list<T> list) : head_(nullptr)
    {
      auto iter_end = list.end();
      auto iter_begin = list.begin();
      try
      {
        while (iter_end != iter_begin)
        {
          push_front(*(--iter_end));
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    ForwardList<T> &operator=(const ForwardList<T> &other)
    {
      ForwardList<T> tmp(other);
      if (std::addressof(other) != this)
      {
        swap(tmp);
      }
      return *this;
    }

    ForwardList<T> &operator=(ForwardList<T> &&other)
    {
      ForwardList<T> tmp(std::move(other));
      if (std::addressof(other) != this)
      {
        swap(tmp);
      }
      return *this;
    }

    node_t *new_list(size_t count, const T &value)
    {
      node_t *new_node = nullptr;
      try
      {
        for (size_t i = 0; i < count; i++)
        {
          node_t *tmp = new node_t(new_node, value);
          new_node = tmp;
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
      return new_node;
    }

    node_t *new_list(T first, T last)
    {
      if (first == last)
      {
        return nullptr;
      }
      node_t *new_head = new node_t(nullptr, *(first++));
      try
      {
        node_t *tail = new_head;
        for (; first != last; ++first)
        {
          tail->next_ = new node_t(nullptr, *first);
          tail = tail->next_;
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
      return new_head;
    }

    iter begin()
    {
      return iter(head_);
    }

    constIter begin() const
    {
      return constIter(head_);
    }

    constIter cbegin() const
    {
      return constIter(head_);
    }

    iter end()
    {
      return iter();
    }

    constIter end() const
    {
      return constIter();
    }

    constIter cend() const
    {
      return constIter();
    }

    bool empty() const noexcept
    {
      return !head_;
    }
    const T &front() const
    {
      return head_->value_;
    }
    T &front()
    {
      return head_->value_;
    }

    iter insert_after(constIter pos, const T &value)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert");
      }
      auto goToPos = this->begin();
      while (pos.operator!=(goToPos))
      {
        goToPos++;
      }
      node_t *node = new node_t(value);
      node->next_ = goToPos.node_->next_;
      goToPos.node_->next_ = node;
      return goToPos++;
    }

    iter insert_after(constIter pos, size_t count, const T &value)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert");
      }
      auto goToPos = this->begin();
      while (pos.operator!=(goToPos))
      {
        goToPos++;
      }
      for (size_t i = 0; i < count; i++)
      {
        node_t *node = new node_t(value);
        node->next_ = goToPos.node_->next_;
        goToPos.node_->next_ = node;
      }
      return goToPos++;
    }

    iter insert_after(constIter pos, T &&value) noexcept
    {
      iter iter_res(pos.node_);
      node_t *new_node = new node_t(std::move(value), iter_res.node_->next_);
      iter_res.node_->next_ = new_node;
      return (++iter_res);
    }

    iter insert_after(constIter pos, std::initializer_list<T> list)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert");
      }
      auto goToPos = this->begin();
      while (pos.operator!=(goToPos))
      {
        goToPos++;
      }
      for (T value : list)
      {
        node_t *node = new node_t(value);
        node->next_ = goToPos.node_->next_;
        goToPos.node_->next_ = node;
      }
      return goToPos++;
    }

    iter erase_after(constIter pos)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert");
      }
      auto goToPos = this->begin();
      while (pos.operator!=(goToPos))
      {
        goToPos++;
      }
      if (goToPos.node_->next_)
      {
        ForwardIterator<T> next(goToPos.node_->next_->next_);
        delete goToPos.node_->next_;
        goToPos.node_->next_ = next.node_;
        return next;
      }
      else
      {
        return end();
      }
    }

    iter erase_after(constIter first, constIter last)
    {
      while (std::next(first) != last)
      {
        erase_after(first);
      }
      return iter(const_cast<detail::Node<T> *>(last.node_));
    }

    void splice_after(constIter &pos, ForwardList<T> &other)
    {
      if (pos == cend())
      {
        throw std::out_of_range("Can not insert");
      }
      node_t *next = pos.node_->next_;
      pos.node_->next_ = other.head_;
      while (other.head_)
      {
        other.head_ = other.head_->next_;
        pos.node_ = pos.node_->next_;
        pos.node_->next_ = other.head_;
      }
      pos.node_->next_ = next;
      other.head_ = nullptr;
    }

    void splice_after(constIter pos, ForwardList<T> &&other)
    {
      auto iter_curr = other.cbegin();
      auto iter_end = other.cend();
      while (iter_curr != iter_end)
      {
        insert_after(pos, std::move(*iter_curr));
        ++iter_curr;
        ++pos;
      }
      other.clear();
    }

    void splice_after(constIter pos, ForwardList<T> &other, constIter iter)
    {
      splice_after(pos, ForwardList<T>(other), iter);
    }

    void splice_after(constIter pos, ForwardList<T> &&other, constIter iter)
    {
      if (pos == std::next(iter) || pos == iter)
      {
        return;
      }
      splice_after(pos, std::move(other), other.cend());
    }

    void splice_after(constIter pos, ForwardList<T> &other, constIter first, constIter last)
    {
      splice_after(pos, T(other), first, last);
    }

    void splice_after(constIter pos, ForwardList<T> &&other, constIter first, constIter last)
    {
      auto curr_iter = first;
      auto iter_end = last;
      while (std::next(first) != iter_end)
      {
        insert_after(pos, std::move(*std::next(curr_iter)));
        other.erase_after(curr_iter);
        ++pos;
      }
    }
    void push_front(const T &value)
    {
      node_t *ptr = new node_t(value);
      ptr->next_ = head_;
      head_ = ptr;
    }
    void push_front(T &value)
    {
      node_t *ptr = new node_t(value);
      ptr->next_ = head_;
      head_ = ptr;
    }

    void push_front(T &&value)
    {
      node_t *ptr = new node_t(std::move(value));
      ptr->next_ = head_;
      head_ = ptr;
    }

    void pop_front()
    {
      if (empty())
      {
        std::cerr << "The forward_list is empty\n";
        return;
      }
      node_t *temp = head_;
      head_ = head_->next_;
      delete temp;
    }
    size_t size() const
    {
      size_t count{};
      if (head_ == nullptr)
      {
        return 0;
      }
      node_t *curr = head_;
      while (curr)
      {
        count++;
        curr = curr->next_;
      }
      return count;
    }
    void clear()
    {
      while (!empty())
      {
        pop_front();
      }
    }
    void assign(size_t count, const T &value)
    {
      node_t *otherHead = nullptr;
      try
      {
        for (size_t i = 0; i < count; i++)
        {
          node_t *temp = new node_t(value);
          temp->next_ = otherHead;
          otherHead = temp;
        }
      }
      catch (const std::bad_alloc &)
      {
        while (head_)
        {
          node_t *temp = head_->next_;
          delete head_;
          head_ = temp;
        }
      }
      head_ = otherHead;
    }

    void assign(std::initializer_list<T> list)
    {
      try
      {
        clear();
        for (T data : list)
        {
          push_front(data);
        }
        reverse();
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }

    void assign(iter first, iter last)
    {
      clear();
      while (first != last)
      {
        push_front(*first++);
      }
      reverse();
    }

    void swap(ForwardList<T> &other)
    {
      std::swap(head_, other.head_);
    }
    void reverse()
    {
      if (!head_)
      {
        return;
      }
      node_t *result = head_;
      node_t *temp = head_->next_;
      result->next_ = nullptr;
      while (temp)
      {
        node_t *prev = temp->next_;
        temp->next_ = result;
        result = temp;
        temp = prev;
      }
      head_ = result;
    }
    size_t remove(const T &value)
    {
      return remove_if([value](const T &val) -> bool
                       { return val = value; });
    }
    template <typename P>
    size_t remove_if(P predicate)
    {
      size_t removedElement{};
      node_t *curr = head_;
      node_t *prev = nullptr;
      while (curr)
      {
        if (predicate(curr->value_))
        {
          if (head_ == curr)
          {
            prev->next_ = curr->next_;
            delete curr;
          }
          else
          {
            head_ = curr->next_;
          }
          node_t *temp = curr;
          curr = curr->next_;
          ++removedElement;
          delete temp;
        }
        else
        {
          prev = curr;
          curr = curr->next_;
        }
      }
      return removedElement;
    }

    bool operator==(ForwardList<T> &other) const
    {
      size_t maxPossibleSize = std::min(this->size(), other.size());
      node_t *curr = head_;
      node_t *otherHead = other.head_;
      for (size_t i = 0; i < maxPossibleSize; i++)
      {
        if (curr->value_ != otherHead->value_)
        {
          return false;
        }
        curr = curr->next_;
        otherHead = otherHead->next_;
      }
      return true;
    }
    bool operator!=(ForwardList<T> &other) const
    {
      return !(*this == other);
    }
    bool operator<(const ForwardList<T> &other) const
    {
      size_t maxPossibleSize = std::min(this->size(), other.size());
      node_t *curr = head_;
      node_t *otherHead = other.head_;
      for (size_t i = 0; i < maxPossibleSize; i++)
      {
        if (curr->value_ != otherHead->value_)
        {
          return curr->value_ < otherHead->value_;
        }
        curr = curr->next_;
        otherHead = otherHead->next_;
      }
      return false;
    }

    bool operator>(const ForwardList<T> &other) const
    {
      return (other < *this);
    }
    bool operator<=(const ForwardList<T> &other) const
    {
      return (*this < other || *this == other);
    }
    bool operator>=(const ForwardList<T> &other) const
    {
      return (other < *this || *this == other);
    }
    void print()
    {
      while (head_ != nullptr)
      {
        std::cout << head_->value_ << " ";
        head_ = head_->next_;
      }
      std::cout << std::endl;
    }
    ~ForwardList()
    {
      clear();
    }

  private:
    detail::Node<T> *head_;
    ForwardList(const T &value) : head_(new detail::Node<T>)
    {
      for (auto i = begin(); i < end(); i++)
      {
        push_front(value);
      }
    }
  };
}

#endif
