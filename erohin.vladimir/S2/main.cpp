#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "token.hpp"
#include <queue>

int main()
{
  using namespace erohin;
  std::string string_token;
  std::istringstream input("23 - ( 98 * ( 9 - 2 ) )");
  std::queue< Token > input_queue;
  token_identifier_t temp_id = token_identifier_t::OPERAND_TYPE;
  token_t temp_token{ Operand() };
  while (input >> string_token)
  {
    std::cout << string_token << " ";
    try
    {
      temp_token.operand = Operand(stoll(string_token));
      temp_id = token_identifier_t::OPERAND_TYPE;
    }
    catch (const std::out_of_range &)
    {
      std::cout << "Numeric is out of range\n";
      return 1;
    }
    catch (const std::invalid_argument &)
    {
      std::cout << "Numeric is out of range\n";
      return 1;
    }
  }
  Operator oper('+');
  Operand res = oper.evaluate(Operand(2), Operand(3));
  std::cout << res();
}
