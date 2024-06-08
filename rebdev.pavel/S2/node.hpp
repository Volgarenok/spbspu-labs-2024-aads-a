#ifndef NODE_HPP
#define NODE_HPP

namespace rebdev
{
  class node
  {
    public:
      node() = delete;
      node(const node & origNode) = default;
      node(node && origNode) = default;
      node(long long int number) noexcept;
      node(char operationName);
      ~node() noexcept = default;

      node & operator=(const node & origNode) = default;
      node & operator=(node && origNode) = default;
      bool operator>=(const node & origNode) const noexcept;
      bool operator!=(char sym) const noexcept;

      long long getResult() const;
      long long getResult(long long first, long long second) const;

      long long getPriority() const noexcept;
    private:
      union
      {
        char operationName_;
        long long number_;
      };
      int operationPriority_;

      bool isSignSame(long long f, long long s) const noexcept;
  };
}

#endif
