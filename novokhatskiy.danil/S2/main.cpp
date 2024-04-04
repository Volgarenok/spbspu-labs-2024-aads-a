#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <exception>
#include "forward_list.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "tokens.hpp"
#include "input_infix.hpp"

int main(int argc, char** argv)
{
  using namespace novokhatskiy;
  /*Queue< Queue< InfixType > > infixQueue;
	try
	{
		if (argc == 2)
		{
			std::ifstream in(argv[1]);
			inputInfix(infixQueue, in);
		}
		else if (argc == 1)
		{
			inputInfix(infixQueue, std::cin);
		}
		else
		{
			std::cerr << "Wrong input arguments\n";
			return 1;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}*/
	InfixType inf;
	inf.data.operation.operation = '-';
	inf.type = PartsOfExpression::OPERATION;
	Postfix pos;
	pos.convertToPostfix(inf);
	//std::cout << pos.data.operand.value;
	Queue< Queue < InfixType > > q;
	inputInfix(q, std::cin);

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
