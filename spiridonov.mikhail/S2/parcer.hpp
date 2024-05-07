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
    static int parseExpression(const std::string& expression);

  private:
    static void applyOperation(Stack<int>& operands, char op);
  };
}
#endif
