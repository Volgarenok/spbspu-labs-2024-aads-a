#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <exception>
#include "queue.hpp"
#include "stack.hpp"
#include "tokens.hpp"
#include "input_infix.hpp"
#include "convert_expression.hpp"

int main(int argc, char **argv)
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
	try
	{
		InfixType inf1;
		inf1.data.operand.value = 4;
		inf1.type = PartsOfExpression::OPERAND;
		InfixType inf2;
		inf2.data.operation.operation = '-';
		inf2.type = PartsOfExpression::OPERATION;
		InfixType inf3;
		inf3.data.operand.value = 5;
		inf3.type = PartsOfExpression::OPERAND;
		Postfix pos;
		Queue<InfixType> qI;
		qI.push(inf1);
		qI.push(inf2);
		qI.push(inf3);
		convertExpression(qI);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	// std::cout << pos.data.operand.value;
	// Queue< Queue < InfixType > > q;
	// inputInfix(q, std::cin);

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
