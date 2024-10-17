#ifndef TREE_HPP
#define TREE_HPP

#include <functional>
#include <utility>
#include <list>
#include <initializer_list>

#include "treeNode.hpp"
#include "iterBase.hpp"

namespace rebdev
{
  template < class Key, class Value, class Compare = std::less< Key > >
  class AVLTree
  {
    using pair = std::pair< const Key, Value >;
    using node = TreeNode< pair >;

    public:
      using iterator = BaseIter< Key, Value, Compare, pair, node >;
      using const_iterator = BaseIter< Key, Value, Compare, const pair, const node >;

      AVLTree():
        headNode_(new node{nullptr, nullptr, nullptr, pair{}}),
        size_(0)
      {}
      template < class InIter >
      AVLTree(InIter first, InIter last, const Compare & comp = Compare()):
        headNode_(new node{nullptr, nullptr, nullptr, pair{}}),
        size_(0),
        comp_(comp)
      {
        insert(first, last);
      }
      AVLTree(const AVLTree & tree):
        headNode_(new node{nullptr, nullptr, nullptr, pair{}}),
        size_(0),
        comp_(tree.comp_)
      {
        (*this)=tree;
      }
      AVLTree(AVLTree && tree):
        headNode_(new node{nullptr, nullptr, nullptr, pair{}}),
        size_(0)
      {
        swap(tree);
      }
      AVLTree(std::initializer_list< pair > il, const Compare & comp = Compare()):
        headNode_(new node{nullptr, nullptr, nullptr, pair{}}),
        size_(0),
        comp_(comp)
      {
        insert(il.begin(), il.end());
      }
      ~AVLTree() noexcept
      {
        clear();
        delete headNode_;
      }
      AVLTree & operator=(const AVLTree & tree)
      {
        AVLTree treeToSwap;
        auto it = tree.cend();
        --it;
        while (it != tree.cbegin())
        {
          treeToSwap.insert(*it);
          --it;
        }
        if (it != tree.cend())
        {
          treeToSwap.insert(*it);
        }
        swap(treeToSwap);
        return *this;
      }
      AVLTree & operator=(AVLTree && tree)
      {
        swap(tree);
        return *this;
      }
      iterator begin() const
      {
        return iterator(beginBase());
      }
      iterator end() const
      {
        return iterator(headNode_);
      }
      const_iterator cbegin() const
      {
        return const_iterator(beginBase());
      }
      const_iterator cend() const
      {
        return const_iterator(headNode_);
      }
      bool empty() const noexcept
      {
        return (size_ == 0);
      }
      size_t size() const noexcept
      {
        return size_;
      }
      Value & operator[](const Key & k)
      {
        iterator it = find(k);
        if (it != end())
        {
          return ((*it).second);
        }
        std::pair< iterator, bool > it2 = insert(pair{k, Value{}});
        return ((*(it2.first)).second);
      }
      Value & operator[](Key && k)
      {
        iterator it = find(k);
        if (it != end())
        {
          return ((*it).second);
        }
        std::pair< iterator, bool > it2 = insert(pair{std::move(k), Value{}});
        return ((*(it2.first)).second);
      }
      Value & at (const Key & k)
      {
        iterator it = find(k);
        if (it == end())
        {
          throw std::out_of_range("Can't find element in tree by method at");
        }
        return ((*it).second);
      }
      const Value & at (const Key & k) const
      {
        const_iterator it = find(k);
        if (it = cend())
        {
          throw std::out_of_range("Can't find element in tree by method at");
        }
        return ((*it).second);
      }
      void swap(AVLTree & tree)
      {
        std::swap(headNode_, tree.headNode_);
        std::swap(size_, tree.size_);
        std::swap(comp_, tree.comp_);
      }
      void clear() noexcept
      {
        iterator it = begin();
        while (it != end())
        {
          node * nodeToDel = it.node_;
          ++it;
          delete nodeToDel;
        }
        size_ = 0;
      }
      std::pair< iterator, bool > insert(const pair & p)
      {
        iterator it = find(p.first);
        bool orig = (it == end());
        if (orig)
        {
          node * newNode = new node{nullptr, nullptr, nullptr, p};
          if ((headNode_->right) == nullptr)
          {
            (headNode_->right) = newNode;
            (newNode->parent) = headNode_;
          }
          else
          {
            node * nodeNow = headNode_->right;
            while ((newNode->parent) == nullptr)
            {
              if (comp_(((newNode->data).first), ((nodeNow->data).first)))
              {
                if ((nodeNow->left) != nullptr)
                {
                  nodeNow = (nodeNow->left);
                }
                else
                {
                  (newNode->parent) = nodeNow;
                  (nodeNow->left) = newNode;
                }
              }
              else
              {
                if ((nodeNow->right) != nullptr)
                {
                  nodeNow = (nodeNow->right);
                }
                else
                {
                  (newNode->parent) = nodeNow;
                  (nodeNow->right) = newNode;
                }
              }
            }
          }
          it = iterator(newNode);
          ++size_;
        }
        return std::pair< iterator, bool >{it, !orig};
      }
      template < class InIter >
      void insert (InIter first, InIter last)
      {
        InIter it = first;
        while (it != last)
        {
          insert(*it);
          ++it;
        }
      }
      iterator erase (iterator position)
      {
        if (position == end())
        {
          return end();
        }
        node * it = position.node_;
        if (((it->left) == nullptr) && ((it->right) == nullptr))
        {
          if ((it->parent->left) == it)
          {
            (it->parent->left) = nullptr;
          }
          else
          {
            (it->parent->right) = nullptr;
          }
          auto it2 = (++(iterator(it)));
          delete it;
          it = (it2.node_);
        }
        else
        {
          if ((it->left) != nullptr)
          {
            while ((it->left) != nullptr)
            {
              it = (it->left);
              while ((it->right) != nullptr)
              {
                it = (it->right);
              }
            }
          }
          else
          {
            while ((it->right) != nullptr)
            {
              it = (it->right);
              while ((it->left) != nullptr)
              {
                it = (it->left);
              }
            }
          }
          if ((position.node_->left) != it)
          {
            (it->left) = (position.node_->left);
          }
          if ((position.node_->right) != it)
          {
            (it->right) = (position.node_->right);
          }
          (it->parent) = (position.node_->parent);
          if ((it->left) != nullptr)
          {
            (it->left->parent) = it;
          }
          if ((it->right) != nullptr)
          {
            (it->right->parent) = it;
          }
          if (((position.node_)->parent->right) == position.node_)
          {
            ((position.node_)->parent->right) = it;
          }
          else
          {
            ((position.node_)->parent->left) = it;
          }
          delete position.node_;
        }
        --size_;
        return iterator(it);
      }
      size_t erase (const Key & k)
      {
        size_t num = 0;
        iterator it = find(k);
        while (it != end())
        {
          erase(it);
          ++num;
          it = find(k);
        }
        return num;
      }
      iterator erase (iterator first, iterator last)
      {
        iterator it = first;
        while (it != last)
        {
          auto it2 = it;
          ++it2;
          erase(it);
          it = it2;
        }
        return iterator(last);
      }
      iterator find(const Key & k)
      {
        return iterator(findBase(k));
      }
      const_iterator find(const Key & k) const
      {
        return const_iterator(findBase(k));
      }
      size_t count (const Key & k) const
      {
        size_t num = 0;
        iterator it = begin();
        while (it != end())
        {
          num += ((*it).first == k);
          ++it;
        }
        return num;
      }
      iterator lower_bound (const Key & k)
      {
        return iterator(boundBase(k, [&](const Key & keyNow, const Key & k)
          {
            return comp_(keyNow, k);
          }));
      }
      const_iterator lower_bound (const Key & k) const
      {
        return const_iterator(boundBase(k, [&](const Key & keyNow, const Key & k)
          {
            return comp_(keyNow, k);
          }));
      }
      iterator upper_bound (const Key & k)
      {
        return iterator(boundBase(k, [&](const Key & keyNow, const Key & k)
          {
            return !comp_(keyNow, k);
          }));
      }
      const_iterator upper_bound (const Key & k) const
      {
        return const_iterator(boundBase(k, [&](const Key & keyNow, const Key & k)
          {
            return !comp_(keyNow, k);
          }));
      }
      std::pair< const_iterator, const_iterator > equal_range (const Key & k) const
      {
        using c_i = const_iterator;
        std::pair< node *, node * > nodePair = equal_rangeBase(k);
        return std::pair< c_i, c_i >{c_i(nodePair.first), c_i(nodePair.second)};
      }
      std::pair< iterator, iterator > equal_range (const Key & k)
      {
        std::pair< node *, node * > nodePair = equal_rangeBase(k);
        return std::pair< iterator, iterator >{iterator(nodePair.first), iterator(nodePair.second)};
      }

