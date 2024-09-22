#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <iostream>

namespace belokurskaya
{
  template < class T >
  class MyVector
  {
    private:
      T* array_;
      size_t size_;
      size_t capacity_;
      const int CAPACITY_CHANGE_FACTOR_ = 2;

    public:
      MyVector():
        array_(nullptr),
        size_(0),
        capacity_(0)
      {}

      MyVector(const MyVector& other):
        size_(other.size_),
        capacity_(other.size_)
      {
        array_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i)
        {
          array_[i] = other.array_[i];
        }
      }

      MyVector(MyVector&& other) noexcept:
        array_(other.array_),
        size_(other.size_),
        capacity_(other.capacity_)
      {
        other.array_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
      }

      ~MyVector()
      {
        delete[] array_;
      }

      void push_back(const T& value)
      {
        if (size_ >= capacity_)
        {
          capacity_ = (capacity_ == 0) ? 1 : capacity_ * CAPACITY_CHANGE_FACTOR_;
          T* new_array = new T[capacity_];
          for (size_t i = 0; i < size_; ++i)
          {
            new_array[i] = array_[i];
          }
          delete[] array_;
          array_ = new_array;
        }
        array_[size_++] = value;
      }

      void erase(size_t index)
      {
        if (index >= size_)
        {
          throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size_ - 1; ++i)
        {
          array_[i] = array_[i + 1];
        }
        size_--;
      }

      bool contains(const T& value) const
      {
        for (size_t i = 0; i < size_; ++i)
        {
          if (array_[i] == value)
          {
            return true;
          }
        }
        return false;
      }

      size_t size() const
      {
        return size_;
      }

      T& operator[](size_t index)
      {
        if (index >= size_)
        {
          throw std::out_of_range("Index out of range");
        }
        return array_[index];
      }

      const T& operator[](size_t index) const
      {
        if (index >= size_)
        {
          throw std::out_of_range("Index out of range");
        }
        return array_[index];
      }

      void clear()
      {
        size_ = 0;
      }

      T* begin() const
      {
        return array_;
      }

      T* end() const
      {
        return array_ + size_;
      }

      void insert(const T& value)
      {
        if (size_ >= capacity_)
        {
          capacity_ = (capacity_ == 0) ? 1 : capacity_ * CAPACITY_CHANGE_FACTOR_;
          T* new_array = new T[capacity_];
          for (size_t i = 0; i < size_; ++i)
          {
            new_array[i] = array_[i];
          }
          delete[] array_;
          array_ = new_array;
        }
        array_[size_++] = value;
      }

      size_t findIndexElement(const T& value) const
      {
        for (size_t i = 0; i < size_; ++i)
        {
          if (array_[i] == value)
          {
            return i;
          }
        }
        return size_;
      }

      MyVector& operator=(const MyVector& other)
      {
        if (this != &other)
        {
          delete[] array_;
          array_ = new T[other.capacity_];
          size_ = other.size_;
          capacity_ = other.capacity_;
          for (size_t i = 0; i < size_; ++i)
          {
            array_[i] = other.array_[i];
          }
        }
        return *this;
      }

      friend std::ostream& operator<<(std::ostream& out, const MyVector< T >& vector)
      {
        for (size_t i = 0; i < vector.size(); i++)
        {
          out << vector[i] << " ";
        }
        return out;
      }
  };

  template < class T >
  MyVector< T > getIntersectionVector(const MyVector< T >& vector1, const MyVector< T >& vector2)
  {
    MyVector< T > intersection;
    for (size_t i = 0; i < vector1.size(); ++i)
    {
      if (vector2.contains(vector1[i]))
      {
        intersection.push_back(vector1[i]);
      }
    }
    return intersection;
  }
}

#endif
