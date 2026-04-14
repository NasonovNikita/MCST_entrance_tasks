//
// Created by nosokvkokose on 20.03.26.
//

#include "parser.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>

unsigned long unmask(const unsigned long mask, const size_t n, const size_t i) {
    return mask >> (n - 1 - i) & 1;
}

int main() {
    std::string expr;
    std::getline(std::cin, expr);

    auto [evaluate, variables] = parse(expr);

#ifdef DEBUG
    std::cout << "Variables: ";
    for (auto var: variables) {
        std::cout << var << " ";
    }
    std::cout << std::endl;
#endif

    const size_t n = variables.size();
    std::sort(variables.begin(), variables.end());

    for (auto var: variables) {
        std::cout << var << " ";
    }
    std::cout << "Result" << std::endl;

    // Iterate through all combinations (2^n possibilities)
    for (unsigned long mask = 0; mask < (1ULL << n); ++mask) {  // Iterate by mask
        std::unordered_map<char, bool> assignment;
        for (size_t i = 0; i < n; ++i) {
            assignment[variables[i]] = unmask(mask, n, i);  // Get i-th bit
        }

        // Print variable values
        for (size_t i = 0; i < n; ++i) {
            printf("%ld ", unmask(mask, n, i));
        }

        // Evaluate and print result
        const bool result = evaluate(assignment);
        printf("%d\n", result ? 1 : 0);
    }

    return 0;
}
