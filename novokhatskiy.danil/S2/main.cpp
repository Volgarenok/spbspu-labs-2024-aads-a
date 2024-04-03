#include <iostream>
#include <list>
#include <string>
#include "forward_list.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "tokens.hpp"
#include "input_infix.hpp"

int main(int argc, char** argv)
{
  using namespace novokhatskiy;
  Queue< Queue< InfixType > > infixList;
	inputInfix(infixList, std::cin);
	/*try
	{
		std::string str = "4 + 3";
		checkType(str);
		InfixType inf(PartsOfExpression::operation, '+');
		Bracket b('(');		b.getBracket();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}*/
}
