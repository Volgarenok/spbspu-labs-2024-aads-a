#include "input_infix.hpp"
#include <string>


//novokhatskiy::InfixType novokhatskiy::checkType(std::string& str)
//{
//	if (std::isdigit(str[0]))
//	{
//		return InfixType(PartsOfExpression::operand, str[0]);
//	}
//	else if (str[0] == '(')
//	{
//		return InfixType(PartsOfExpression::openBracket, str[0] == '(');
//	}
//	else if (str[0] == ')')
//	{
//		return InfixType(PartsOfExpression::closedBracket, str[0]);
//	}
//	else
//	{
//		return InfixType(PartsOfExpression::operation, str[0]);
//	}
//}

void novokhatskiy::inputInfix(Queue<Queue<InfixType>> infixQueue, std::istream& in)
{
	in >> std::noskipws;
	while (in)
	{
		char symb{};
		Queue< InfixType > currQ;
		InfixType res;
		while (in >> symb)
		{
			if (symb == ' ')
			{
				continue;
			}
			if (std::isdigit(symb))
			{
				std::string str = {};
				while (symb != ' ' && symb != '\n')
				{
					str += symb;
					in >> symb;
				}
				res.data_.operand.value_ = std::stoll(str);
				res.type_ = PartsOfExpression::operand;
				if (symb == '\n')
				{
					currQ.push(res);
					break;
				}
			}
			else if (symb == '(' || symb == ')')
			{
				res.data_.bracket.scope = symb;
				res.type_ = PartsOfExpression::bracket;
			}
			else
			{
				res.data_.operation.operation_ = symb;
				res.type_ = PartsOfExpression::operation;
			}
			currQ.push(res);
		}
		infixQueue.push(currQ);
	}
	in >> std::skipws;
}
