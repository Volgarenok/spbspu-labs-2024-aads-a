#include "input.hpp"
#include <iostream>
#include <string>
#include <queue.hpp>


namespace sivkov
{
  void inputString(std::istream& input, Queue< Queue< std::string > >& queueOfString)
  {
    std::string in = "";
    while (std::getline(input, in))
    {
      if (in == "")
      {
        continue;
      }
      Queue< std::string > infix1;
      for (size_t i = 0; i < in.length(); ++i)
      {
        std::string token = "";
        while (i < in.length() && !std::isspace(in[i]))
        {
          token += in[i];
          ++i;
        }
        infix1.push(token);
      }
      queueOfString.push(infix1);
    }
  }
}
