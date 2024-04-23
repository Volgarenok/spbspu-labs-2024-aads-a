#ifndef TREE_HPP
#define TREE_HPP
#include <cstddef>
#include "treeiterator.hpp"

namespace piyavkin
{
  template< class Key, class T, class Compare = std::less< Key > >
  class Tree
  {
  public:
    using val_type = std::pair< const Key, T >;
    Tree():
      root_(nullptr),
      cmp_(Compare()),
      size_(0),
      before_min_(Key(), nullptr, nullptr, nullptr, T()),
      end_node_(Key(), nullptr, nullptr, nullptr, T())
    {}
    template< class InputIterator >
    Tree(InputIterator first, InputIterator second):
      Tree()
    {
      while (first != second)
      {
        insert(*first++);
      }
    }
    Tree(std::initializer_list< val_type > il):
      Tree()
    {
      auto it = il.begin();
      while (it != il.end())
      {
        insert(*it++);
      }
    }
    Tree(const Tree& rhs):
      Tree()
    {
      cmp_ = rhs.cmp_;
      TreeIterator< Key, T, Compare > it_right(rhs.root_);
      TreeIterator< Key, T, Compare > it_left(rhs.root_);
      while (it_left.node_ != std::addressof(rhs.before_min_) && it_right.node_ != std::addressof(rhs.end_node_))
      {
        insert(std::pair< Key, T >(*it_right++));
        insert(std::pair< Key, T >(*it_left--));
      }
    }
    Tree(Tree&& rhs):
      root_(rhs.root_),
      cmp_(rhs.cmp_),
      size_(rhs.size_),
      before_min_(rhs.before_min_),
      end_node_(rhs.end_node_)
    {
      rhs.root_ = nullptr;
      rhs.size_ = 0;
    }
    ~Tree()
    {
      clear();
    }
    Tree< Key, T, Compare >& operator=(const Tree& rhs)
    {
      if (std::addressof(rhs) != this)
      {
        Tree< Key, T, Compare > temp(rhs);
        swap(temp);
        detail::Node< Key, T >* left = root_;
        detail::Node< Key, T >* right = root_;
        while (left->left_->parent_ && right->right_->parent_)
        {
          if (left->left_->parent_)
          {
            left = left->left_;
          }
          if (right->right_->parent_)
          {
            right = right->right_;
          }
        }
        left->left_ = std::addressof(before_min_);
        right->right_ = std::addressof(end_node_);
      }
      return *this;
    }
    Tree< Key, T, Compare >& operator=(Tree&& rhs)
    {
      if (this != std::addressof(rhs))
      {
        clear();
        swap(rhs);
        detail::Node< Key, T >* left = root_;
        detail::Node< Key, T >* right = root_;
        while (left->left_->parent_ && right->right_->parent_)
        {
          if (left->left_)
          {
            left = left->left_;
          }
          if (right->right_)
          {
            right = right->right_;
          }
        }
        left->left_ = std::addressof(before_min_);
        right->right_ = std::addressof(end_node_);
      }
      return *this;
    }
    size_t size() const noexcept
    {
      return size_;
    }
    bool empty() const noexcept
    {
      return size_ == 0;
    }
    void swap(Tree< Key, T, Compare >& mp)
    {
      std::swap(root_, mp.root_);
      std::swap(cmp_, mp.cmp_);
      std::swap(size_, mp.size_);
      std::swap(before_min_, mp.before_min_);
      std::swap(end_node_, mp.end_node_);
    }
    std::pair< TreeIterator< Key, T, Compare >, bool > insert(const val_type& val)
    {
      detail::Node< Key, T >* node = new detail::Node< Key, T >(val.first, nullptr, nullptr, nullptr, val.second);
      detail::Node< Key, T >* curr_node = root_;
      detail::Node< Key, T >* parent_node = nullptr;
      while (curr_node != nullptr && (curr_node != std::addressof(end_node_) && curr_node != std::addressof(before_min_)))
      {
        if (cmp_(curr_node->key_, node->key_))
        {
          if (!curr_node->right_ || curr_node != std::addressof(end_node_))
          {
            parent_node = curr_node;
          }
          curr_node = curr_node->right_;
        }
        else
        {
          if (!curr_node->left_ || curr_node != std::addressof(end_node_))
          {
            parent_node = curr_node;
          }
          curr_node = curr_node->left_;
        }
      }
      if (!parent_node)
      {
        root_ = node;
        root_->left_ = std::addressof(before_min_);
        root_->right_ = std::addressof(end_node_);
        before_min_.parent_ = root_;
        end_node_.parent_ = root_;
      }
      else if (cmp_(parent_node->key_, node->key_))
      {
        if (parent_node->right_ == std::addressof(end_node_))
        {
          node->right_ = std::addressof(end_node_);
          end_node_.parent_ = node;
        }
        parent_node->right_ = node;
      }
      else if (cmp_(node->key_, parent_node->key_))
      {
        if (parent_node->left_ == std::addressof(before_min_))
        {
          node->left_ = std::addressof(before_min_);
          before_min_.parent_ = node;
        }
        parent_node->left_ = node;
      }
      else
      {
        delete node;
        // splay();
        return std::make_pair< TreeIterator< Key, T, Compare >, bool >(TreeIterator< Key, T, Compare >(parent_node), false);
      }
      node->parent_ = parent_node;
      ++size_;
      //splay();
      return std::make_pair< TreeIterator< Key, T, Compare >, bool >(TreeIterator< Key, T, Compare >(node), true);
    }
    template< class Iterator >
    void insert(Iterator start, Iterator finish)
    {
      while (start != finish)
      {
        insert(*start++);
      }
    }
    TreeIterator< Key, T, Compare > begin() noexcept
    {
      return TreeIterator< Key, T, Compare >(before_min_.parent_);
    }
    TreeIterator< Key, T, Compare > end() noexcept
    {
      return TreeIterator< Key, T, Compare >(std::addressof(end_node_));
    }
    TreeIterator< Key, T, Compare > find(const Key& key)
    {
      TreeIterator< Key, T, Compare > it = lower_bound(key);
      if (it.node_->key_ != key)
      {
        return end();
      }
      return it;
    }
    TreeIterator< Key, T, Compare > upper_bound(const Key& key)
    {
      TreeIterator< Key, T, Compare > it = lower_bound(key);
      if (it.node_->key_ != key)
      {
        return it;
      }
      return ++it;
    }
    TreeIterator< Key, T, Compare > lower_bound(const Key& key)
    {
      detail::Node< Key, T >* curr_node = root_;
      while (curr_node && (curr_node != std::addressof(end_node_) && curr_node != std::addressof(before_min_)))
      {
        if (cmp_(curr_node->key_, key))
        {
          curr_node = curr_node->right_;
        }
        else
        {
          if (!cmp_(key, curr_node->key_) || (curr_node->left_ == std::addressof(before_min_)))
          {
            // splay();
            return TreeIterator< Key, T, Compare >(curr_node);
          }
          curr_node = curr_node->left_;
        }
      }
      return TreeIterator< Key, T, Compare >(curr_node);
    }
    T& operator[](const Key& key)
    {
      return (*((this->insert(std::make_pair(key, T()))).first));
    }
    T& at(const Key& key)
    {
      if (find(key) == end())
      {
        throw std::out_of_range("No data with this key");
      }
      return operator[](key);
    }
    TreeIterator< Key, T, Compare > erase(TreeIterator< Key, T, Compare> pos)
    {
      TreeIterator< Key, T, Compare > delete_node = find(pos.node_->key_);
      if (delete_node == end())
      {
        return delete_node;
      }
      TreeIterator< Key, T, Compare > result = delete_node;
      ++result;
      detail::Node< Key, T >* node = delete_node.node_->right_;
      if (!node || delete_node.node_->right_ == std::addressof(end_node_))
      {
        if ((size_ == 1) || (delete_node.node_->parent_ && !delete_node.node_->parent_->left_))
        {
          delete delete_node.node_;
          --size_;
          return result;
        }
        delete_node.node_->left_->parent_ = delete_node.node_->parent_;
        node = delete_node.node_->left_;
        while (node->right_)
        {
          node = node->right_;
        }
        node->right_ = delete_node.node_->right_;
        if (node)
        {
          node->parent_ = delete_node.node_->left_;
        }
        if (delete_node.node_->parent_)
        {
          if (delete_node.node_->parent_->left_ == delete_node.node_)
          {
            delete_node.node_->parent_->left_ = delete_node.node_->left_;
          }
          else
          {
            delete_node.node_->parent_->right_ = delete_node.node_->left_;
          }
        }
        if (delete_node.node_ == root_)
        {
          root_ = delete_node.node_->left_;
        }
        delete delete_node.node_;
        --size_;
        return result;
      }
      while (node && node->left_)
      {
        node = node->left_;
      }
      if (node)
      {
        node->left_ = delete_node.node_->left_;
        if (node->parent_)
        {
          if (node->parent_->left_ == node)
          {
            node->parent_->left_ = node->right_;
          }
          else
          {
            node->parent_->right_ = node->right_;
          }
          if (node->right_)
          {
            node->right_->parent_ = node->parent_;
          }
          if (!(delete_node.node_->right_ == node))
          {
            node->right_ = delete_node.node_->right_;
          }
        }
        node->parent_ = delete_node.node_->parent_;
      }
      if (delete_node.node_->left_ && delete_node.node_->left_ != node)
      {
        delete_node.node_->left_->parent_ = node;
      }
      if (delete_node.node_->right_ && delete_node.node_->right_ != node)
      {
        delete_node.node_->right_->parent_ = node;
      }
      if (delete_node.node_->parent_)
      {
        if (delete_node.node_->parent_->left_ == delete_node.node_)
        {
          delete_node.node_->parent_->left_ = node;
        }
        else
        {
          delete_node.node_->parent_->right_ = node;
        }
      }
      if (delete_node.node_ == root_)
      {
        root_ = node;
      }
      delete delete_node.node_;
      --size_;
      return result;
    }
    TreeIterator< Key, T, Compare > erase(TreeIterator< Key, T, Compare> start, TreeIterator< Key, T, Compare> finish)
    {
      while (start != finish)
      {
        erase(start++);
      }
      return finish;
    }
    void clear()
    {
      while (!empty())
      {
        erase(TreeIterator< Key, T, Compare >(root_));
      }
    }
    size_t erase(const Key& key)
    {
      size_t count = 0;
      while (erase(find(key)) != end())
      {
        ++count;
      }
      return count;
    }
    std::pair< TreeIterator< Key, T, Compare >, TreeIterator< Key, T, Compare > > equil_range(const Key& key)
    {
      TreeIterator< Key, T, Compare > it = find(key);
      TreeIterator< Key, T, Compare > it2 = it;
      if (it != end())
      {
        ++it2;
      }
      return std::pair< TreeIterator< Key, T, Compare >, TreeIterator< Key, T, Compare > >(it, it2);
    }
    size_t count(const Key& key)
    {
      return (find(key) != end()) ? 1 : 0;
    }
  private:
    detail::Node< Key, T >* root_;
    Compare cmp_;
    size_t size_;
    detail::Node< Key, T > before_min_;
    detail::Node< Key, T > end_node_;
  };
}
#endif