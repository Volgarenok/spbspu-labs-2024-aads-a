#ifndef MAP_HPP
#define MAP_HPP
#include <algorithm>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <stack.hpp>
#include <queue.hpp>

namespace zaitsev
{
  template< typename Key, typename T, typename Compare = std::less< Key > >
  class Map
  {
    using val_t = std::pair< const Key, T >;
    struct Node;
    Compare comparator_;
    Node* fakeroot_;
    size_t size_;
    struct Node
    {
      val_t val_;
      int height_;
      Node* left_;
      Node* right_;
      Node* parent_;

      Node():
        val_(),
        height_(0),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr)
      {}
      template< class... Args  >
      explicit Node(int height, Args&&... args):
        val_(std::forward< Args >(args)...),
        height_(height),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr)
      {}
      Node(const Node& other):
        val_(other.val_),
        height_(0),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr)
      {}
      Node(Node&& other):
        val_(std::move(other.val_)),
        height_(height_),
        left_(other.left_),
        right_(other.right_),
        parent_(other.parent_)
      {
        other.height_ = 0;
        other.left_ = nullptr;
        other.right_ = nullptr;
        other.parent_ = nullptr;
      }
      static int depth(Node* node)
      {
        return node ? node->height_ + 1 : 0;
      }
      void clear()
      {
        height_ = 0;
        left_ = nullptr;
        right_ = nullptr;
        parent_ = nullptr;
      }
      bool updateHeight()
      {
        int old_height = height_;
        height_ = std::max(depth(left_), depth(right_));
        return old_height != height_;
      }
      void rotate()
      {
        Node* root = this;
        Node* parent = root->parent_;
        bool left = (root == parent->left_);
        if (depth(left_) < depth(right_))
        {
          root = (depth(right_->left_) <= depth(right_->right_)) ? root->rotateLeft() : root->rotateLeftRight();
        }
        else
        {
          root = (depth(left_->right_) <= depth(left_->left_)) ? root->rotateRight() : root->rotateRightLeft();
        }
        root->parent_ = parent;
        (left ? parent->left_ : parent->right_) = root;
        return;
      }
    private:
      Node* rotateLeft()
      {
        Node* root = this;
        Node* new_root = root->right_;
        root->right_ = new_root->left_;
        if (new_root->left_)
        {
          new_root->left_->parent_ = root;
        }
        new_root->left_ = root;
        root->parent_ = new_root;
        root->updateHeight();
        new_root->updateHeight();
        return new_root;
      }
      Node* rotateRight()
      {
        Node* root = this;
        Node* new_root = root->left_;
        root->left_ = new_root->right_;
        if (new_root->right_)
        {
          new_root->right_->parent_ = root;
        }
        new_root->right_ = root;
        root->parent_ = new_root;
        root->updateHeight();
        new_root->updateHeight();
        return new_root;
      }
      Node* rotateLeftRight()
      {
        Node* root = this;
        Node* new_root = root->right_->left_;
        root->right_->left_ = new_root->right_;
        if (new_root->right_)
        {
          new_root->right_->parent_ = root->right_;
        }
        new_root->right_ = root->right_;
        root->right_->parent_ = new_root;
        root->right_ = new_root->left_;
        if (new_root->left_)
        {
          new_root->left_->parent_ = root;
        }
        new_root->left_ = root;
        root->parent_ = new_root;
        root->updateHeight();
        new_root->right_->updateHeight();
        new_root->updateHeight();
        return new_root;
      }
      Node* rotateRightLeft()
      {
        Node* root = this;
        Node* new_root = root->left_->right_;
        root->left_->right_ = new_root->left_;
        if (new_root->left_)
        {
          new_root->left_->parent_ = root->left_;
        }
        new_root->left_ = root->left_;
        root->left_->parent_ = new_root;
        root->left_ = new_root->right_;
        if (new_root->right_)
        {
          new_root->right_->parent_ = root;
        }
        new_root->right_ = root;
        root->parent_ = new_root;
        root->updateHeight();
        new_root->left_->updateHeight();
        new_root->updateHeight();
        return new_root;
      }
    };
    Node* findHint(Node* root, const Key& key)
    {
      Node* cur = (root->height_ < 0) ? root->left_ : root;
      while (cur)
      {
        if (cur->val_.first == key)
        {
          return cur;
        }
        if (comparator_(key, cur->val_.first))
        {
          if (!cur->left_)
          {
            return cur;
          }
          cur = cur->left_;
        }
        else
        {
          if (!cur->right_)
          {
            return cur;
          }
          cur = cur->right_;
        }
      }
      return nullptr;
    }
    void rebalanceTree(Node* start)
    {
      using std::abs;
      using std::max;
      while (start && start->height_ != -1)
      {
        int depth_diff = Node::depth(start->left_) - Node::depth(start->right_);
        if (start->height_ == max(Node::depth(start->left_), Node::depth(start->right_)) && abs(depth_diff) < 2)
        {
          return;
        }
        Node* parent = start->parent_;
        if (abs(depth_diff) > 1)
        {
          start->rotate();
        }
        else
        {
          start->height_ = max(Node::depth(start->left_), Node::depth(start->right_));
        }
        start = parent;
      }
      return;
    }
    void freeNodes(Node* root) noexcept
    {
      if (!root)
      {
        return;
      }
      Node* cur = root;
      while (root->right_ || root->left_)
      {
        if (cur->right_)
        {
          cur = cur->right_;
          continue;
        }
        if (cur->left_)
        {
          cur = cur->left_;
          continue;
        }
        cur = cur->parent_;
        if (cur->left_ && !cur->left_->left_ && !cur->left_->right_)
        {
          delete cur->left_;
          cur->left_ = nullptr;
        }
        if (cur->right_ && !cur->right_->left_ && !cur->right_->right_)
        {
          delete cur->right_;
          cur->right_ = nullptr;
        }
      }
      delete root;
    }
    Node* addNode(Node* root, Node* hint, const Key& key, const T& new_val)
    {
      if (!hint)
      {
        hint = findHint(root, key);
      }
      if (!hint)
      {
        root->left_ = new Node(0, std::forward< val_t >(std::make_pair(key, new_val)));
        root->left_->parent_ = root;
        return root->left_;
      }
      if (hint->val_.first == key)
      {
        hint->val_.second = new_val;
        return hint;
      }
      Node* new_node = new Node(0, std::forward< val_t >(std::make_pair(key, new_val)));
      (comparator_(hint->val_.first, key) ? hint->right_ : hint->left_) = new_node;
      new_node->parent_ = hint;
      rebalanceTree(hint);
      return new_node;
    }
    void eraseNode(Node* for_del)
    {
      Node* parent = for_del->parent_;
      if (!for_del->left_ || !for_del->right_)
      {
        Node* child = (for_del->left_ ? for_del->left_ : for_del->right_);
        (for_del == parent->left_ ? parent->left_ : parent->right_) = child;
        if (child)
        {
          child->parent_ = parent;
        }
        rebalanceTree(parent);
      }
      else
      {
        Node* prev = for_del->left_;
        for (; prev->right_; prev = prev->right_);
        Node* prev_parent = prev->parent_;
        prev->right_ = for_del->right_;
        if (for_del->right_)
        {
          for_del->right_->parent_ = prev;
        }
        ((for_del == parent->left_) ? parent->left_ : parent->right_) = prev;
        prev->parent_ = parent;
        if (prev_parent != for_del)
        {
          prev_parent->right_ = prev->left_;
          prev->left_->parent_ = prev_parent;
          prev->left_ = for_del->left_;
        }
        rebalanceTree((prev_parent != for_del) ? prev_parent : prev);
      }
      delete for_del;
    }
    template< typename InputIt >
    Node* createMap(Node* fakeroot, InputIt begin, InputIt end, size_t& nmb_of_added)
    {
      nmb_of_added = 0;
      if (begin == end)
      {
        return nullptr;
      }
      bool fake_given = fakeroot;
      if (!fakeroot)
      {
        fakeroot_ = new Node(-1);
      }
      fakeroot->left_ = new Node(0, std::forward(*begin));
      fakeroot->left_->parent_ = fakeroot;
      ++begin;
      ++nmb_of_added;
      try
      {
        while (begin != end)
        {
          addNode(fakeroot, nullptr, (*begin).first, (*begin).second);
          ++begin;
          ++nmb_of_added;
        }
      }
      catch (...)
      {
        freeNodes(fake_given ? fakeroot->left_ : fakeroot);
        throw;
      }
      return fakeroot;
    }

    template< bool IsConst >
    class BaseIterator
    {
      template< bool U > friend class BaseIterator;
      template< typename T1, typename T2, class T3 > friend class Map;
      using val_t = std::conditional_t< IsConst, const std::pair< const Key, T >, std::pair< const Key, T > >;
      using prt_t = std::conditional_t< IsConst, const val_t*, val_t* >;
      using ref_t = std::conditional_t< IsConst, const val_t&, val_t& >;
      using node_t = Node*;

      node_t node_;
    public:
      using iterator_category = std::bidirectional_iterator_tag;
      using value_type = val_t;
      using difference_type = std::ptrdiff_t;
      using pointer = prt_t;
      using reference = ref_t;

      BaseIterator() noexcept:
        node_(nullptr)
      {}
      BaseIterator(const BaseIterator& other) noexcept:
        node_(other.node_)
      {}
      explicit BaseIterator(node_t node) noexcept:
        node_(node)
      {}
      template< bool cond = IsConst, std::enable_if_t< cond, bool > = true >
      BaseIterator(const BaseIterator< !cond >& other) noexcept:
        node_(other.node_)
      {}
      BaseIterator& operator=(const BaseIterator& other) noexcept
      {
        node_ = other.node_;
      }
      BaseIterator& operator++()
      {
        if (node_->right_)
        {
          node_ = node_->right_;
          for (; node_->left_; node_ = node_->left_);
        }
        else
        {
          for (; node_ == node_->parent_->right_; node_ = node_->parent_);
          node_ = node_->parent_;
        }
        return *this;
      }
      BaseIterator operator++(int)
      {
        BaseIterator copy = *this;
        ++(*this);
        return copy;
      }
      BaseIterator& operator--()
      {
        if (node_->left_)
        {
          node_ = node_->left_;
          for (; node_->right_; node_ = node_->right_);
        }
        else
        {
          for (; node_ == node_->parent_->left_; node_ = node_->parent_);
          node_ = node_->parent_;
        }
        return *this;
      }
      BaseIterator operator--(int)
      {
        BaseIterator copy = *this;
        --(*this);
        return copy;
      }
      ref_t operator*() const
      {
        return node_->val_;
      }
      prt_t operator->() const
      {
        return std::addressof(node_->val_);
      }
      bool operator!=(const BaseIterator& other) const noexcept
      {
        return node_ != other.node_;
      }
      bool operator==(const BaseIterator& other) const noexcept
      {
        return node_ == other.node_;
      }
    };

    template< bool IsConst >
    class BaseLNRIterator
    {
      template< bool U > friend class BaseLNRIterator;
      template< typename T1, typename T2, class T3 > friend class Map;
      using val_t = std::conditional_t< IsConst, const std::pair< const Key, T >, std::pair< const Key, T > >;
      using prt_t = std::conditional_t< IsConst, const val_t*, val_t* >;
      using ref_t = std::conditional_t< IsConst, const val_t&, val_t& >;
      using path_t = Stack< Node* >;

      path_t path_;
    public:
      using iterator_category = std::bidirectional_iterator_tag;
      using value_type = val_t;
      using difference_type = std::ptrdiff_t;
      using pointer = prt_t;
      using reference = ref_t;

      explicit BaseLNRIterator(Node* fakeroot):
        path_()
      {
        path_.push(fakeroot);
      }
      BaseLNRIterator(const BaseLNRIterator& other):
        path_(other.path_)
      {}
      BaseLNRIterator(BaseLNRIterator&& other) noexcept:
        path_(std::move(other.path_))
      {}
      template< bool cond = IsConst, std::enable_if_t<cond, bool > = true >
      BaseLNRIterator(const BaseLNRIterator< !cond >& other) :
        path_(other.path_)
      {}
      BaseLNRIterator& operator=(const BaseLNRIterator& other)
      {
        path_ = other.path_;
      }
      BaseLNRIterator& operator++()
      {
        if (path_.top()->right_)
        {
          path_.push(path_.top()->right_);
          for (; path_.top()->left_; path_.push(path_.top()->left_));
        }
        else
        {
          Node* cur = path_.top();
          path_.pop();
          while (path_.top()->right_ == cur)
          {
            cur = path_.top();
            path_.pop();
          }
        }
        return *this;
      }
      BaseLNRIterator operator++(int)
      {
        BaseLNRIterator copy = *this;
        ++(*this);
        return copy;
      }
      BaseLNRIterator& operator--()
      {
        if (path_.top()->left_)
        {
          path_.push(path_.top()->left_);
          for (; path_.top()->right_; path_.push(path_.top()->right_));
        }
        else
        {
          Node* cur = path_.top();
          path_.pop();
          while (path_.top()->left_ == cur && path_.size() != 1)
          {
            cur = path_.top();
            path_.pop();
          }
        }
        return *this;
      }
      BaseLNRIterator operator--(int)
      {
        BaseLNRIterator copy = *this;
        --(*this);
        return copy;
      }
      ref_t operator*() const
      {
        return path_.top()->val_;
      }
      prt_t operator->() const
      {
        return std::addressof(path_.top()->val_);
      }
      bool operator!=(const BaseLNRIterator& other) const
      {
        return path_.top() != other.path_.top();
      }
      bool operator==(const BaseLNRIterator& other) const
      {
        return path_.top() == other.path_.top();
      }
    };
  public:
    using iterator = BaseIterator< false >;
    using const_iterator = BaseIterator< true >;
    using reverse_iterator = std::reverse_iterator< iterator >;
    using const_reverse_iterator = std::reverse_iterator< const_iterator >;

    using lnr_iterator = BaseLNRIterator< false >;
    using const_lnr_iterator = BaseLNRIterator< true >;
    using rnl_iterator = std::reverse_iterator< lnr_iterator >;
    using const_rnl_iterator = std::reverse_iterator< const_lnr_iterator >;
    Map():
      comparator_(),
      fakeroot_(new Node(-1)),
      size_(0)
    {}
    Map(const Map& other):
      comparator_(other.comparator_),
      fakeroot_(new Node(-1)),
      size_(other.size_)
    {
      size_t added = 0;
      const Node* cur_other = other.fakeroot_;
      Node* cur = fakeroot_;
      try
      {
        while (size_ != added)
        {
          if (cur_other->right_ && !cur->right_)
          {
            cur->right_ = new Node(*(cur_other->right_));
            cur->right_->parent_ = cur;
            cur = cur->right_;
            cur_other = cur_other->right_;
            ++added;
            continue;
          }
          if (cur_other->left_ && !cur->left_)
          {
            cur->left_ = new Node(*(cur_other->left_));
            cur->left_->parent_ = cur;
            cur = cur->left_;
            cur_other = cur_other->left_;
            ++added;
            continue;
          }
          cur = cur->parent_;
          cur_other = cur_other->parent_;
        }
      }
      catch (...)
      {
        freeNodes(fakeroot_);
        throw;
      }
    }
    Map(Map&& other) noexcept:
      comparator_(std::move(other.comparator_)),
      fakeroot_(other.fakeroot_),
      size_(other.size_)
    {
      other.fakeroot_ = nullptr;
      other.size_ = 0;
    }
    Map(std::initializer_list< std::pair< const Key, T > > init_list):
      comparator_(),
      fakeroot_(new Node(-1)),
      size_(0)
    {
      try
      {
        createMap(fakeroot_, init_list.begin(), init_list.end(), size_);
      }
      catch (...)
      {
        freeNodes(fakeroot_);
      }
    }
    template< typename InputIt >
    Map(InputIt begin, InputIt end):
      comparator_(),
      fakeroot_(new Node(-1)),
      size_(0)
    {
      try
      {
        createMap(fakeroot_, begin, end, size_);
      }
      catch (...)
      {
        freeNodes(fakeroot_);
      }
    }
    ~Map()
    {
      freeNodes(fakeroot_);
    }
    Map& operator=(const Map& other)
    {
      Map new_map(other);
      clear();
      this->swap(new_map);
      return *this;
    }
    Map& operator=(Map&& other)
    {
      if (this == std::addressof(other))
      {
        return *this;
      }
      this->swap(other);
      other.clear();
      return *this;
    }

    iterator begin() noexcept
    {
      Node* cur = fakeroot_;
      for (; cur->left_; cur = cur->left_);
      return iterator(cur);
    }
    const_iterator begin() const noexcept
    {
      return cbegin();
    }
    const_iterator cbegin() const noexcept
    {
      Node* cur = fakeroot_;
      for (; cur->left_; cur = cur->left_);
      return const_iterator(cur);
    }
    reverse_iterator rbegin() noexcept
    {
      return std::make_reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const noexcept
    {
      return std::make_reverse_iterator(cend());
    }
    const_reverse_iterator crbegin() const noexcept
    {
      return std::make_reverse_iterator(cend());
    }
    static iterator get_lite_iterator(lnr_iterator it)
    {
      return iterator(it.path_.top());
    }
    static const_iterator get_lite_iterator(const_lnr_iterator it)
    {
      return const_iterator(it.path_.top());
    }

    iterator end() noexcept
    {
      return iterator(fakeroot_);
    }
    const_iterator end() const noexcept
    {
      return const_iterator(fakeroot_);
    }
    const_iterator cend() const noexcept
    {
      return const_iterator(fakeroot_);
    }
    reverse_iterator rend() noexcept
    {
      return std::make_reverse_iterator(begin());
    }
    const_reverse_iterator rend() const noexcept
    {
      return std::make_reverse_iterator(cbegin());
    }
    const_reverse_iterator crend() const noexcept
    {
      return std::make_reverse_iterator(cbegin());
    }
    static reverse_iterator get_lite_iterator(rnl_iterator it)
    {
      iterator forward_it(it.base().path_.top());
      return std::make_reverse_iterator(forward_it);
    }
    static const_reverse_iterator get_lite_iterator(const_rnl_iterator it)
    {
      const_iterator forward_it(it.base().path_.top());
      return std::make_reverse_iterator(forward_it);
    }

    lnr_iterator lnr_begin()
    {
      lnr_iterator it(fakeroot_);
      for (; it.path_.top()->left_; it.path_.push(it.path_.top()->left_));
      return it;
    }
    const_lnr_iterator lnr_begin() const
    {
      return lnr_cbegin();
    }
    const_lnr_iterator lnr_cbegin() const
    {
      const_lnr_iterator it(fakeroot_);
      for (; it.path_.top()->left_; it.path_.push(it.path_.top()->left_));
      return it;
    }
    lnr_iterator lnr_end()
    {
      return lnr_iterator(fakeroot_);
    }
    const_lnr_iterator lnr_end() const
    {
      return lnr_cend();
    }
    const_lnr_iterator lnr_cend() const
    {
      return const_lnr_iterator(fakeroot_);
    }
    template< class F >
    F traverse_lnr(F f)
    {
      for (lnr_iterator i = lnr_begin(); i != lnr_end(); ++i)
      {
        f(*i);
      }
      return f;
    }
    template< class F >
    F const_traverse_lnr(F f) const
    {
      for (const_lnr_iterator i = lnr_cbegin(); i != lnr_cend(); ++i)
      {
        f(*i);
      }
      return f;
    }

    rnl_iterator rnl_begin()
    {
      return std::make_reverse_iterator(lnr_end());
    }
    const_rnl_iterator rnl_begin() const
    {
      return rnl_cbegin();
    }
    const_rnl_iterator rnl_cbegin() const
    {
      return std::make_reverse_iterator(lnr_cend());
    }
    rnl_iterator rnl_end()
    {
      return std::make_reverse_iterator(lnr_begin());
    }
    const_rnl_iterator rnl_end() const
    {
      return rnl_cend();
    }
    const_rnl_iterator rnl_cend() const
    {
      return std::make_reverse_iterator(lnr_cbegin());
    }
    template< class F >
    F traverse_rnl(F f)
    {
      for (rnl_iterator i = rnl_begin(); i != rnl_end(); ++i)
      {
        f(*i);
      }
      return f;
    }
    template< class F >
    F const_traverse_rnl(F f) const
    {
      for (const_rnl_iterator i = rnl_cbegin(); i != rnl_cend(); ++i)
      {
        f(*i);
      }
      return f;
    }
    template< class F >
    F traverse_breadth(F f)
    {
      Queue< Node* > bf_queue;
      if (size_)
      {
        bf_queue.push(fakeroot_->left_);
      }
      while (!bf_queue.empty())
      {
        if (bf_queue.front()->left_)
        {
          bf_queue.push(bf_queue.front()->left_);
        }
        if (bf_queue.front()->right_)
        {
          bf_queue.push(bf_queue.front()->right_);
        }
        f(bf_queue.front()->val_);
        bf_queue.pop();
      }
      return f;
    }
    template< class F >
    F const_traverse_breadth(F f) const
    {
      Queue< const Node* > bf_queue;
      if (size_)
      {
        bf_queue.push(fakeroot_->left_);
      }
      while (!bf_queue.empty())
      {
        if (bf_queue.front()->left_)
        {
          bf_queue.push(bf_queue.front()->left_);
        }
        if (bf_queue.front()->right_)
        {
          bf_queue.push(bf_queue.front()->right_);
        }
        f(bf_queue.front()->val_);
        bf_queue.pop();
      }
      return f;
    }

    bool empty() const noexcept
    {
      return !size_;
    }
    size_t size() const noexcept
    {
      return size_;
    }
    void clear() noexcept
    {
      freeNodes(fakeroot_->left_);
      fakeroot_->left_ = nullptr;
      size_ = 0;
    }
    void swap(Map& other)
    {
      std::swap(comparator_, other.comparator_);
      std::swap(fakeroot_, other.fakeroot_);
      std::swap(size_, other.size_);
    }

    template< typename K>
    iterator find(const K& x)
    {
      Node* cur = fakeroot_->left_;
      while (cur)
      {
        if (cur->val_.first == x)
        {
          return iterator(cur);
        }
        cur = (comparator_(cur->val_.first, x)) ? cur->right_ : cur->left_;
      }
      return end();
    }
    template< class K >
    const_iterator find(const K& x) const
    {
      Node* cur = fakeroot_.left_;
      while (cur)
      {
        if (cur->val_.first == x)
        {
          return const_iterator(cur);
        }
        cur = (comparator_(cur->val_.first, x)) ? cur->left_ : cur->right_;
      }
      return cend();
    }
    template< class K >
    size_t count(const K& x) const
    {
      return (find(x) != end());
    }
    iterator lower_bound(const Key& key)
    {
      Node* cur = findHint(fakeroot_->left_, key);
      if (comparator_(cur->val_.first, key))
      {
        return ++iterator(cur);
      }
      return iterator(cur);
    }
    const_iterator lower_bound(const Key& key) const
    {
      Node* cur = findHint(fakeroot_->left_, key);
      if (comparator_(cur->val_.first, key))
      {
        return ++const_iterator(cur);
      }
      return const_iterator(cur);
    }
    iterator upper_bound(const Key& key)
    {
      iterator lb = lower_bound(key);
      if (lb != end() && !comparator_((*lb).first, key))
      {
        return ++lb;
      }
      return lb;
    }
    const_iterator upper_bound(const Key& key) const
    {
      const_iterator lb = lower_bound(key);
      if (lb != cend() && !comparator_((*lb).first, key))
      {
        return ++lb;
      }
      return lb;
    }
    std::pair< iterator, iterator > equal_range(const Key& key)
    {
      return std::make_pair(lower_bound(key), upper_bound(key));
    }
    std::pair< const_iterator, const_iterator > equal_range(const Key& key) const
    {
      return std::make_pair(lower_bound(key), upper_bound(key));
    }
    const_iterator find(const Key& key) const
    {
      Node* cur = fakeroot_->left_;
      while (cur)
      {
        if (cur->val_.first == key)
        {
          return const_iterator(cur);
        }
        cur = (comparator_(cur->val_.first, key)) ? cur->right_ : cur->left_;
      }
      return cend();
    }

    T& at(const Key& key)
    {
      Node* cur = findHint(fakeroot_->left_, key);
      if (cur && cur->val_.first == key)
      {
        return cur->val_.second;
      }
      throw std::out_of_range("No such element");
    }
    const T& at(const Key& key) const
    {
      Node* cur = findHint(fakeroot_->left_, key);
      if (cur && cur->val_.first == key)
      {
        return cur->val_.second;
      }
      throw std::out_of_range("No such element");
    }
    T& operator[](const Key& key)
    {
      Node* cur = findHint(fakeroot_, key);
      if (cur && cur->val_.first == key)
      {
        return cur->val_.second;
      }
      Node* added = addNode(fakeroot_, cur, key, T{});
      ++size_;
      return added->val_.second;
    }

    template< class... Args >
    std::pair< iterator, bool > emplace(Args&&... args)
    {
      val_t new_val(std::forward< Args >(args)...);
      Node* hint = findHint(fakeroot_, new_val.first);
      if (hint && hint->val_.first == new_val.first)
      {
        return std::make_pair(iterator(hint), false);
      }
      Node* added = addNode(fakeroot_, hint, new_val.first, new_val.second);
      ++size_;
      return std::make_pair(iterator(added), true);
    }
    template< class... Args >
    iterator emplace_hint(const_iterator  pos, Args&&... args)
    {
      val_t new_val(std::forward< Args >(args)...);
      if (empty() || pos == end())
      {
        return iterator(addNode(fakeroot_, nullptr, new_val.first, new_val.second));
      }
      if (comparator_(new_val, (*pos).first)&&(pos == begin()|| comparator_((*std::prev(pos)).first, new_val)))
      {
        return iterator(addNode(fakeroot_, pos.node_, new_val.first, new_val.second));
      }
      Node* hint = findHint(fakeroot_, new_val.first);
      if (hint->val_.first == new_val.first)
      {
        return iterator(hint);
      }
      else
      {
        return iterator(addNode(fakeroot_, hint, new_val.first, new_val.second));
      }
    }
    std::pair< iterator, bool > insert(const val_t& val)
    {
      Node* hint = findHint(fakeroot_, val.first);
      if (hint && hint->val_.first == val.first)
      {
        return std::make_pair(iterator(hint), false);
      }
      Node* added = addNode(fakeroot_, hint, val.first, val.second);
      ++size_;
      return std::make_pair(iterator(added), true);
    }
    iterator insert(const_iterator pos, const val_t& val)
    {
      return emplace_hint(pos, val);
    }
    template< class InputIt >
    void insert(InputIt first, InputIt last)
    {
      for (; first != last; ++first)
      {
        addNode(fakeroot_, nullptr, first->first, first->second);
      }
    }
    void insert(std::initializer_list<val_t> init_list)
    {
      insert(init_list.begin(), init_list.end());
    }

    iterator erase(iterator pos)
    {
      Node* for_del = pos.node_;
      ++pos;
      eraseNode(for_del);
      --size_;
      return pos;
    }
    const_iterator erase(const_iterator pos)
    {
      Node* for_del = pos.node_;
      ++pos;
      eraseNode(for_del);
      --size_;
      return pos;
    }
    size_t erase(const Key& key)
    {
      iterator pos = find(key);
      if (pos == end())
      {
        return 0;
      }
      erase(pos);
      return 1;
    }
    iterator erase(iterator first, iterator last)
    {
      for (; first != last; first = erase(first));
      return first;
    }
    const_iterator erase(const_iterator first, const_iterator last)
    {
      for (; first != last; first = erase(first));
      return first;
    }
  };
}
#endif
