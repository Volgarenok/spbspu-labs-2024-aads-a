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
      node_t* node;
      if (root_)
      {
        node = insert_p(key, val, root_);
        ++size_;
      }
      else
      {
        root_ = new node_t(key, val);
        node = root_;
        ++size_;
      }
      return node;
    }

    node_t* insert_p(const Key& key, const Value& val, node_t* currNode)
    {
      node_t* node;
      if (compare()(key, currNode->data.first))
      {
        if (currNode->hasLeft())
        {
          node = insert_p(key, val, currNode->left);
        }
        else
        {
          currNode->left = new node_t(key, val, currNode);
          getBalabce(currNode->left);
          return currNode->left;
        }
      }
      else
      {
        if (currNode->hasRight())
        {
          node = insert_p(key, val, currNode->right);
        }
        else
        {
          currNode->right = new node_t(key, val, currNode);
          getBalabce(currNode->right);
          return currNode->right;
        }
      }
      return node;
    }

    bool empty() const noexcept
    {
      return size_ == 0;
    }

    void del(const Key& key)
    {
      if (size_ == 1 && root_->data.first == key)
      {
        --size_;
        root_ = nullptr;
      }
      else if (size_ > 1)
      {
        node_t* nodeRemove = get(key, root_);
        if (nodeRemove)
        {
          remove(nodeRemove);
          --size_;
        }
        else
        {
          throw std::out_of_range("Error\n");
        }
      }
      else
      {
        throw std::out_of_range("Error\n");
      }
    }

    const_iterator_tree< Key, Value, Compare > cbegin() const noexcept
    {
      return const_iterator_tree< Key, Value, Comparee >(getMin(root_));
    }

    const_iterator_tree< Key, Value, Compare > cend() const noexcept
    {
      return const_iterator_tree< Key, Value, Comparee >();
    }

    const Value& operator[](const Key& key) const
    {
      node_t* traverser = get(key, root_);
      return traverser->data.second;
    }

    Value& operator[](const Key& key)
    {
      node_t* traverser = get(key, root_);
      if (traverser)
      {
        return traverser->data.second;
      }
      else
      {
        traverser = insert(key, Value());
      }
    }

    Value& at(const Key& key)
    {
      node_t* traverser = get(key, root_);
      if (traverser)
      {
        return traverser->data.second;
      }
      throw std::out_of_range("No such element");
    }

    const Value& at(const Key& key) const
    {
      node_t* traverser = get(key, root_);
      if (traverser)
      {
        return traverser->data.second;
      }
      throw std::out_of_range("No such element");
    }

    const_iterator< Key, Value > find(const Key& key) const
    {
      
    }
  };

}



#endif
