#include "inputData.hpp"

#include <cctype>
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <string>

#include "expressionObject.hpp"
#include "queue.hpp"

bool isOperation(const std::string line)
{
  return (line == "+" || line == "-" || line == "/" || line == "*" || line == "%");
}

bool isBracket(const std::string line)
{
  return (line == "(" || line == ")");
}

void parseLine(std::string &line, arakelyan::Queue< arakelyan::ExpressionObj > &someQ)
{
  using namespace arakelyan;
  size_t pos = 0;
  std::string expr;
  while (pos < line.length())
  {
    while (pos < line.length() && line[pos] == ' ')
    {
      pos++;
    }

    size_t start = pos;
    while (pos < line.length() && line[pos] != ' ')
    {
      pos++;
    }

    if (start < pos)
    {
      expr = line.substr(start, pos - start);

      Token token;
      token_t tokenType = token_t::undef;
      try
      {
        long long expLl = std::stoll(expr);
        token = Token(expLl);
        tokenType = token_t::operand;
      }
      catch (const std::invalid_argument &e)
      {
        char expCh = expr[0];
        token = Token(expCh);
        if (isOperation(expr))
        {
          tokenType = token_t::operation;
        }
        else if (isBracket(expr))
        {
          tokenType = token_t::bracket;
        }
      }
      catch (const std::out_of_range &e)
      {
        throw std::out_of_range("Out of range!");
      }

      arakelyan::ExpressionObj expObj(tokenType, token);
      someQ.push(expObj);
    }
  }
}

std::istream &arakelyan::readDataInInfixFormat(std::istream &input, Queue< Queue< ExpressionObj > > &qOfInfixQs)
{
  std::string line;

  while (!input.eof())
  {
    std::getline(input, line, '\n');
    if (!line.empty())
    {
      Queue< ExpressionObj > infixQ;
      parseLine(line, infixQ);
      if (!infixQ.empty())
      {
        qOfInfixQs.push(infixQ);
      }
    }
  }
  return input;
}
