#include <iostream>
#include "list.hpp"
#include "node.hpp"
#include "iterator.hpp"
#include "constiterator.hpp"
#include "process_sequences.hpp"

int main() {
    try {
        stepanov::process_sequences();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
