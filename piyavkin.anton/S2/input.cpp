#include "input.hpp"
#include <iostream>

// void piyavkin::input(std::istream& in, List< Queue< char > >& queues)
// {
//   char symbol = 0;
//   in >> std::noskipws;
//   while (!in.eof())
//   {
//     Queue< char > q;
//     while (symbol != '\n')
//     {
//       in >> symbol;
//       if (in)
//       {
//         throw std::logic_error("Bad input");
//       }
//       if (symbol != ' ')
//       {
//         q.push(symbol);
//       }
//     }
//     queues.push_back(q);
//   }
//   in >> std::skipws;
// }