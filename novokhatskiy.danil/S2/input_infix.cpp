#include "input_infix.hpp"

novokhatskiy::InfixType novokhatskiy::checkType(std::string& str)
{
	if (std::isdigit(str[0]))
	{
		return InfixType(PartsOfExpression::operand, str[0]);
	}
	else if (str[0] == '(')
	{
		return InfixType(PartsOfExpression::openBracket, str[0]);
	}
	else if (str[0] == ')')
	{
		return InfixType(PartsOfExpression::closedBracket, str[0]);
	}
	else
	{
		return InfixType(PartsOfExpression::operation, str[0]);
	}
}

void novokhatskiy::inputInfix(Queue<Queue<InfixType>> infixQueue, std::istream& in)
{

}
