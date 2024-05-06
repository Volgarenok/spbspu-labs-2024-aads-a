#ifndef MAP_HPP
#define MAP_HPP
#include <algorithm>
#include <initializer_list>
#include <memory>
#include <stdexcept>


namespace zaitsev
{
  template< typename Key, typename T, typename Compare = std::less< Key > >
  class Map
  {
    using val_t = std::pair<const Key, T>;
    struct Node;
    Node* fakeroot_;
    size_t size_;
    Compare cmp_;

    struct Node
    {
      std::pair< const Key, T > val_;
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
      explicit Node(bool):
        val_(),
        height_(-1),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr)
      {}
      explicit Node(const val_t& val):
        val_(val),
        height_(0),
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
      bool update_height()
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
          root = (depth(right_->left_) <= depth(right_->right_)) ? root->rotate_left() : root->rotate_left_right();
        }
        else
        {
          root = (depth(left_->right_) <= depth(left_->left_)) ? root->rotate_right() : root->rotate_right_left();
        }
        root->parent_ = parent;
        (left ? parent->left_ : parent->right_) = root;
        return;
      }
    private:
      Node* rotate_left()
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
        root->update_height();
        new_root->update_height();
        return new_root;
      }
      Node* rotate_right()
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
        root->update_height();
        new_root->update_height();
        return new_root;
      }
      Node* rotate_left_right()
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
        root->update_height();
        new_root->right_->update_height();
        new_root->update_height();
        return new_root;
      }
      Node* rotate_right_left()
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
        root->update_height();
        new_root->left_->update_height();
        new_root->update_height();
        return new_root;
      }
    };
    Node* find_hint(Node* root, const Key& key)
    {
      Node* cur = (root->height_ < 0) ? root->left_ : root;
      while (cur)
      {
        if (cur->val_.first == key)
        {
          return cur;
        }
        if (cmp_(key, cur->val_.first))
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
    void rebalance_tree(Node* start)
    {
      while (start && start->height_ != -1)
      {
        int depth_diff = Node::depth(start->left_) - Node::depth(start->right_);
        if (start->height_ == std::max(Node::depth(start->left_), Node::depth(start->right_)) && std::abs(depth_diff) < 2)
        {
          return;
        }
        Node* parent = start->parent_;
        if (std::abs(depth_diff) > 1)
        {
          start->rotate();
        }
        else
        {
          start->height_ = std::max(Node::depth(start->left_), Node::depth(start->right_));
        }
        start = parent;
      }
      return;
    }
    void freeNodes(Node* root)
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
      hint = find_hint((hint == nullptr || !cmp_(hint->val_.first, key)) ? root : hint, key);
      if (!hint)
      {
        root->left_ = new Node(std::make_pair(key, new_val));
        root->left_->parent_ = root;
        return root->left_;
      }
      if (hint->val_.first == key)
      {
        hint->val_.second = new_val;
        return hint;
      }
      Node* new_node = new Node(std::make_pair(key, new_val));
      (cmp_(hint->val_.first, key) ? hint->right_ : hint->left_) = new_node;
      new_node->parent_ = hint;
      rebalance_tree(hint);
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
        rebalance_tree(parent);
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
        rebalance_tree((prev_parent != for_del) ? prev_parent : prev);
      }
      delete for_del;
    }
    template< typename InputIt >
    Node* create_map(Node* fakeroot, InputIt begin, InputIt end, size_t& nmb_of_added)
    {
      nmb_of_added = 0;
      if (begin == end)
      {
        return nullptr;
      }
      bool fake_given = fakeroot;
      if (!fakeroot)
      {
        fakeroot_ = new Node(false);
      }
      fakeroot->left_ = new Node(*begin);
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
      using node_t = std::conditional_t < IsConst, const Node*, Node*>;

      node_t node_;
    public:
      using iterator_category = std::bidirectional_iterator_tag;
      using value_type = val_t;
      using difference_type = std::ptrdiff_t;
      using pointer = prt_t;
      using reference = ref_t;

      BaseIterator():
        node_(nullptr)
      {}
      explicit BaseIterator(node_t node):
        node_(node)
      {}
      template<bool cond = IsConst, std::enable_if_t<cond, bool> = true >
      BaseIterator(const BaseIterator<!cond>& other) :
        node_(other.node_)
      {}
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
      bool operator!=(const BaseIterator& other) const
      {
        return node_ != other.node_;
      }
      bool operator==(const BaseIterator& other) const
      {
        return node_ == other.node_;
      }
    };
  public:
    using iterator = BaseIterator< false >;
    using const_iterator = BaseIterator< true >;
    using reverse_iterator = std::reverse_iterator< iterator >;
    using const_reverse_iterator = std::reverse_iterator< const_iterator >;
    Map():
      fakeroot_(new Node(false)),
      size_(0),
      cmp_()
    {}
    Map(const Map& other):
      fakeroot_(new Node(*(other.fakeroot_))),
      size_(other.size_),
      cmp_(other.cmp_)
    {
      size_t added = 0;
      const Node* cur_other = other.fakeroot_;
      Node* cur = fakeroot_;
      try
      {
        while (size_ != added)
        {
          if (cur_other->right_)
          {
            cur->right_ = new Node(*(cur_other->right_));
            cur->right_->parent_ = cur;
            cur = cur->right_;
            cur_other = cur_other->right_;
            ++added;
            continue;
          }
          if (cur_other->left_)
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
        freeNodes(fakeroot_->left_);
        throw;
      }
    }
    Map(Map&& other):
      fakeroot_(other.fakeroot_),
      size_(other.size_),
      cmp_(std::move(other.cmp_))
    {
      other.fakeroot_ = nullptr;
      other.size_ = 0;
    }
    Map(std::initializer_list< std::pair< const Key, T > > init_list):
      fakeroot_(new Node(false)),
      size_(0),
      cmp_()
    {
      create_map(fakeroot_, init_list.begin(), init_list.end(), size_);
    }
    template< typename InputIt >
    Map(InputIt begin, InputIt end):
      fakeroot_(new Node(false)),
      size_(0),
      cmp_()
    {
      create_map(fakeroot_, begin, end, size_);
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
      clear();
      this->swap(other);
      return *this;
    }

    iterator begin()
    {
      Node* cur = fakeroot_;
      for (; cur->left_; cur = cur->left_);
      return iterator(cur);
    }
    const_iterator begin() const
    {
      return cbegin();
    }
    const_iterator cbegin() const
    {
      const Node* cur = fakeroot_;
      for (; cur->left_; cur = cur->left_);
      return const_iterator(cur);
    }
    reverse_iterator rbegin()
    {
      return std::make_reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const
    {
      return std::make_reverse_iterator(cend());
    }
    const_reverse_iterator crbegin() const
    {
      return std::make_reverse_iterator(cend());
    }

    iterator end()
    {
      return iterator(fakeroot_);
    }
    const_iterator end() const
    {
      return const_iterator(fakeroot_);
    }
    const_iterator cend() const
    {
      return const_iterator(fakeroot_);
    }
    reverse_iterator rend()
    {
      return std::make_reverse_iterator(begin());
    }
    const_reverse_iterator rend() const
    {
      return std::make_reverse_iterator(cbegin());
    }
    const_reverse_iterator crend() const
    {
      return std::make_reverse_iterator(cbegin());
    }

    bool empty() const
    {
      return !size_;
    }
    size_t size() const
    {
      return size_;
    }
    void clear()
    {
      freeNodes(fakeroot_->left_);
      fakeroot_->left_ = nullptr;
      size_ = 0;
    }
    void swap(Map& other)
    {
      std::swap(fakeroot_, other.fakeroot_);
      std::swap(size_, other.size_);
      std::swap(cmp_, other.cmp_);
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
        cur = (cmp_(cur->val_.first, x)) ? cur->right_ : cur->left_;
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
        cur = (cmp_(cur->val_.first, x)) ? cur->left_ : cur->right_;
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
      Node* cur = find_hint(fakeroot_->left_, key);
      if (cmp_(cur->val_.first, key))
      {
        return ++iterator(cur);
      }
      return iterator(cur);
    }
    const_iterator lower_bound(const Key& key) const
    {
      Node* cur = find_hint(fakeroot_->left_, key);
      if (cmp_(cur->val_.first, key))
      {
        return ++const_iterator(cur);
      }
      return const_iterator(cur);
    }
    iterator upper_bound(const Key& key)
    {
      iterator lb = lower_bound(key);
      if (lb != end() && (*lb).first == key)
      {
        return ++lb;
      }
      return lb;
    }
    const_iterator upper_bound(const Key& key) const
    {
      const_iterator lb = lower_bound(key);
      if (lb != cend() && (*lb).first == key)
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
        cur = (cmp_(cur->val_.first, key)) ? cur->right_ : cur->left_;
      }
      return cend();
    }

    T& at(const Key& key)
    {
      Node* cur = find_hint(fakeroot_->left_, key);
      if (cur && cur->val_.first == key)
      {
        return cur->val_.second;
      }
      throw std::out_of_range("No such element");
    }
    const T& at(const Key& key) const
    {
      Node* cur = find_hint(fakeroot_->left_, key);
      if (cur && cur->val_.first == key)
      {
        return cur->val_.second;
      }
      throw std::out_of_range("No such element");
    }
    T& operator[](const Key& key)
    {
      Node* cur = find_hint(fakeroot_, key);
      if (cur&&cur->val_.first == key)
      {
        return cur->val_.second;
      }
      Node* added = addNode(fakeroot_, cur, key, T());
      ++size_;
      return added->val_.second;
    }

    template< class... Args >
    std::pair< iterator, bool > emplace(Args&&... args)
    {
      val_t new_val(std::forward< Args >(args)...);
      Node* hint = find_hint(fakeroot_, new_val.first);
      if (hint && hint->val_.first == new_val.first)
      {
        return std::make_pair(iterator(hint), false);
      }
      Node* added = addNode(fakeroot_, hint, new_val.first, new_val.second);
      ++size_;
      return std::make_pair(iterator(added), true);
    }
    std::pair< iterator, bool > insert(const val_t& val)
    {
      Node* hint = find_hint(fakeroot_, val.first);
      if (hint && hint->val_.first == val.first)
      {
        return std::make_pair(iterator(hint), false);
      }
      Node* added = addNode(fakeroot_, hint, val.first, val.second);
      ++size_;
      return std::make_pair(iterator(added), true);
    }
    template< class InputIt >
    void insert(InputIt first, InputIt last)
    {
      for (; first != last; ++first)
      {
        addNode(nullptr, first->val_.first, first->val_.second);
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
      return pos;
    }
    const_iterator erase(const_iterator pos)
    {
      Node* for_del = pos.node_;
      ++pos;
      eraseNode(for_del);
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
    iterator  erase(iterator first, iterator last)
    {
      for (; first != last; first = erase(first));
      return first;
    }
    const_iterator  erase(const_iterator first, const_iterator last)
    {
      for (; first != last; first = erase(first));
      return first;
    }
  };
}
#endif
