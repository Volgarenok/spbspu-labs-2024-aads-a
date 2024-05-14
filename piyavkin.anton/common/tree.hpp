#ifndef TREE_HPP
#define TREE_HPP
#include <cstddef>
#include "treeiterator.hpp"
#include "../S5/specialiterator.hpp"

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
      before_min_(Key(), nullptr, nullptr, std::addressof(end_node_), T()),
      end_node_(Key(), nullptr, nullptr, std::addressof(before_min_), T())
    {}
    template< class InputIterator >
    Tree(InputIterator first, InputIterator second):
      Tree()
    {
      try
      {
        while (first != second)
        {
          insert(*first++);
        }
      }
      catch (...)
      {
        clear();
      }
    }
    Tree(std::initializer_list< val_type > il):
      Tree(il.begin(), il.end())
    {}
    Tree(const Tree& rhs):
      Tree()
    {
      try
      {
        ConstTreeIterator< Key, T, Compare > it_right(rhs.root_);
        ConstTreeIterator< Key, T, Compare > it_left(rhs.root_);
        while (rhs.root_ && (it_right != rhs.cend() || it_left != --rhs.cbegin()))
        {
          if (it_right != rhs.cend())
          {
            insert_impl(std::pair< Key, T >(*it_right++));
          }
          if (it_left != --rhs.cbegin())
          {
            insert_impl(std::pair< Key, T >(*it_left--));
          }
        }
      }
      catch (...)
      {
        clear();
      }
    }
    Tree(Tree&& rhs):
      root_(rhs.root_),
      cmp_(rhs.cmp_),
      size_(rhs.size_),
      before_min_(Key(), nullptr, nullptr, rhs.before_min_.parent_, T()),
      end_node_(Key(), nullptr, nullptr, rhs.end_node_.parent_, T())
    {
      rhs.root_ = nullptr;
      rhs.size_ = 0;
      end_node_.parent_->right_ = std::addressof(end_node_);
      before_min_.parent_->left_ = std::addressof(before_min_);
      rhs.before_min_.parent_ = std::addressof(rhs.end_node_);
      rhs.end_node_.parent_ = std::addressof(rhs.before_min_);
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
      }
      return *this;
    }
    Tree< Key, T, Compare >& operator=(Tree&& rhs)
    {
      if (this != std::addressof(rhs))
      {
        clear();
        swap(rhs);
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
      detail::TreeNode< Key, T > temp1 = end_node_;
      detail::TreeNode< Key, T > temp2 = before_min_;
      end_node_.parent_ = mp.end_node_.parent_;
      end_node_.parent_->right_ = std::addressof(end_node_);
      before_min_.parent_ = mp.before_min_.parent_;
      before_min_.parent_->left_ = std::addressof(before_min_);
      mp.before_min_.parent_ = temp2.parent_;
      mp.end_node_.parent_ = temp1.parent_;
      if (mp.size_ != 0)
      {
        mp.before_min_.parent_->left_ = std::addressof(mp.before_min_);
        mp.end_node_.parent_->right_ = std::addressof(mp.end_node_);
      }
    }
    std::pair< TreeIterator< Key, T, Compare >, bool > insert(const val_type& val)
    {
      auto res = insert_impl(val);
      splay(res.first.node_);
      return res;
    }
    std::pair< TreeIterator< Key, T, Compare >, bool > unsplay_insert(const val_type& val)
    {
      return insert_impl(val);
    }
    TreeIterator< Key, T, Compare > insert(ConstTreeIterator< Key, T, Compare > pos, const val_type& val)
    {
      if (cmpLeftNode(pos.node_, val.first) && cmpNodeRight(pos.node_, val.first) && cmpNodeParent(pos.node_, val.first))
      {
        detail::TreeNode< Key, T >* node = nullptr;
        node = new detail::TreeNode< Key, T >(val.first, pos.node_, pos.node_->left_, pos.node_->parent_, val.second);
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
        pos.node_->left_ = nullptr;
        if (pos.node_ == root_ || !root_)
        {
          if (!root_)
          {
            node->parent_ = nullptr;
            node->left_ = std::addressof(before_min_);
            before_min_.parent_ = node;
          }
          root_ = node;
        }
        ++size_;
        splay(node);
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
      return ConstTreeIterator< Key, T, Compare >(const_cast< detail::TreeNode< Key, T >* >(std::addressof(end_node_)));
    }
    std::reverse_iterator< TreeIterator< Key, T, Compare > > rbegin() noexcept
    {
      return std::reverse_iterator< TreeIterator< Key, T, Compare > >(end());
    }
    std::reverse_iterator< TreeIterator< Key, T, Compare > > rend() noexcept
    {
      return std::reverse_iterator< TreeIterator< Key, T, Compare > >(begin());
    }
    std::reverse_iterator< ConstTreeIterator< Key, T, Compare > > crbegin() const noexcept
    {
      return std::reverse_iterator< ConstTreeIterator< Key, T, Compare > >(cend());
    }
    std::reverse_iterator< ConstTreeIterator< Key, T, Compare > > crend() const noexcept
    {
      return std::reverse_iterator< ConstTreeIterator< Key, T, Compare > >(cbegin());
    }
    TreeIterator< Key, T, Compare > find(const Key& key)
    {
      auto it = find_impl(key);
      if (it != end())
      {
        splay(it.node_);
      }
      return it;
    }
    ConstTreeIterator< Key, T, Compare > find(const Key& key) const
    {
      return find_impl(key);
    }
    TreeIterator< Key, T, Compare > upper_bound(const Key& key)
    {
      TreeIterator< Key, T, Compare > it = lower_bound_impl(key);
      if (!cmp(it.node_->val_type.first, key) && !cmp(key, it.node_->val_type.first))
      {
        if (it != end())
        {
          splay(it.node_);
        }
        return it;
      }
      ++it;
      if (it != end())
      {
        splay(it.node_);
      }
      return it;
    }
    ConstTreeIterator< Key, T, Compare > upper_bound(const Key& key) const
    {
      ConstTreeIterator< Key, T, Compare > it = lower_bound(key);
      if (equal_key(it.node_->val_type.first, key))
      {
        return it;
      }
      return ++it;
    }
    TreeIterator< Key, T, Compare > lower_bound(const Key& key)
    {
      auto it = static_cast< const Tree< Key, T, Compare >& >(*this).lower_bound(key);
      if (it != end())
      {
        splay(it.node_);
      }
      return TreeIterator< Key, T, Compare >(const_cast< detail::TreeNode< Key, T >* >(it.node_));
    }
    ConstTreeIterator< Key, T, Compare > lower_bound(const Key& key) const
    {
      return lower_bound_impl(key);
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
    TreeIterator< Key, T, Compare > erase(TreeIterator< Key, T, Compare > pos)
    {
      TreeIterator< Key, T, Compare > delete_node = find_impl(pos.node_->val_type.first);
      if (delete_node == end())
      {
        return delete_node;
      }
      TreeIterator< Key, T, Compare > result = delete_node;
      ++result;
      detail::TreeNode< Key, T >* node = delete_node.node_->right_;
      if (!node || delete_node.node_->right_ == std::addressof(end_node_))
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
          if (delete_node.node_->right_)
          {
            end_node_.parent_ = node;
            node->right_ = std::addressof(end_node_);
          }
        }
        if (isLeftChild(delete_node.node_))
        {
          delete_node.node_->parent_->left_ = node;
        }
        else if (isRightChild(delete_node.node_))
        {
          delete_node.node_->parent_->right_ = node;
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
        if (isLeftChild(node))
        {
          node->parent_->left_ = node->right_;
        }
        else if (isRightChild(node))
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
      if (isLeftChild(delete_node.node_))
      {
        delete_node.node_->parent_->left_ = node;
      }
      else if (isRightChild(delete_node.node_))
      {
        delete_node.node_->parent_->right_ = node;
      }
      if (delete_node.node_ == root_)
      {
        root_ = node;
      }
      delete delete_node.node_;
      --size_;
      return result;
    }
    TreeIterator< Key, T, Compare > erase(TreeIterator< Key, T, Compare > start, TreeIterator< Key, T, Compare > finish)
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
    std::pair< ConstTreeIterator< Key, T, Compare >, ConstTreeIterator< Key, T, Compare > > equal_range(const Key& key) const
    {
      ConstTreeIterator< Key, T, Compare > it = find_impl(key);
      if (it == cend())
      {
        return std::make_pair< ConstTreeIterator< Key, T, Compare >, ConstTreeIterator< Key, T, Compare > >(cend(), cend());
      }
      ConstTreeIterator< Key, T, Compare > it2 = it;
      ConstTreeIterator< Key, T, Compare > temp = --it;
      ++it;
      while (temp != --cbegin() && equal_key(it.node_->val_type.first, temp.node_->val_type.first))
      {
        --it;
        --temp;
      }
      temp = ++it2;
      --it2;
      while (temp != cend() && equal_key(it2.node_->val_type.first, temp.node_->val_type.first))
      {
        ++it2;
        ++temp;
      }
      return std::pair< ConstTreeIterator< Key, T, Compare >, ConstTreeIterator< Key, T, Compare > >(it, ++it2);
    }
    std::pair< TreeIterator< Key, T, Compare >, TreeIterator< Key, T, Compare > > equal_range(const Key& key)
    {
      auto pair = static_cast< const Tree< Key, T, Compare >& >(*this).equal_range(key);
      TreeIterator< Key, T, Compare > it1(const_cast< detail::TreeNode< Key, T >* >(pair.first.node_));
      TreeIterator< Key, T, Compare > it2(const_cast< detail::TreeNode< Key, T >* >(pair.second.node_));
      auto res = it1;
      while (it1 != it2)
      {
        detail::TreeNode< Key, T >* splayNode = it1.node_;
        ++it1;
        splay(splayNode);
      }
      return std::pair< TreeIterator< Key, T, Compare >, TreeIterator< Key, T, Compare > >(res, it2);
    }
    size_t count(const Key& key) const
    {
      std::pair< ConstTreeIterator< Key, T, Compare >, ConstTreeIterator< Key, T, Compare > > pair = equal_range(key);
      size_t sum = 0;
      while (pair.first != pair.second)
      {
        ++sum;
        ++pair.first;
      }
      return sum;
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
    ConstLnrIterator< Key, T, Compare > clbegin() const noexcept
    {
      return ConstLnrIterator< Key, T, Compare >(root_, before_min_.parent_, false);
    }
    ConstLnrIterator< Key, T, Compare > clend() const noexcept
    {
      return ConstLnrIterator< Key, T, Compare >(root_, const_cast< detail::TreeNode< Key, T >* >(std::addressof(end_node_)), true);
    }
    ConstRnlIterator< Key, T, Compare > clrbegin() const noexcept
    {
      return ConstRnlIterator< Key, T, Compare >(root_, end_node_.parent_, false);
    }
    ConstRnlIterator< Key, T, Compare > clrend() const noexcept
    {
      return ConstRnlIterator< Key, T, Compare >(root_, const_cast< detail::TreeNode< Key, T >* >(std::addressof(before_min_)), true);
    }
    ConstBreadthIterator< Key, T, Compare > cbbegin() const noexcept
    {
      return ConstBreadthIterator< Key, T, Compare >(root_, root_, false);
    }
    ConstBreadthIterator< Key, T, Compare > cbend() const noexcept
    {
      return ConstBreadthIterator< Key, T, Compare >(root_, root_, true);
    }
    template< class F >
    F& traverse_lnr(F& f) const
    {
      if (empty())
      {
        throw std::logic_error("<EMPTY>");
      }
      for (auto it = clbegin(); it != clend(); ++it)
      {
        f(*it);
      }
      return f;
    }
    template< class F >
    F& traverse_lnr(F& f)
    {
      return static_cast< const Tree< Key, T, Compare >& >(*this).traverse_lnr(f);
    }
    template< class F >
    F& traverse_rnl(F& f) const
    {
      if (empty())
      {
        throw std::logic_error("<EMPTY>");
      }
      for (auto it = clrbegin(); it != clrend(); ++it)
      {
        f(*it);
      }
      return f;
    }
    template< class F >
    F& traverse_rnl(F& f)
    {
      return static_cast< const Tree< Key, T, Compare >& >(*this).traverse_rnl(f);
    }
    template< class F >
    F& traverse_breadth(F& f) const
    {
      if (empty())
      {
        throw std::logic_error("<EMPTY>");
      }
      for (auto it = cbbegin(); it != cbend(); ++it)
      {
        f(*it);
      }
      return f;
    }
    template< class F >
    F& traverse_breadth(F& f)
    {
      return static_cast< const Tree< Key, T, Compare >& >(*this).traverse_breadth(f);
    }
  private:
    detail::TreeNode< Key, T >* root_;
    Compare cmp_;
    size_t size_;
    detail::TreeNode< Key, T > before_min_;
    detail::TreeNode< Key, T > end_node_;
    bool isLeftChild(const detail::TreeNode< Key, T >* node) const
    {
      return (node->parent_ && node->parent_->left_ == node);
    }
    bool isRightChild(const detail::TreeNode< Key, T >* node) const
    {
      return (node->parent_ && node->parent_->right_ == node);
    }
    bool cmpLeftNode(const detail::TreeNode< Key, T >* node, const Key& key) const
    {
      return (!node->left_ || node->left_ == std::addressof(before_min_) || cmp_(node->left_->val_type.first, key));
    }
    bool cmpNodeRight(const detail::TreeNode< Key, T >* node, const Key& key) const
    {
      return (!node->right_ || node->right_ == std::addressof(end_node_) || cmp_(key, node->right_->val_type.first));
    }
    bool cmpNodeParent(const detail::TreeNode< Key, T >* node, const Key& key) const
    {
      return (!root_ || node == root_ || isCorrectLeftChild(node, key) || isCorrectRightChild(node, key));
    }
    bool isCorrectLeftChild(const detail::TreeNode< Key, T >* node, const Key& key) const
    {
      return isLeftChild(node) && cmp_(key, node->parent_->val_type.first);
    }
    bool isCorrectRightChild(const detail::TreeNode< Key, T >* node, const Key& key) const
    {
      return isRightChild(node) && cmp_(node->parent_->val_type.first, key);
    }
    void zig(detail::TreeNode< Key, T >* node)
    {
      detail::TreeNode< Key, T >* temp = node->left_;
      node->left_ = temp->right_;
      if (temp->right_)
      {
        temp->right_->parent_ = node;
      }
      temp->parent_ = node->parent_;
      temp->right_ = node;
      if (!node->parent_)
      {
        root_ = temp;
      }
      else if (isRightChild(node))
      {
        node->parent_->right_ = temp;
      }
      else
      {
        node->parent_->left_ = temp;
      }
      node->parent_ = temp;
    }
    void zag(detail::TreeNode< Key, T >* node)
    {
      detail::TreeNode< Key, T >* temp = node->right_;
      node->right_ = temp->left_;
      if (temp->left_)
      {
        temp->left_->parent_ = node;
      }
      temp->parent_ = node->parent_;
      temp->left_ = node;
      if (!node->parent_)
      {
        root_ = temp;
      }
      else if (isRightChild(node))
      {
        node->parent_->right_ = temp;
      }
      else
      {
        node->parent_->left_ = temp;
      }
      node->parent_ = temp;
    }
    void splay(detail::TreeNode< Key, T >* node)
    {
      while (node->parent_)
      {
        if (!node->parent_->parent_)
        {
          if (isLeftChild(node))
          {
            zig(node->parent_);
          }
          else
          {
            zag(node->parent_);
          }
        }
        else if (isLeftChild(node->parent_) && isLeftChild(node))
        {
          zig(node->parent_);
          zig(node->parent_);
        }
        else if (isLeftChild(node) && isRightChild(node->parent_))
        {
          zig(node->parent_);
          zag(node->parent_);
        }
        else if (isRightChild(node) && isLeftChild(node->parent_))
        {
          zag(node->parent_);
          zig(node->parent_);
        }
        else
        {
          zag(node->parent_);
          zag(node->parent_);
        }
      }
    }
    std::pair< TreeIterator< Key, T, Compare >, bool > insert_impl(const val_type& val)
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
      return std::make_pair< TreeIterator< Key, T, Compare >, bool >(TreeIterator< Key, T, Compare >(node), true);
    }
    ConstTreeIterator< Key, T, Compare > lower_bound_impl(const Key& key) const
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
            return ConstTreeIterator< Key, T, Compare >(curr_node);
          }
          curr_node = curr_node->left_;
        }
      }
      return ConstTreeIterator< Key, T, Compare >(curr_node);
    }
    TreeIterator< Key, T, Compare > find_impl(const Key& key)
    {
      auto it = static_cast< const Tree< Key, T, Compare >& >(*this).find_impl(key);
      return TreeIterator< Key, T, Compare >(const_cast< detail::TreeNode< Key, T >* >(it.node_));
    }
    ConstTreeIterator< Key, T, Compare > find_impl(const Key& key) const
    {
      ConstTreeIterator< Key, T, Compare > it = lower_bound_impl(key);
      if (!it.node_ || !equal_key(it.node_->val_type.first, key))
      {
        return cend();
      }
      return it;
    }
    bool equal_key(const Key& key1, const Key& key2) const
    {
      return !cmp_(key1, key2) && !cmp_(key2, key1);
    }
  };
}
#endif

