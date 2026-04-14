//
// Created by nosokvkokose on 11.04.26.
//

#include "parser.h"
#ifdef DEBUG
#include <iostream>
#endif

constexpr char OR = '|';
constexpr char AND = '&';
constexpr char NOT = '!';
constexpr char OPEN_BRACKET = '(';
constexpr char CLOSE_BRACKET = ')';

class Parser {
public:
    explicit Parser(std::string to_parse) : expr(std::move(to_parse)) {}

    evaluate_t parse() { return parseExpr(); }
private:
    std::string expr;
    size_t pos = 0;

    char peek() {
        while (pos < expr.size() && isspace(expr[pos])) pos++;
        return pos < expr.size() ? expr[pos] : 0;
    }
    char get() { return expr.at(pos++); }

    evaluate_t parseExpr() {
        auto left = parseAnd();
        while (peek() == OR) {
            get();
            auto right = parseAnd();


            // Parse all ORs
            left = [l = std::move(left), r = std::move(right)](const auto& v) {  // v is map
#ifdef DEBUG
                std::cout << l(v) << " OR "  << r(v) << std::endl;
#endif

                return l(v) || r(v);
            };
        }

        return left;
    }

    evaluate_t parseAnd() {
        auto left = parseFactor();
        while (peek() == AND) {
            get();

            auto right = parseFactor();
            left = [l = std::move(left), r = std::move(right)](const auto& v) {  // v is map
#ifdef DEBUG
                std::cout << l(v) << " AND "  << r(v) << std::endl;
#endif
                return l(v) && r(v);
            };
        }

        return left;
    }

    evaluate_t parseFactor() {
        char c = peek();
        if (c == NOT) {
            get();
            auto inner = parseFactor();
            return [f = std::move(inner)](const auto& v) { return !f(v); };
        }
        if (c == OPEN_BRACKET) {
            get();
            auto inner = parseExpr();
            get(); // Closing bracket
            return inner;
        }

        c = get();
        return [c](const auto& v) { return v.at(c); };
    }
};

evaluate_t parse(const std::string &expression) {
    Parser parser(expression);

    return parser.parse();
}
