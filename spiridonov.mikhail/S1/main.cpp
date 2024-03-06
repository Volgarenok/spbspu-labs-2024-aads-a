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

    for (int i = 0; i < numSequences; ++i)
    {
      std::cout << namedSequences[i].name << " ";
    }
    std::cout << "\n";


    int maxSequenceLength = 0;
    for (int i = 0; i < numSequences; ++i) {
      maxSequenceLength = std::max(maxSequenceLength, namedSequences[i].length);
    }

    for (int i = 0; i < maxSequenceLength; ++i)
    {
      bool printed = false;
      for (int j = 0; j < numSequences; ++j)
      {
        if (i < namedSequences[j].length)
        {
          std::cout << namedSequences[j].sequence[i] << " ";
          printed = true;
        }
      }
      if (printed)
      {
        std::cout << "\n";
      }
    }

    for (int i = 0; i < maxSequenceLength; ++i)
    {
      int sum = 0;
      bool summed = false;
      for (int j = 0; j < numSequences; ++j)
      {
        if (i < namedSequences[j].length)
        {
          sum += namedSequences[j].sequence[i];
          summed = true;
        }
      }

      if (summed)
      {
        std::cout << sum << " ";
      }
    }
    std::cout << "\n";
  }

}
int main()
{
  spiridonov::processSequences();
  return 0;
}
