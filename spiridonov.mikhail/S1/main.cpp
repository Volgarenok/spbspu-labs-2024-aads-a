#include <iostream>
#include "forward_sequence.hpp"

namespace spiridonov {

  void processSequences()
  {
    const int max_sequence_len = 100;
    const int max_sequences = 100;

    NamedSequence<int> namedSequences[max_sequences];
    int numSequences = 0;

    char sequenceName[max_sequence_len];

    while (numSequences < max_sequences && std::cin.getline(sequenceName, max_sequence_len))
    {
      if (sequenceName[0] == '\0')
      {
        continue;
      }

      int i = 0;
      while (sequenceName[i] != ' ' && sequenceName[i] != '\0')
      {
        namedSequences[numSequences].name[i] = sequenceName[i];
        i++;
      }
      namedSequences[numSequences].name[i] = '\0';

      namedSequences[numSequences].length = 0;

      i++;
      int value = 0;
      while (sequenceName[i] != '\0')
      {
        if (sequenceName[i] == ' ')
        {
          namedSequences[numSequences].sequence[namedSequences[numSequences].length++] = value;
          value = 0;
        }
        else {
          value = value * 10 + (sequenceName[i] - '0');
        }
        i++;
      }

      if (value != 0)
      {
        namedSequences[numSequences].sequence[namedSequences[numSequences].length++] = value;
      }

      numSequences++;
    }

    int allNumbers[max_sequences * max_sequence_len];
    int sumIndex = 0;

    int maxSequenceLength = 0;
    for (int i = 0; i < numSequences; ++i) {
      maxSequenceLength = std::max(maxSequenceLength, namedSequences[i].length);
    }

    for (int i = 0; i < maxSequenceLength; ++i)
    {
      for (int j = 0; j < numSequences; ++j)
      {
        if (i < namedSequences[j].length)
        {
          allNumbers[sumIndex++] = namedSequences[j].sequence[i];
        }
      }
    }

    for (int i = 0; i < sumIndex; ++i)
    {
      std::cout << allNumbers[i] << " ";
      if ((i + 1) % numSequences == 0) {
        std::cout << "\n";
      }
    }

    for (int i = 0; i < maxSequenceLength; ++i)
    {
      int sum = 0;
      for (int j = 0; j < numSequences; ++j)
      {
        if (i < namedSequences[j].length)
        {
          sum += namedSequences[j].sequence[i];
        }
      }
      std::cout << sum << " ";
    }
    std::cout << "\n";

  }

}

int main()
{
  spiridonov::processSequences();
  return 0;
}
