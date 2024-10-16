#ifndef INPUT_DATA_H
#define INPUT_DATA_H

#include "Queue.h"
#include "Stack.h"
#include "Tokenizer.h"
#include <string>
#include <limits>
#include <cmath>
#include <iostream>

namespace stepanov
{
  class manageExpression
  {
    public:
      void parseExpression(const std::string& input);
      int checkOperatorsPriority(Token token) const;
      void convertToPolish(const std::string& newString);
      void calculatePolish(Stack< long long >& stackResult);
      void printResult(Stack< long long >& stackResult);
    private:
      Queue< Token > newExpr_;
      Queue< Token > postfQueue_;
      Stack< Token > stack_;
  };
}

#endif
