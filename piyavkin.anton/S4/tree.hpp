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
      while (rhs.root_ && (it_right.node_ != rhs.end_node_.parent_->right_ || it_left.node_ != rhs.before_min_.parent_->left_))
      {
        if (rhs.root_ && (it_right.node_ != rhs.end_node_.parent_->right_))
        {
          insert(std::pair< Key, T >(*it_right++));
        }
        if (rhs.root_ && (it_left.node_ != rhs.before_min_.parent_->left_))
        {
          insert(std::pair< Key, T >(*it_left--));
        }
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
        if (root_)
        {
          detail::TreeNode< Key, T >* left = root_;
          detail::TreeNode< Key, T >* right = root_;
          while (left->left_->parent_ || right->right_->parent_)
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
      }
      return *this;
    }
    Tree< Key, T, Compare >& operator=(Tree&& rhs)
    {
      if (this != std::addressof(rhs))
      {
        clear();
        swap(rhs);
        if (root_)
        {
          detail::TreeNode< Key, T >* left = root_;
          detail::TreeNode< Key, T >* right = root_;
          while (left->left_->parent_ || right->right_->parent_)
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
      detail::TreeNode< Key, T >* node = new detail::TreeNode< Key, T >(val.first, nullptr, nullptr, nullptr, val.second);
      detail::TreeNode< Key, T >* curr_node = root_;
      detail::TreeNode< Key, T >* parent_node = nullptr;
      while (curr_node != nullptr && (curr_node != std::addressof(end_node_) && curr_node != std::addressof(before_min_)))
      {
        if (cmp_(curr_node->val_type.first, node->val_type.first))
        {
          if (!curr_node->right_ || curr_node != std::addressof(end_node_))
          {
            parent_node = curr_node;
          }
          curr_node = curr_node->right_;
        }
        else
        {
          if (!cmp_(node->val_type.first, curr_node->val_type.first))
          {
            delete node;
            return std::make_pair< TreeIterator< Key, T, Compare >, bool >(TreeIterator< Key, T, Compare >(curr_node), false);
          }
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
      else if (cmp_(parent_node->val_type.first, node->val_type.first))
      {
        if (parent_node->right_ == std::addressof(end_node_))
        {
          node->right_ = std::addressof(end_node_);
          end_node_.parent_ = node;
        }
        parent_node->right_ = node;
      }
      else if (cmp_(node->val_type.first, parent_node->val_type.first))
      {
        if (parent_node->left_ == std::addressof(before_min_))
        {
          node->left_ = std::addressof(before_min_);
          before_min_.parent_ = node;
        }
        parent_node->left_ = node;
      }
      node->parent_ = parent_node;
      ++size_;
      //splay();
      return std::make_pair< TreeIterator< Key, T, Compare >, bool >(TreeIterator< Key, T, Compare >(node), true);
    }
    TreeIterator< Key, T, Compare > insert(ConstTreeIterator< Key, T, Compare > pos, const val_type& val)
    {
      if ((pos.node_ == std::addressof(end_node_) || cmp_(val.first, pos.node_->val_type.first)) && (!pos.node_->left_ || pos.node_->left_ == std::addressof(before_min_) || cmp_(pos.node_->left_->val_type.first, val.first)) && (pos.node_ == root_ || (isLeftChild(pos.node_) && cmp_(val.first, pos.node_->parent_->val_type.first)) || (isRightChild(pos.node_) && cmp_(pos.node_->parent_->val_type.first, val.first))))
      {
        detail::TreeNode< Key, T >* node = new detail::TreeNode< Key, T >(val.first, pos.node_, pos.node_->left_, pos.node_->parent_, val.second);
        if (pos.node_->left_)
        {
          pos.node_->left_->parent_ = node;
          if (pos.node_->left_ == std::addressof(before_min_))
          {
            node->right_->left_ = nullptr;
          }
        }
        if (isLeftChild(pos.node_))
        {
          pos.node_->parent_->left_ = node;
        }
        else if (isRightChild(pos.node_))
        {
          pos.node_->parent_->right_ = node;
        }
        pos.node_->parent_ = node;
        if (pos.node_ == root_)
        {
          root_ = node;
        }
        ++size_;
        return TreeIterator< Key, T, Compare >(node);
      }
      return insert(val).first;
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
    ConstTreeIterator< Key, T, Compare > cbegin() const noexcept
    {
      return ConstTreeIterator< Key, T, Compare >(before_min_.parent_);
    }
    ConstTreeIterator< Key, T, Compare > cend() const noexcept
    {
      return ConstTreeIterator< Key, T, Compare >(std::addressof(end_node_));
    }
    TreeReverseIterator< Key, T, Compare > rbegin() noexcept
    {
      return TreeReverseIterator< Key, T, Compare >(std::addressof(end_node_));
    }
    TreeReverseIterator< Key, T, Compare > rend() noexcept
    {
      return TreeReverseIterator< Key, T, Compare >(before_min_.parent_);
    }
    ConstTreeReverseIterator< Key, T, Compare > crbegin() const noexcept
    {
      return ConstTreeReverseIterator< Key, T, Compare >(std::addressof(end_node_));
    }
    ConstTreeReverseIterator< Key, T, Compare > crend() const noexcept
    {
      return ConstTreeReverseIterator< Key, T, Compare >(before_min_.parent_);
    }
    TreeIterator< Key, T, Compare > find(const Key& key)
    {
      TreeIterator< Key, T, Compare > it = lower_bound(key);
      if (it.node_->val_type.first != key)
      {
        return end();
      }
      return it;
    }
    ConstTreeIterator< Key, T, Compare > find(const Key& key) const
    {
      ConstTreeIterator< Key, T, Compare > it = lower_bound(key);
      if (it.node_->val_type.first != key)
      {
        return cend();
      }
      return it;
    }
    TreeIterator< Key, T, Compare > upper_bound(const Key& key)
    {
      TreeIterator< Key, T, Compare > it = lower_bound(key);
      if (it.node_->val_type.first != key)
      {
        return it;
      }
      return ++it;
    }
    ConstTreeIterator< Key, T, Compare > upper_bound(const Key& key) const
    {
      ConstTreeIterator< Key, T, Compare > it = lower_bound(key);
      if (it.node_->val_type.first != key)
      {
        return it;
      }
      return ++it;
    }
    TreeIterator< Key, T, Compare > lower_bound(const Key& key)
    {
      detail::TreeNode< Key, T >* curr_node = root_;
      while (curr_node && (curr_node != std::addressof(end_node_) && curr_node != std::addressof(before_min_)))
      {
        if (cmp_(curr_node->val_type.first, key))
        {
          if (!curr_node->right_)
          {
            TreeIterator< Key, T, Compare > it(curr_node);
            return ++it;
          }
          curr_node = curr_node->right_;
        }
        else
        {
          if (!cmp_(key, curr_node->val_type.first) || (curr_node->left_ == std::addressof(before_min_)))
          {
            // splay();
            return TreeIterator< Key, T, Compare >(curr_node);
          }
          curr_node = curr_node->left_;
        }
      }
      return TreeIterator< Key, T, Compare >(curr_node);
    }
    ConstTreeIterator< Key, T, Compare > lower_bound(const Key& key) const
    {
      detail::TreeNode< Key, T >* curr_node = root_;
      while (curr_node && (curr_node != std::addressof(end_node_) && curr_node != std::addressof(before_min_)))
      {
        if (cmp_(curr_node->val_type.first, key))
        {
          if (!curr_node->right_)
          {
            ConstTreeIterator< Key, T, Compare > it(curr_node);
            return ++it;
          }
          curr_node = curr_node->right_;
        }
        else
        {
          if (!cmp_(key, curr_node->val_type.first) || (curr_node->left_ == std::addressof(before_min_)))
          {
            // splay();
            return ConstTreeIterator< Key, T, Compare >(curr_node);
          }
          curr_node = curr_node->left_;
        }
      }
      return ConstTreeIterator< Key, T, Compare >(curr_node);
    }
    T& operator[](const Key& key)
    {
      return (((this->insert(std::make_pair(key, T()))).first)->second);
    }
    T& at(const Key& key)
    {
      if (find(key) == end())
      {
        throw std::out_of_range("No data with this key");
      }
      return operator[](key);
    }
    const T& at(const Key& key) const
    {
      if (find(key) == cend())
      {
        throw std::out_of_range("No data with this key");
      }
      return find(key)->second;
    }
    TreeIterator< Key, T, Compare > erase(TreeIterator< Key, T, Compare> pos)
    {
      TreeIterator< Key, T, Compare > delete_node = find(pos.node_->val_type.first);
      if (delete_node == end())
      {
        return delete_node;
      }
      TreeIterator< Key, T, Compare > result = delete_node;
      ++result;
      detail::TreeNode< Key, T >* node = delete_node.node_->right_;
      if (!node || delete_node.node_->right_ == end_node_.parent_->right_)
      {
        if ((size_ == 1) || (delete_node.node_->parent_ && !delete_node.node_->parent_->left_))
        {
          if (size_ != 1 && delete_node.node_->right_)
          {
            delete_node.node_->parent_->right_ = std::addressof(end_node_);
          }
          delete delete_node.node_;
          --size_;
          return result;
        }
        node = delete_node.node_->left_;
        while (node && node->right_)
        {
          node = node->right_;
        }
        if (node)
        {
          if (node != delete_node.node_->left_)
          {
            node->left_ = delete_node.node_->left_;
            delete_node.node_->left_->parent_ = node;
          }
          if (isLeftChild(node))
          {
            node->parent_->left_ = nullptr;
          }
          else
          {
            node->parent_->right_ = nullptr;
          }
          node->parent_ = delete_node.node_->parent_;
        }
        if (delete_node.node_->right_)
        {
          end_node_.parent_ = node;
          node->right_ = std::addressof(end_node_);
        }
        if (delete_node.node_->parent_)
        {
          if (isLeftChild(delete_node.node_))
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
    template< class... Args >
    std::pair< TreeIterator< Key, T, Compare >, bool > emplace(Args&&... args)
    {
      return insert(val_type(std::forward< Args >(args)...));
    }
    template< class... Args >
    TreeIterator< Key, T, Compare > emplace_hint(TreeIterator< Key, T, Compare > pos, Args&&... args)
    {
      return insert(pos, val_type(std::forward< Args >(args)...));
    }
  private:
    detail::TreeNode< Key, T >* root_;
    Compare cmp_;
    size_t size_;
    detail::TreeNode< Key, T > before_min_;
    detail::TreeNode< Key, T > end_node_;
    bool isLeftChild(detail::TreeNode< Key, T >* node) const
    {
      return (node->parent_ && node->parent_->left_ == node);
    }
    bool isRightChild(detail::TreeNode< Key, T >* node) const
    {
      return (node->parent_ && node->parent_->right_ == node);
    }
  };
}
#endif