#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <initializer_list>
#include <stdexcept>
#include <cmath>
#include <cstddef>
#include <utility>
#include <hash_table_node.hpp>
#include <bidirectional_list.hpp>
#include <hash_table_iterators.hpp>
#include <const_hash_table_iterators.hpp>

namespace namestnikov
{
  template< class Key, class Value >
  class HashTable
  {
  public:
    using val_type_t = std::pair< const Key, Value >;
    using node_t = detail::HashTableNode< val_type_t >;
    using list_iterator = typename List< node_t * >::iterator;
    using hash_table_iterator = HashTableIterator< Key, Value >;
    using const_hash_table_iterator = ConstHashTableIterator< Key, Value >;

    HashTable():
      capacity_(5),
      count_(0),
      buckets_(new list_iterator[5]),
      elements_()
    {
      for (size_t i = 0; i < 5; ++i)
      {
        buckets_[i] = elements_.end();
      }
    }
    HashTable(const HashTable< Key, Value > & other):
      capacity_(other.capacity_),
      count_(0),
      buckets_(new list_iterator[other.capacity_]),
      elements_()
    {
      try
      {
        for (size_t i = 0; i < capacity_; ++i)
        {
          buckets_[i] = elements_.end();
          if (other.buckets_[i] != other.elements_.end())
          {
            list_iterator iter = other.buckets_[i];
            insert(Key((*iter)->data.first), Value((*iter)->data.second), (*iter)->hash);
          }
        }
        for (auto it = other.elements_.cbegin(); it != other.elements_.cend(); ++it)
        {
          insert(Key((*it)->data.first), Value((*it)->data.second), (*it)->hash);
        }
      }
      catch (...)
      {
        clear();
        delete[] buckets_;
        throw;
      }
    }
    HashTable< Key, Value >& operator=(const HashTable< Key, Value > & other)
    {
      if (this != std::addressof(other))
      {
        HashTable< Key, Value > temp(other);
        swap(temp);
      }
      return *this;
    }
    HashTable(HashTable< Key, Value > && other) noexcept:
      capacity_(other.capacity_),
      count_(other.count_),
      buckets_(other.buckets_),
      elements_(std::move(other.elements_))
    {
      other.capacity_ = 5;
      other.count_ = 0;
      other.buckets_ = nullptr;
    }
    HashTable< Key, Value >& operator=(HashTable< Key, Value > && other) noexcept
    {
      if (this != std::addressof(other))
      {
        HashTable< Key, Value > temp(std::move(other));
        swap(temp);
      }
      return *this;
    }
    void swap(HashTable< Key, Value > & other) noexcept
    {
      std::swap(capacity_, other.capacity_);
      std::swap(count_, other.count_);
      std::swap(elements_, other.elements_);
      std::swap(buckets_, other.buckets_);
    }
    Value & operator[](const Key & key)
    {
      auto result = insert(key, Value());
      return (*(result.first)).second;
    }
    Value & at(const Key & key)
    {
      auto result = find(key);
      if (result == end())
      {
        throw std::out_of_range("There are not value with specific key");
      }
      return (*result).second;
    }
    const Value & at(const Key & key) const
    {
      auto result = find(key);
      if (result == end())
      {
        throw std::out_of_range("There are not value with specific key");
      }
      return (*result).second;
    }
    bool empty() const noexcept
    {
      return (count_ == 0);
    }
    size_t bucketCount() const noexcept
    {
      return capacity_;
    }
    size_t size() const noexcept
    {
      return count_;
    }
    void clear()
    {
      auto it = elements_.begin();
      auto temp = it;
      while (it != elements_.end())
      {
        buckets_[(*it)->hash % capacity_] = elements_.end();
        ++it;
        delete *temp;
        elements_.erase(temp);
        temp = it;
      }
      count_ = 0;
    }
    std::pair< hash_table_iterator, bool > insert(const Key & key, const Value & value)
    {
      return insert(key, value, std::hash< Key >()(key));
    }
    bool erase(const Key & key)
    {
      auto it = find(key);
      bool isErased = false;
      if (it != end())
      {
        erase(it);
        isErased = true;
      }
      return isErased;
    }
    hash_table_iterator find(const Key & key)
    {
      return find(key, std::hash< Key >()(key));
    }
    const_hash_table_iterator find(const Key & key) const
    {
      return find(key, std::hash< Key >()(key));
    }
    hash_table_iterator begin() const
    {
      return hash_table_iterator(elements_.begin());
    }
    hash_table_iterator end() const
    {
      return hash_table_iterator(elements_.end());
    }
    const_hash_table_iterator cbegin() const
    {
      return const_hash_table_iterator(elements_.cbegin());
    }
    const_hash_table_iterator cend() const
    {
      return const_hash_table_iterator(elements_.cend());
    }
    hash_table_iterator erase(hash_table_iterator pos)
    {
      list_iterator iter = pos.listIter_;
      size_t hash = (*iter)->hash;
      if ((pos.listIter_ == elements_.begin()) || (((*(--iter))->hash % capacity_) != (hash % capacity_)))
      {
        size_t index = hash % capacity_;
        delete *(pos.listIter_);
        list_iterator next = elements_.erase(pos.listIter_);
        if ((next != elements_.end()) && (((*next)->hash % capacity_) == (hash % capacity_)))
        {
          buckets_[index] = next;
        }
        else
        {
          buckets_[index] = elements_.end();
        }
        --count_;
        return hash_table_iterator(next);
      }
      else
      {
        delete *(pos.listIter_);
        --count_;
        return hash_table_iterator(elements_.erase(pos.listIter_));
      }
    }
    ~HashTable()
    {
      clear();
      delete[] buckets_;
    }
  private:
    size_t capacity_;
    size_t count_;
    list_iterator * buckets_;
    List< node_t * > elements_;
    void rehash(size_t count)
    {
      size_t newCapacity = 5;
      while ((newCapacity < count) || (newCapacity < (count_ / 0.75)))
      {
        newCapacity = calculateNextCapacity(newCapacity);
      }
      if (newCapacity == capacity_)
      {
        return;
      }
      try
      {
        List< node_t * > newElements;
        list_iterator * newBuckets = new list_iterator[newCapacity] {};
        for (size_t i = 0; i < newCapacity; ++i)
        {
          newBuckets[i] = newElements.end();
        }
        auto it = elements_.begin();
        auto temp = it;
        while (it != elements_.end())
        {
          size_t index = (*it)->hash % newCapacity;
          if (newBuckets[index] == newElements.end())
          {
            newElements.push_front(*it);
            newBuckets[index] = newElements.begin();
          }
          else
          {
            newElements.insert(newBuckets[index], *it);
            --(newBuckets[index]);
          }
          ++it;
          elements_.erase(temp);
          temp = it;
        }
        elements_ = std::move(newElements);
        delete[] buckets_;
        buckets_ = newBuckets;
        capacity_ = newCapacity;
      }
      catch (...)
      {
        clear();
        delete[] buckets_;
        throw;
      }
    }
    size_t calculateNextCapacity(size_t current) const
    {
      size_t powDegree = 0;
      for (; current > std::pow(2, powDegree); ++powDegree) {};
      ++powDegree;
      return std::pow(2, powDegree) - (std::pow(2, powDegree) - std::pow(2, powDegree - 1)) / 2 - 1;
    }
    hash_table_iterator find(const Key & key, size_t hash)
    {
      size_t index = hash % capacity_;
      auto bucketIter = buckets_[index];
      if (bucketIter == elements_.end())
      {
        return end();
      }
      while ((bucketIter != elements_.end()) && (((*bucketIter)->hash % capacity_) == index) && ((*bucketIter)->data.first != key))
      {
        ++bucketIter;
      }
      if ((bucketIter != elements_.end()) && ((*bucketIter)->data.first == key))
      {
        return hash_table_iterator(bucketIter);
      }
      else
      {
        return end();
      }
    }
    const_hash_table_iterator find(const Key & key, size_t hash) const
    {
      size_t index = hash % capacity_;
      auto bucketIter = buckets_[index];
      if (bucketIter == elements_.end())
      {
        return cend();
      }
      while ((bucketIter != elements_.end()) && (((*bucketIter)->hash % capacity_) == index) && ((*bucketIter)->data.first != key))
      {
        ++bucketIter;
      }
      if ((bucketIter != elements_.end()) && ((*bucketIter)->data.first == key))
      {
        return const_hash_table_iterator(bucketIter);
      }
      else
      {
        return cend();
      }
    }
    std::pair< hash_table_iterator, bool > insert(const Key & key, const Value & value, size_t hash)
    {
      try
      {
        hash_table_iterator desired = find(key, hash);
        if (desired != end())
        {
          return std::pair< hash_table_iterator, bool >(desired, false);
        }
        size_t index = hash % capacity_;
        if (capacity_ < ((count_ + 1) / 0.75))
        {
          rehash(calculateNextCapacity(capacity_));
          index = hash % capacity_;
        }

        node_t  * node = new node_t(val_type_t(key, value), hash);
        std::pair< hash_table_iterator, bool > result(end(), true);
        try
        {
          if (buckets_[index] == elements_.end())
          {
            elements_.push_front(node);
            buckets_[index] = elements_.begin();
            result.first = begin();
          }
          else
          {
            elements_.insert(buckets_[index], node);
            --(buckets_[index]);
            result.first = hash_table_iterator(buckets_[index]);
          }
        }
        catch (...)
        {
          delete node;
          throw;
        }
        ++count_;
        return result;
      }
      catch (...)
      {
        clear();
        delete[] buckets_;
        throw;
      }
    }
  };
}

#endif
