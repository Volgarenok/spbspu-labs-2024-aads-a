#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

namespace marishin
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  struct BinarySearchTree
  {
    using node_t = detail::TreeNode< Key, Value >;
    BinarySearchTree():
      root_(nullptr),
      size_(0)
    {}

    BinarySearchTree(const BinarySearchTree& rhs):
      root_(nullptr),
      size_(0)
    {
      try
      {
        for (auto begin = rhs.cbegin(); begin != rhs.cend(); ++begin)
        {
          insert(begin->first, begin->second);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    BinarySearchTree(BinarySearchTree&& rhs):
      root_(rhs.root_),
      size_(rhs.size_)
    {
      rhs.root_ = nullptr;
      rhs.size_ = 0;
    }

    BinarySearchTree& operator=(const BinarySearchTree& rhs)
    {
      BinarySearchTree< Key, Value > temp(rhs);
      if (this != std::addressof(rhs))
      {
        swap(temp);
      }
      return *this;
    }

    BinarySearchTree& operator=(BinarySearchTree&& rhs) noexcept
    {
      Tree< Key, Value > temp(std::move(rhs));
      if (this != std::addressof(rhs))
      {
        swap(temp);
      }
      return *this;
    }

    size_t size() const noexcept
    {
      return this->size_;
    }

    ~BinarySearchTree()
    {
      clear();
    }

    void swap(BinarySearchTree< Key, Value, Compare >& rhs) noexcept
    {
      std::swap(root_, rhs.root_);
      std::swap(size_, rhs.size_);
    }

    node_t* insert(const Key& key, const Value& val)
    {
      
    }


  };

}



#endif
