#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "list.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "output.hpp"

int main(int argc, char* argv[])
{
  std::istream* inputStream = &std::cin;
  std::ifstream file;
  bool fromFile = false;

  if (argc > 2)
  {
    std::cerr << "using: " << argv[0] << " [filename]" << '\n';
    return EXIT_FAILURE;
  }

  if (argc == 2)
  {
    file.open(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "cannot open file " << argv[1] << '\n';
      return EXIT_FAILURE;
    }
      inputStream = &file;
      fromFile = true;
    }

    std::string line;
    vojuck::Queue<int> resultsQueue;

    try
    {
      while (std::getline(*inputStream, line))
      {
        std::size_t start = line.find_first_not_of(" \t\r\n");
        std::size_t end = line.find_last_not_of(" \t\r\n");
        if (start == std::string::npos)
        {
          continue;
        }
        std::string trimmed = line.substr(start, end - start + 1);

        if (trimmed.empty())
        {
          continue;
        }

        vojuck::Queue<std::string> postfix =vojuck::infixToPostfix(trimmed);

        int result =vojuck::evaluatePostfix(postfix);

        resultsQueue.push(result);
      }

        vojuck::List<int> resultsList;
        while (!resultsQueue.isEmpty())
        {
            resultsList.push_front(resultsQueue.drop());
        }

        for (vojuck::List<int>::const_iterator it = resultsList.cbegin(); it != resultsList.cend(); ++it)
        {
          std::cout << *it;
          vojuck::List<int>::const_iterator nextIt = it;
          ++nextIt;
          if (nextIt != resultsList.cend())
          {
            std::cout << ' ';
          }
        }
        std::cout << '\n';

    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      if (fromFile)
      {
        file.close();
      }
      return EXIT_FAILURE;
    }

    if (fromFile)
    {
      file.close();
    }

    return EXIT_SUCCESS;
}
