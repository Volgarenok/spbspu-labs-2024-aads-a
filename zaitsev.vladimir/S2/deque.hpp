#ifndef DEQUE_HPP
#define DEQUE_HPP
#include <cstddef>
#include <memory>
#include <cstring>
#include <iterator>
#include <algorithm>

namespace zaitsev
{
  template< typename T >
  class Deque
  {
    using alloc_traits = std::allocator_traits<std::allocator< T >>;
    static const size_t chunk_cap_ = 20;
    size_t chunks_nmb_;
    size_t size_;
    size_t head_chunk_;
    size_t head_pos_;
    T** chunk_heads_;
    std::allocator< T > chunk_alloc_;
    std::allocator< T* > head_alloc_;

    template<bool IsConst>
    class BaseIterator
    {
      using prt_t = std::conditional_t< IsConst, const T*, T* >;
      using ref_t = std::conditional_t< IsConst, const T&, T& >;
      using container_t = std::conditional_t< IsConst, const Deque< T >&, Deque< T >& >;
    private:
      size_t chunk_nmb_;
      size_t pos_;
      container_t container_;

    public:
      BaseIterator(size_t chuck_nmb, size_t pos, container_t container):
        chunk_nmb_(chuck_nmb),
        pos_(pos),
        container_(container)
      {}
      BaseIterator() = delete;
      BaseIterator(const BaseIterator& other) = default;
      BaseIterator(BaseIterator&& other) = default;
      ~BaseIterator() = default;
      BaseIterator& operator++()
      {
        container_.next_pos(chunk_nmb_, pos_);
        return *this;
      }
      BaseIterator operator++(int)
      {
        BaseIterator copy = *this;
        container_.next_pos(chunk_nmb_, pos_);
        return copy;
      }
      BaseIterator& operator--()
      {
        container_.prev_pos(chunk_nmb_, pos_);
        return *this;
      }
      BaseIterator operator--(int)
      {
        BaseIterator copy = *this;
        if (pos_ > 0)
        {
          --pos_;
        }
        else
        {
          --chunk_nmb_;
          pos_ = container_.chunk_cap_ - 1;
        }
        return copy;
      }
      ref_t operator*() const
      {
        return container_.chunk_heads_[chunk_nmb_][pos_];
      }
      prt_t operator->() const
      {
        return container_.chunk_heads_[chunk_nmb_] + pos_;
      }
      bool operator!=(const BaseIterator& other) const
      {
        return pos_ != other.pos_ || chunk_nmb_ != other.chunk_nmb_;
      }
      bool operator==(const BaseIterator& other) const
      {
        return pos_ == other.pos_ && chunk_nmb_ == other.chunk_nmb_;
      }
    };

    void add_chunk(bool to_end)
    {
      T** new_chunk_heads_ = head_alloc_.allocate(chunks_nmb_ + 1);
      if (to_end)
      {
        std::memcpy(new_chunk_heads_, chunk_heads_, chunks_nmb_ * sizeof(T*));
        new_chunk_heads_[chunks_nmb_] = chunk_alloc_.allocate(chunk_cap_);
      }
      else
      {
        std::memcpy(new_chunk_heads_ + 1, chunk_heads_, chunks_nmb_ * sizeof(T*));
        new_chunk_heads_[0] = chunk_alloc_.allocate(chunk_cap_);
      }
      head_alloc_.deallocate(chunk_heads_, chunks_nmb_);
      chunk_heads_ = new_chunk_heads_;
      if (!to_end)
      {
        ++head_chunk_;
      }
      ++chunks_nmb_;
    }
    void next_pos(size_t& chunk_nmb, size_t& pos) const
    {
      if (pos < chunk_cap_ - 1)
      {
        ++pos;
      }
      else
      {
        ++chunk_nmb;
        pos = 0;
      }
    }
    void prev_pos(size_t& chunk_nmb, size_t& pos) const
    {
      if (pos > 0)
      {
        --pos;
      }
      else
      {
        --chunk_nmb;
        pos = chunk_cap_ - 1;
      }
    }
    void convert_index(size_t index, size_t& dest_chunk_nmb, size_t& dest_pos) const
    {
      if (index == 0)
      {
        return;
      }
      if (chunk_cap_ - head_pos_ >= index)
      {
        dest_chunk_nmb = head_chunk_;
        dest_pos = head_pos_ + index - 1;
      }
      else
      {
        size_t sz_without_first_chunk = index - chunk_cap_ + head_pos_;
        dest_chunk_nmb = (sz_without_first_chunk - 1) / chunk_cap_ + 1 + head_chunk_;
        dest_pos = (sz_without_first_chunk - 1) % chunk_cap_;
      }
    }
    void reset_head()
    {
      if (!size_)
      {
        head_chunk_ = chunks_nmb_ / 2;
        head_pos_ = 0;
      }
    }

