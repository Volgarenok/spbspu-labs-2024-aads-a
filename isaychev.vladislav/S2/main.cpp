#include <iostream>
#include <fstream>
#include "inputInfix.hpp"
#include "convertInfToPostf.hpp"
#include "calculateExpression.hpp"
#include "tokens.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  std::istream * input = nullptr;
  std::ifstream file;
  if (argc == 1)
  {
    input = std::addressof(std::cin);
  }
  else
  {
    file.open(argv[1]);
    input = std::addressof(file);
  }

  Stack< long long int > results;
  try
  {
//    while (!(*input).eof())
  //  {
//      Queue< std::string > infExp;
      //Queue< std::string > postfExp;
      Queue< Token > infExp;
      Queue< Token > postfExp;
      try
      {
        inputInfix(*input, infExp);
      }
      catch (const std::length_error &)
      {
//        continue;
      }
//      convertInfToPostf(infExp, postfExp);
  //    results.push(calculateExpression(postfExp));
   // } ( 1 + 2 ) * ( 6 / 2 )
     TokenType n[11] = {isaychev::TokenType::BRACKET, isaychev::TokenType::OPERAND,
      isaychev::TokenType::OPERATION, isaychev::TokenType::OPERAND,isaychev::TokenType::BRACKET,
      isaychev::TokenType::OPERATION,isaychev::TokenType::BRACKET, isaychev::TokenType::OPERAND,
      isaychev::TokenType::OPERATION, isaychev::TokenType::OPERAND,isaychev::TokenType::BRACKET  };
     int k = 0;
     for (int i = 0; !infExp.empty(); ++i)
     {
       if (infExp.front().type == n[i])
       {
         k++;
       }
       infExp.pop();
     }
     std::cout << k;
  }
  catch (const std::invalid_argument & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::out_of_range & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << e.what() << "\n";
    return 3;
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << "\n";
    return 4;
  }

/*  if (!results.empty())
  {
    std::cout << results.top();
    results.pop();
    while (!results.empty())
    {
      std::cout << " " << results.top();
      results.pop();
    }
  }*/
  std::cout << "\n";
}

