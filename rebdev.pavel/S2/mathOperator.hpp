#ifndef MATHOPERATOR_HPP
#define MATHOPERATOR_HPP

namespace rebdev
{
  class mathOperator
  {
    public:
      mathOperator(char type);

      long long operator()(long long firts, long long second);
      unsigned int priority() const noexcept;
      bool leftBracket() const noexcept;

    private:
      char operType_;
      unsigned int priority_;

      bool isSignSame(long long f, long long s) const noexcept;
  };
}

#endif
