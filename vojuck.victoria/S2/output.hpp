#ifndef OUTPUT_HPP
#define OUTPUT_HPP

namespace vojuck
{
int precedence(const std::string& op);
bool isOperator(const std::string& token);
int evaluatePostfix(const vojuck::Queue<std::string>& postfixQueue);
vojuck::Queue<std::string> infixToPostfix(const std::string& expression);
}

#endif