  public:
    using iterator = BaseIterator<false>;
    using const_iterator = BaseIterator<true>;
    Deque():
      chunks_nmb_(0),
      size_(0),
      head_chunk_(0),
      head_pos_(0),
      chunk_heads_(nullptr),
      chunk_alloc_(),
      head_alloc_()
    {}
    Deque(const Deque& other):
      chunks_nmb_(other.chunks_nmb_),
      size_(other.size_),
      head_pos_(0),
      chunk_alloc_(),
      head_alloc_()
    {
      chunk_heads_ = head_alloc_.allocate(chunks_nmb_);
      size_t i = 0;
      size_t j = 0;
      try
      {
        for (; j < chunks_nmb_; ++j)
        {
          chunk_heads_[j] = chunk_alloc_.allocate(chunk_cap_);
        }
        size_t chunk = other.head_chunk_;
        size_t pos = other.head_pos_;
        Deque< T >::iterator it = other.begin();
        for (; i < size_; ++i, ++it)
        {
          alloc_traits::construct(chunk_alloc_, chunk_heads_[chunk] + pos, *it);
          if (pos < chunk_cap_ - 1)
          {
            ++pos;
          }
          else
          {
            ++chunks_nmb_;
            pos = 0;
          }
        }
      }
      catch (const std::bad_alloc&)
      {
        size_t chunk = other.head_chunk_;
        size_t pos = other.head_pos_;
        for (size_t k = 0; k < i; ++k)
        {
          alloc_traits::destroy(chunk_alloc_, chunk_heads_[chunk] + pos);
          if (pos < chunk_cap_ - 1)
          {
            ++pos;
          }
          else
          {
            ++chunks_nmb_;
            pos = 0;
          }
        }
        for (size_t k = 0; k < j; ++k)
        {
          chunk_alloc_.deallocate(chunk_heads_[j], chunk_cap_);
        }
        head_alloc_.deallocate(chunk_heads_, chunks_nmb_);
        throw;
      }
    }
    Deque(Deque&& other):
      chunks_nmb_(other.chunks_nmb_),
      size_(other.size_),
      head_chunk_(other.head_chunk_),
      head_pos_(other.head_pos_),
      chunk_heads_(other.chunk_heads_),
      chunk_alloc_(other.chunk_alloc_),
      head_alloc_(other.head_alloc_)
    {
      other.chunks_nmb_ = 0;
      other.size_ = 0;
      other.head_chunk_ = 0;
      other.head_pos_ = 0;
      other.chunk_heads_ = nullptr;
      other.chunk_alloc_ = std::allocator< T >();
      other.head_alloc_ = std::allocator< T* >();
    }
    Deque& operator=(const Deque& other)
    {
      Deque& other_cp(other);
      *this = std::move(other.cp);
      return *this;
    }
    Deque& operator=(Deque&& other)
    {
      clear();
      chunks_nmb_ = other.chunks_nmb_;
      size_ = other.size_;
      head_chunk_ = other.head_chunk_;
      head_pos_ = other.head_pos_;
      chunk_heads_ = other.chunk_heads_;
      chunk_alloc_=other.chunk_alloc_;
      head_alloc_=other.head_alloc_;
      other.chunks_nmb_ = 0;
      other.size_ = 0;
      other.head_chunk_ = 0;
      other.head_pos_ = 0;
      other.chunk_heads_ = nullptr;
      other.chunk_alloc_ = std::allocator< T >();
      other.head_alloc_ = std::allocator< T* >();

      return *this;
    }
    ~Deque()
    {
      for (Deque< T >::iterator i = begin(); i != end(); ++i)
      {
        alloc_traits::destroy(chunk_alloc_, i.operator->());
      }
      for (size_t i = 0; i < chunks_nmb_; ++i)
      {
        chunk_alloc_.deallocate(chunk_heads_[i], chunk_cap_);
      }
      head_alloc_.deallocate(chunk_heads_, chunks_nmb_);
    }
    void push_back(const T& value)
    {
      size_t end_chunk = head_chunk_;
      size_t end_pos = head_pos_;
      if (size_)
      {
        convert_index(size_, end_chunk, end_pos);
      }
      if (chunks_nmb_ == 0 || (end_chunk == chunks_nmb_ - 1 && end_pos == chunk_cap_ - 1))
      {
        add_chunk(true);
      }
      if (size_)
      {
        next_pos(end_chunk, end_pos);
      }
      alloc_traits::construct(chunk_alloc_, chunk_heads_[end_chunk] + end_pos, value);
      ++size_;
    }
    void push_back(T&& value)
    {
      size_t end_chunk = head_chunk_;
      size_t end_pos = head_pos_;
      if (size_)
      {
        convert_index(size_, end_chunk, end_pos);
      }
      if (chunks_nmb_ == 0 || end_chunk == chunks_nmb_ - 1 && end_pos == chunk_cap_ - 1)
      {
        add_chunk(true);
      }
      if (size_)
      {
        next_pos(end_chunk, end_pos);
      }
      alloc_traits::construct(chunk_alloc_, chunk_heads_[end_chunk] + end_pos, value);
      ++size_;
    }
    void pop_back()
    {
      if (size_ == 0)
      {
        throw std::out_of_range("Queue is empty");
      }
      size_t end_chunk = 0;
      size_t end_pos = 0;
      convert_index(size_, end_chunk, end_pos);
      alloc_traits::destroy(chunk_alloc_, chunk_heads_[end_chunk] + end_pos);
      --size_;
      reset_head();
    }
    void push_front(const T& value)
    {
      if (head_chunk_ == 0 && head_pos_ == 0)
      {
        add_chunk(false);
      }
      prev_pos(head_chunk_, head_pos_);
      try
      {
        alloc_traits::construct(chunk_alloc_, chunk_heads_[head_chunk_] + head_pos_, value);
        ++size_;
      }
      catch (const std::bad_alloc&)
      {
        next_pos(head_chunk_, head_pos_);
        throw;
      }
    }
    void push_front(T&& value)
    {
      if (head_chunk_ == 0 && head_pos_ == 0)
      {
        add_chunk(false);
      }
      prev_pos(head_chunk_, head_pos_);
      alloc_traits::construct(chunk_alloc_, chunk_heads_[head_chunk_] + head_pos_, value);
      ++size_;
    }
    void pop_front()
    {
      if (size_ == 0)
      {
        throw std::out_of_range("Queue is empty");
      }
      alloc_traits::destroy(chunk_alloc_, chunk_heads_[head_chunk_] + head_pos_);
      next_pos(head_chunk_, head_pos_);
      --size_;
      reset_head();
    }
    void clear()
    {
      for (Deque< T >::iterator i = begin(); i != end(); ++i)
      {
        alloc_traits::destroy(chunk_alloc_, i.operator->());
      }
      for (size_t i = 0; i < chunks_nmb_; ++i)
      {
        chunk_alloc_.deallocate(chunk_heads_[i], chunk_cap_);
      }
      head_alloc_.deallocate(chunk_heads_, chunks_nmb_);
      size_ = 0;
      chunks_nmb_ = 0;
      head_chunk_ = 0;
      head_pos_ = 0;
      chunk_heads_ = nullptr;
    }
    T& front()
    {
      if (size_ == 0)
      {
        throw std::out_of_range("Queue is empty");
      }
      return chunk_heads_[head_chunk_][head_pos_];
    }
    const T& front() const
    {
      if (size_ == 0)
      {
        throw std::out_of_range("Queue is empty");
      }
      return chunk_heads_[head_chunk_][head_pos_];
    }
    T& back()
    {
      if (size_ == 0)
      {
        throw std::out_of_range("Queue is empty");
      }
      size_t chunk = 0;
      size_t pos = 0;
      convert_index(size_, chunk, pos);
      return chunk_heads_[chunk][pos];
    }
    const T& back() const
    {
      if (size_ == 0)
      {
        throw std::out_of_range("Queue is empty");
      }
      size_t chunk = 0;
      size_t pos = 0;
      convert_index(size_, chunk, pos);
      return chunk_heads_[chunk][pos];
    }
    iterator begin()
    {
      return iterator(head_chunk_, head_pos_, *this);
    }
    iterator end()
    {
      size_t end_chunk = head_chunk_;
      size_t end_pos = head_pos_;
      convert_index(size_ + 1, end_chunk, end_pos);
      return iterator(end_chunk, end_pos, *this);
    }
    const_iterator begin() const
    {
      return const_iterator(head_chunk_, head_pos_, *this);
    }
    const_iterator end() const
    {
      size_t end_chunk = 0;
      size_t end_pos = 0;
      convert_index(size_ + 1, end_chunk, end_pos);
      return const_iterator(end_chunk, end_pos, *this);
    }
    const_iterator cbegin() const
    {
      return const_iterator(head_chunk_, head_pos_, *this);
    }
    const_iterator cend() const
    {
      size_t end_chunk = 0;
      size_t end_pos = 0;
      convert_index(size_ + 1, end_chunk, end_pos);
      return const_iterator(end_chunk, end_pos, *this);
    }
    bool empty() const
    {
      return !size_;
    }
    size_t size() const
    {
      return size_;
    }
  };
}
#endif