    private:
      node * headNode_;
      size_t size_;
      Compare comp_;

      node * findBase(const Key & k) const
      {
        node * nodeNow = headNode_;
        while ((nodeNow->data.first) != k)
        {
          if (comp_((nodeNow->data.first), k))
          {
            nodeNow = (nodeNow->right);
          }
          else
          {
            nodeNow = (nodeNow->left);
          }
          if (nodeNow == nullptr)
          {
            return headNode_;
          }
        }
        return nodeNow;
      }
      node * beginBase() const
      {
        node * beginNode = headNode_;
        while (((beginNode->left) != nullptr) || ((beginNode->right) != nullptr))
        {
          while ((beginNode->left) != nullptr)
          {
            beginNode = (beginNode->left);
          }
          if ((beginNode->right) != nullptr)
          {
            beginNode = (beginNode->right);
          }
        }
        return beginNode;
      }
      std::pair< node *, node * > equal_rangeBase(const Key & k) const
      {
        iterator firstIt = find(k);
        iterator secondIt;
        if (firstIt == end())
        {
          firstIt = upper_bound(k);
          secondIt = upper_bound(k);
        }
        else
        {
          secondIt = firstIt;
          ++secondIt;
        }
        return std::pair< node *, node * >{firstIt.node, secondIt.node};
      }
      using lambda = const std::function< bool(const Key & nowKey, const Key & key) >;
      node * boundBase(const Key & k, lambda pred) const
      {
        node * nodeNow = headNode_->right;
        while (!pred(((nodeNow->data).first), k))
        {
          if (pred(((nodeNow->data).first), k))
          {
            nodeNow = (nodeNow->left);
          }
          else
          {
            nodeNow = (nodeNow->right);
          }
          if (nodeNow == nullptr)
          {
            return headNode_;
          }
        }
        return nodeNow;
      }
  };
}

#endif
