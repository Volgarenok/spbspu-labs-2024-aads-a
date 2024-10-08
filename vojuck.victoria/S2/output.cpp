#include "output.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include <string>
#include <iostream>
#include <cstdexept>

bool vojuck::isOperator(const std::string& token)
{
  return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
}
int vojuck::precedence(const std::string& op)
{
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/" || op == "%")
        return 2;
    return 0;
}
int vojuck::evaluatePostfix(const vojuck::Queue<std::string>& postfixQueue)
{
    vojuck::Stack<int> evalStack;
    vojuck::Queue<std::string> q = postfixQueue;

    while (!q.isEmpty())
    {
        std::string token = q.drop();
        if (isOperator(token))
        {
            if (evalStack.size() < 2)
            {
                throw std::runtime_error("Недостаточно операндов для оператора " + token);
            }
            int right = evalStack.pop();
            int left = evalStack.pop();
            int result;
            if (token == "+")
            {
                result = left + right;
            }
            else if (token == "-")
            {
                result = left - right;
            }
            else if (token == "*")
            {
                result = left * right;
            }
            else if (token == "/")
            {
                if (right == 0) {
                    throw std::invalid_argument("zero devision");
                }
                result = left / right;
            }
            else if (token == "%")
            {
                if (right == 0)
                {
                    throw std::invalid_argument("Zero devision");
                }
                result = left % right;
            }
            else
            {
                throw std::invalid_argument("unknown argument: " + token);
            }
            evalStack.push(result);
        }
        else
        {
            try
            {
                int value = std::stoi(token);
                evalStack.push(value);
            }
            catch (const std::invalid_argument&)
            {
                throw std::invalid_argument("invalid token: " + token);
            }
            catch (const std::out_of_range&)
            {
                throw std::invalid_argument("token out of range: " + token);
            }
        }
    }

    if (evalStack.size() != 1)
    {
        throw std::invalid_argument("invalid argument");
    }

    return evalStack.pop();
}

vojuck::Queue<std::string> vojuck:: infixToPostfix(const std::string& expression)
{
    vojuck::Queue<std::string> outputQueue;
    vojuck::Stack<std::string> operatorStack;

    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (std::isdigit(token[0]) ||
            (token.size() > 1 && (token[0] == '-' || token[0] == '+') && std::isdigit(token[1])))
        {
            outputQueue.push(token);
        }
        else if (token == "(")
        {
            operatorStack.push(token);
        }
        else if (token == ")")
        {
            while (!operatorStack.isEmpty() && operatorStack.top() != "(")
            {
                outputQueue.push(operatorStack.pop());
            }
            if (operatorStack.isEmpty())
            {
                throw std::invalid_argument("invalid argument) ");
            }
            operatorStack.pop();
        }
        else if (isOperator(token))
        {
            while (!operatorStack.isEmpty() && isOperator(operatorStack.top()) &&
                   precedence(operatorStack.top()) >= precedence(token))
            {
                outputQueue.push(operatorStack.pop());
            }
            operatorStack.push(token);
        }
        else
        {
            throw std::invalid_argument("invalid token: " + token);
        }
    }

    while (!operatorStack.isEmpty())
    {
        if (operatorStack.top() == "(" || operatorStack.top() == ")")
        {
            throw std::invalid_argument("invalid parenthesis.");
        }
        outputQueue.push(operatorStack.pop());
    }

    return outputQueue;
}
