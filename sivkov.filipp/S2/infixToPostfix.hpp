#ifndef INFIXTOPOSTFIX_HPP
#define INFIXTOPOSTFIX_HPP

#include <queue>
#include <iostream>
#include "postfixType.hpp"

void infixToPostFix(std::istream& inputFile, std::queue<PostfixType>& numb);

#endif


