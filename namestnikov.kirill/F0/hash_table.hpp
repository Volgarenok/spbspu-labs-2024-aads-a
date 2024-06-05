#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <initializer_list>
#include <stdexcept>
#include <cmath>
#include <cstddef>
#include "hash_table_node.hpp"
#include "hash_table_iterators.hpp"
#include "const_hash_table_iterators.hpp"

namespace namestnikov
{
  template< class Key, class Value >
  class HashTable
  {
  public:
    using val_type_t = std::pair< const Key, Value >;
    using node_t = HashTableNode< val_type_t >;
    using list_iterator_t = typename std::list< node_t * >::iterator;
    using hash_table_iterator = HashTableIterator< Key, Value >;
    using const_hash_table_iterator = ConstHashTableIterator< Key, Value >;
    HashTable():
      capacity_(5),
      count_(0),
      buckets_(new list_iterator_t[5]),
      elements_()
    {
      for (size_t i = 0; i < 5; ++i)
      {
        buckets_[i] = elements_.end();
      }
    }
    HashTable(std::initializer_list< val_type_t > initList):
      capacity_(initList.size() / 0.75 + 1),
      count_(0),
      buckets_(new list_iterator_t[initList.size() / 0.75 + 1]),
      elements_()
    {
      for (size_t i = 0; i < capacity_; ++i)
      {
        buckets_[i] = elements_.end();
      }
      auto it = initList.begin();
      for (; it != initList.end(); ++it)
      {
        insert((*it).first, (*it).second);
      }
    }
    HashTable(const HashTable< Key, Value > & other):
      capacity_(other.capacity_),
      count_(0),
      buckets_(new list_iterator_t[other.capacity_]),
      elements_()
    {
      for (size_t i = 0; i < capacity_; ++i)
      {
        buckets_[i] = elements_.end();
        if (other.buckets_[i] != other.elements_.end())
        {
          list_iterator_t it = other.buckets_[i];
          insert(Key((**it).data.first), Value((**it).data.second), (**it).hash);
        }
      }
      auto it = other.elements_.cbegin();
      for (; it != other.elements_.cend(); ++it)
      {
        insert(Key((**it).data.first), Value((**it).data.second), (**it).hash);
      }
    }
    HashTable< Key, Value > & operator=(const HashTable< Key, Value > & other)
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
      elements_(std::move(other.elements_)),
      buckets_(other.buckets_)
    {
      other.capacity_ = 5;
      other.count_ = 0;
      other.buckets_ = nullptr;
    }
    HashTable< Key, Value > & operator=(HashTable< Key, Value > && other) noexcept
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
        throw std::out_of_range("There aren't any element with this key");
      }
      return (*result).second;
    }
    const Value & at(const Key & key) const
    {
      auto result = find(key);
      if (result == end())
      {
        throw std::out_of_range("There aren't any element with this key");
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
    void clear() noexcept
    {
      auto it = elements_.begin();
      auto tempIt = it;
      while (it != elements_.end())
      {
        buckets_[(**it).hash & capacity_] = elements_.end();
        ++it;
        delete *tempIt;
        elements_.erase(tempIt);
        tempIt = it;
      }
      count_ = 0;
    }
    size_t calculateNewCapacity(size_t current) const
    {
      size_t indicator = 0;
      for (; current > std::pow(2, indicator); ++indicator) {};
      ++indicator;
      return std::pow(2, indicator) - (std::pow(2, indicator) - std::pow(2, indicator - 1)) / 2 - 1;
    }
    void rehash(size_t count)
    {
      size_t newCapacity = 5;
      while ((newCapacity < count) || (newCapacity < (count / 0.75)))
      {
        newCapacity = calculateNewCapacity(newCapacity);
      }
      if (capacity_ == newCapacity)
      {
        return;
      }
      else
      {
        std::list< node_t * > newElements;
        list_iterator_t * newBuckets = new list_iterator_t[newCapacity]{};
        for (size_t i = 0; i < newCapacity; ++i)
        {
          newBuckets[i] = newElements.end();
        }
        auto it = elements_.begin();
        auto temp = it;
        while (it != elements_.end())
        {
          size_t index = (**it).hash % newCapacity;
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
        elements = std::move(newElements);
        delete [] buckets_;
        buckets_ = newBuckets;
        capacity_ = newCapacity;
      }
    }
    hash_table_iterator begin() noexcept
    {
      return hash_table_iterator(elements_.begin());
    }
    hash_table_iterator end() noexcept
    {
      return hash_table_iterator(elements_.end());
    }
    const_hash_table_iterator cbegin() const noexcept
    {
      return const_hash_table_iterator(elements_.cbegin());
    }
    const_hash_table_iterator cend() const noexcept
    {
      return const_hash_table_iterator(elements_.cend());
    }
    ~HashTable()
    {
      clear();
      delete [] buckets_;
    }
  private:
    size_t count_;
    size_t capacity_;
    std::list< node_t * > elements_;
    list_iterator_t * buckets_;
  };
}

#endif