//
// Created by nosokvkokose on 20.03.26.
//

#include "parser.h"
#include <iostream>


int main() {
    std::string expr;
    std::cin >> expr;

    const evaluate_t evaluate = parse(expr);

    printf("%d\n", evaluate({{'A', true}, {'B', false}}));

    return 0;
}
