#ifndef CALC_HPP
#define CALC_HPP

#include <string>
#include "queue.hpp"

int precedence(char op);
int applyOperation(int a, int b, char op);
petuhov::Queue< std::string > infixToPostfix(const std::string &expression);
int evaluatePostfix(petuhov::Queue< std::string > &postfix);

#endif
