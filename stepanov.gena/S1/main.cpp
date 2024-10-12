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
    catch (const std::overflow_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::exit(1);
    }
    return 0;
}
