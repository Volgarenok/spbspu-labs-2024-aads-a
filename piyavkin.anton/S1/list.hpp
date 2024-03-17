#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <limits>
#include <stdexcept>
#include "node.hpp"
#include "listiterator.hpp"

namespace piyavkin
{
  template< class T >
  class List
  {
  public:
    List():
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}
    List(const T& value, size_t count):
      List()
    {
      try
      {
        for (size_t i = 0; i < count; ++i)
        {
          push_back(value);
        }
      }
      catch (const std::exception& e)
      {
        clear();
        throw;
      }
    }
    List(ListIterator< T > start, ListIterator< T > finish):
      List()
    {
      try
      {
        while (start != finish)
        {
          push_back(*start++);
        }
      }
      catch (const std::exception& e)
      {
        clear();
        throw;
      }
    }
    List(std::initializer_list< T > il):
      List()
    {
      try
      {
        auto it = il.begin();
        while (it != il.end())
        {
          push_back(*it++);
        }
      }
      catch (const std::exception& e)
      {
        clear();
        throw;
      }
    }
    List(const List< T >& rhs):
      List()
    {
      try
      {
        Node< T >* node = rhs.head_;
        while (size_ != rhs.size_)
        {
          push_back(node->value_);
          node = node->next_;
        }
      }
      catch (const std::exception& e)
      {
        for (size_t j = 0; j < size_; ++j)
        {
          pop_front();
        }
        throw;
      }
    }
    List(List< T >&& rhs)
    {
      swap(rhs);
    }
    bool operator<(const List< T >& rhs) const
    {
      size_t min_size = std::min(rhs.size_, size_);
      Node< T >* node = head_;
      Node< T >* rhs_node = rhs.head_;
      for (size_t i = 0; i < min_size; ++i)
      {
        if (node->value_ != rhs_node->value_)
        {
          return node->value_ < rhs_node->value_;
        }
        node = node->next_;
        rhs_node = rhs_node->next_;
      }
      return false;
    }
    bool operator>=(const List< T >& rhs) const
    {
      return !(*this < rhs);
    }
    bool operator<=(const List< T >& rhs) const
    {
      return !(rhs < *this);
    }
    bool operator>(const List< T >& rhs) const
    {
      return (rhs < *this);
    }
    bool operator==(const List< T >& rhs) const
    {
      return !(*this < rhs) && !(rhs < *this);
    }
    bool operator!=(const List< T >& rhs) const
    {
      return !(rhs == *this);
    }
    List< T >& operator=(List< T >&& rhs)
    {
      if (this != std::addressof(rhs))
      {
        clear();
        swap(rhs);
      }
      return *this;
    }
    List< T >& operator=(const List< T >& rhs)
    {
      if (this != std::addressof(rhs))
      {
        List< T > temp(rhs);
        temp.swap(*this);
      }
      return *this;
    }
    ~List()
    {
      clear();
    }
    void assign(const T& value, size_t count)
    {
      try
      {
        clear();
        head_ = nullptr;
        tail_ = nullptr;
        for (size_t i = 0; i < count; ++i)
        {
          push_back(value);
        }
      }
      catch(const std::exception& e)
      {
        clear();
        throw;
      }
    }
    void assign(ListIterator< T > start, ListIterator< T > finish)
    {
      try
      {
        clear();
        head_ = nullptr;
        tail_ = nullptr;
        while (start != finish)
        {
          push_back(*start++);
        }
      }
      catch(const std::exception& e)
      {
        clear();
        throw;
      }
    }
    void assign(std::initializer_list< T > il)
    {
      try
      {
        clear();
        head_ = nullptr;
        tail_ = nullptr;
        auto it = il.begin();
        while (it != il.end())
        {
          push_back(*it++);
        }
      }
      catch(const std::exception& e)
      {
        clear();
        throw;
      }
    }
    void remove(const T& value)
    {
      remove_if([&](const T& n){return value == n;});
    }
    void splice(ConstListIterator< T > it, List< T >& list)
    {
      if (it == cbegin())
      {
        head_->prev_ = list.tail_;
        delete list.tail_->next_;
        list.tail_->next_ = head_;
        head_ = list.head_;
        size_ += list.size_;
      }
      else if (it == cend())
      {
        delete tail_->next_;
        list.head_->prev_ = tail_;
        tail_->next_ = list.head_;
        tail_ = list.tail_;
        size_ += list.size_;
      }
      else
      {
        delete list.tail_->next_;
        it.node->prev_->next_ = list.head_;
        list.tail_->next_ = it.node;
        list.head_->prev_ = it.node->prev_;
        it.node->prev_ = list.tail_;
        size_ += list.size_;
      }
      list.head_ = nullptr;
      list.tail_ = nullptr;
      list.size_ = 0;
    }
    void splice(ConstListIterator< T > it, List< T >& list, ConstListIterator< T > list_it)
    {
      insert(ListIterator< T >(it.node), *list_it);
      list.erase(list_it);
    }
    void splice(ConstListIterator< T > it, List< T >& list, ConstListIterator< T > list_start, ConstListIterator< T > list_finish)
    {
      while (list_start != list_finish)
      {
        splice(it, list, list_start++);
      }
    }
    void reverse()
    {
      Node< T >* start = head_;
      Node< T >* finish = tail_;
      while (start != finish)
      {
        std::swap(start->value_, finish->value_);
        start = start->next_;
        if (start != finish)
        {
          finish = finish->prev_;
        }
      }
    }
    template< class Functor >
    void remove_if(Functor f)
    {
      Node< T >* node = head_;
      while (node)
      {
        if (f(node->value_))
        {
          if (node == head_)
          {
            pop_front();
            node = head_;
          }
          else if (node == tail_)
          {
            pop_back();
            node = nullptr;
          }
          else
          {
            Node< T >* temp = node;
            node->next_->prev_ = node->prev_;
            node->prev_->next_ = node->next_;
            node = node->next_;
            delete temp;
            --size_;
          }
        }
        else
        {
          if (node == tail_)
          {
            node = nullptr;
          }
          else
          {
            node = node->next_;
          }
        }
      }
    }
    void swap(List< T >& list)
    {
      std::swap(list.head_, head_);
      std::swap(list.tail_, tail_);
      std::swap(list.size_, size_);
    }
    const T& at(size_t i) const
    {
      if (i >= size_)
      {
        throw std::logic_error("Element outside the list");
      }
      return operator[](i);
    }
    T& at(size_t i)
    {
      return const_cast< T& >(static_cast< const List< T >& >(*this).at(i));
    }
    T& operator[](size_t i)
    {
      return const_cast< T& >(static_cast< const List< T >& >(*this).operator[](i));
    }
    const T& operator[](size_t i) const
    {
      ConstListIterator< T > iterator(head_);
      for (size_t j = 0; j < i; ++j)
      {
        ++iterator;
      }
      return *iterator;
    }
    size_t size() const
    {
      return size_;
    }
    T& back()
    {
      return tail_->value_;
    }
    T& front()
    {
      return head_->value_;
    }
    const T& back() const
    {
      return tail_->value_;
    }
    const T& front() const
    {
      return head_->value_;
    }
    ListIterator< T > begin()
    {
      return ListIterator< T >(head_);
    }
    ListIterator< T > end()
    {
      return ListIterator< T >(tail_->next_);
    }
    ConstListIterator< T > cbegin() const
    {
      return ConstListIterator< T >(head_);
    }
    ConstListIterator< T > cend() const
    {
      return ConstListIterator< T >(tail_->next_);
    }
    ConstListIterator< T > erase(ConstListIterator< T > it)
    {
      if (it == cbegin())
      {
        pop_front();
      }
      else if (it == --cend())
      {
        pop_back();
      }
      else
      {
        it.node->next_->prev_ = it.node->prev_;
        it.node->prev_->next_ = it.node->next_;
        delete it.node;
        --size_;
      }
      return it;
    }
    ConstListIterator< T > erase(ConstListIterator< T > it_start, ConstListIterator< T > it_finish)
    {
      while (it_start != it_finish)
      {
        erase(it_start++);
      }
      return it_finish;
    }
    ListIterator< T > insert(ConstListIterator< T > it, const T& value)
    {
      try
      {
        if (it == cbegin())
        {
          push_front(value);
        }
        else if (it == cend())
        {
          push_back(value);
        }
        else
        {
          Node< T >* new_node = new Node< T >(value, it.node, it.node->prev_);
          it.node->prev_ = new_node;
          new_node->prev_->next_ = new_node;
          ++size_;
        }
        ListIterator< T > iterator(it.node);
        return iterator;
      }
      catch(const std::exception& e)
      {
        clear();
        throw;
      }
    }
    ListIterator< T > insert(ConstListIterator< T > it, ListIterator< T > start, ListIterator< T > finish)
    {
      try
      {
        ListIterator< T > result(it.node);
        while (start != finish)
        {
          insert(it++, *start++);
        }
        return ++result;
      }
      catch(const std::exception& e)
      {
        clear();
        throw;
      }
    }
    ListIterator< T > insert(ConstListIterator< T > it, size_t n, const T& value)
    {
      ListIterator< T > result(it.node);
      for (size_t i = 0; i < n; ++i)
      {
        insert(it++, value);
      }
      return ++result;
    }
    ListIterator< T > insert(ConstListIterator< T > it, std::initializer_list< T > il)
    {
        auto iterator = il.begin();
        ListIterator< T > result(it.node);
        while (iterator != il.end())
        {
          insert(it, *iterator++);
        }
        return ++result;
    }
    bool empty() const
    {
      return size_ == 0;
    }
    void push_front(const T& value)
    {
      Node< T >* new_node = new Node< T >(value, head_, nullptr);
      if (head_)
      {
        head_->prev_ = new_node;
      }
      if (!tail_)
      {
        try
        {
          Node< T >* end_node = new Node< T >(value);
          tail_ = new_node;
          end_node->prev_ = tail_;
          tail_->next_ = end_node;
        }
        catch(const std::exception& e)
        {
          delete new_node;
          throw;
        }
      }
      head_ = new_node;
      ++size_;
    }
    void push_back(const T& value)
    {
      Node< T >* new_node = new Node< T >(value, nullptr, tail_);
      if (tail_)
      {
        tail_->next_->prev_ = new_node;
        new_node->next_ = tail_->next_;
        tail_->next_ = new_node;
      }
      if (!head_)
      {
        try
        {
          Node< T >* end_node = new Node< T >(value);
          head_ = new_node;
          tail_ = head_;
          end_node->prev_ = tail_;
          tail_->next_ = end_node;
          ++size_;
          return;
        }
        catch(const std::exception& e)
        {
          delete new_node;
          throw;
        }
      }
      tail_ = new_node;
      ++size_;
    }
    void pop_back()
    {
      if (size_ == 1)
      {
        delete tail_->next_;
        delete tail_;
        --size_;
      }
      else
      {
        Node< T >* temp = tail_;
        tail_->next_->prev_ = tail_->prev_;
        tail_->prev_->next_ = tail_->next_;
        tail_ = tail_->prev_;
        delete temp;
        --size_;
      }
    }
    void pop_front()
    {
      if (size_ == 1)
      {
        delete tail_->next_;
        delete head_;
        --size_;
      }
      else
      {
        head_ = head_->next_;
        delete head_->prev_;
        --size_;
      }
    }
    void clear()
    {
      while (!empty())
      {
        pop_back();
      }
    }
    void unique()
    {
      ConstListIterator< T > it(head_);
      ConstListIterator< T > end(tail_);
      while (it != cend())
      {
        ConstListIterator< T > temp(it);
        ++temp;
        while (temp != cend())
        {
          ConstListIterator< T > temp_end(tail_);
          end = temp_end;
          if (temp == end)
          {
            if (*temp == *it)
            {
              erase(temp);
            }
            break;
          }
          if (*temp == *it)
          {
            ConstListIterator< T > temp2(temp);
            ++temp2;
            erase(temp);
            temp = temp2;
          }
          else
          {
            ++temp;
          }
        }
        ++it;
      }
    }
    template< class Pred >
    void unique(Pred p)
    {
      ConstListIterator< T > it(head_);
      ConstListIterator< T > end(tail_);
      while (it != cend())
      {
        ConstListIterator< T > temp(it);
        ++temp;
        while (temp != cend())
        {
          ConstListIterator< T > temp_end(tail_);
          end = temp_end;
          if (temp == end)
          {
            if (p(*temp, *it))
            {
              erase(temp);
            }
            break;
          }
          if (p(*temp, *it))
          {
            ConstListIterator< T > temp2(temp);
            ++temp2;
            erase(temp);
            temp = temp2;
          }
          else
          {
            ++temp;
          }
        }
        ++it;
      }
    }
    void sort()
    {
      Node< T >* node1 = head_;
      for (size_t i = 0; i < size_; ++i)
      {
        Node< T >* node2 = node1;
        for (size_t j = i; j < size_; ++j)
        {
          if (node1->value_ > node2->value_)
          {
            std::swap(node1->value_, node2->value_);
          }
          node2 = node2->next_;
        }
        node1 = node1->next_;
      }
    }
    template< class Compare >
    void sort(Compare comp)
    {
      Node< T >* node1 = head_;
      for (size_t i = 0; i < size_; ++i)
      {
        Node< T >* node2 = node1;
        for (size_t j = i; j < size_; ++j)
        {
          if (comp(node1->value_, node2->value_))
          {
            std::swap(node1->value_, node2->value_);
          }
          node2 = node2->next_;
        }
        node1 = node1->next_;
      }
    }
    template< class Compare >
    void merge(List< T >& list, Compare comp)
    {
      ListIterator< T > start(head_);
      ListIterator< T > list_start(list.head_);
      while (list_start != list.cend())
      {
        if (comp(*start, *list_start))
        {
          insert(start, *list_start);
          ++start;
          ++list_start;
          if (start == cend())
          {
            while (list_start != list.cend())
            {
              push_back(*list_start);
              ++list_start;
            }
          }
        }
        else
        {
          ++list_start;
        }
      }
      list.clear();
      list.head_ = nullptr;
      list.tail_ = nullptr;
    }
    void merge(List< T >& list)
    {
      ListIterator< T > start(head_);
      ListIterator< T > list_start(list.head_);
      while (list_start != list.cend())
      {
        if (*start >= *list_start)
        {
          insert(start, *list_start);
          ++start;
          ++list_start;
          if (start == cend())
          {
            while (list_start != list.cend())
            {
              push_back(*list_start);
              ++list_start;
            }
          }
        }
        else
        {
          ++list_start;
        }
      }
      list.clear();
      list.head_ = nullptr;
      list.tail_ = nullptr;
    }
    void emplace(ConstListIterator< T >)
    {}
    template< class... Args >
    ListIterator< T > emplace(ListIterator< T > it, const T& val, Args&&... args)
    {
      ListIterator< T > iterator = insert(it, val);
      emplace(it, args...);
      return iterator;
    }
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}
#endif
