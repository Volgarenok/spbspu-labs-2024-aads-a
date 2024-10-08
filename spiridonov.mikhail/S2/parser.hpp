#ifndef PARSER_HPP
#define PARSER_HPP
#include "detectSym.hpp"
#include "stack.hpp"
#include <string>
#include <stdexcept>

namespace spiridonov
{
  class Parser
  {
  public:
    static int64_t parseExpression(const std::string& expression);

  private:
    static void applyOperation(Stack<int64_t>& operands, char op);
  };
}
#endif
