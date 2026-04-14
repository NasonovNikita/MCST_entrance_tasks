//
// Created by nosokvkokose on 11.04.26.
//

#include "parser.h"

#include <stdexcept>
#ifdef DEBUG
#include <iostream>
#endif

const std::string OR = "OR";
const std::string AND = "AND";
const std::string NOT = "NOT";
const std::string OPEN_BRACKET = "(";
const std::string CLOSE_BRACKET = ")";

class Parser {
public:
    explicit Parser(std::string to_parse) : expr(std::move(to_parse)) {}

    void parse() {
        pos = 0;
#ifdef DEBUG
        std::cout << "Parsing: " << expr << std::endl;
#endif
        eval_func = parseExpr();

        if (pos != expr.size())
            throw std::runtime_error("Error while parsing expression");
    }

    [[nodiscard]] evaluate_t get_eval_func() const { return eval_func; }
    [[nodiscard]] std::vector<char> get_variables() const { return variables; }
private:
    evaluate_t eval_func;
    std::vector<char> variables;
    std::string expr;
    bool latest_is_variable = false;
    size_t pos = 0;

    std::string peek() {
        const size_t preserve_pos = pos;

        std::string elem = get();
        pos = preserve_pos;
#ifdef DEBUG
        if (!elem.empty())
            std::cout << "Peeked: " << elem << std::endl;
#endif
        return elem;
    }

    std::string get() {
        // Skip spaces
        while (pos < expr.size() && isspace(expr[pos])) pos++;

        if (pos >= expr.size()) {
#ifdef DEBUG
            std::cout << "End of expr" << std::endl;
#endif
            return "";
        }

        const size_t start = pos;  // Start of elem

        // Find the end of the current elem
        while (pos < expr.size() && !isspace(expr[pos])) {
            pos++;

            // Return brackets immediately
            if (expr[pos - 1] == OPEN_BRACKET.at(0) ||
                expr[pos - 1] == CLOSE_BRACKET.at(0)) {
                break;
            }
        }

        std::string res = expr.substr(start, pos - start);

        return res;
    }

    evaluate_t parseExpr() {
        auto left = parseAnd();
        while (peek() == OR) {
            latest_is_variable = false;
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
            latest_is_variable = false;
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
        std::string elem = peek();
        if (elem == NOT) {
            latest_is_variable = false;
            get();
            auto inner = parseFactor();
            return [f = std::move(inner)](const auto& v) {

#ifdef DEBUG
                std::cout << " NOT "  << f(v) << std::endl;
#endif
                return !f(v);
            };
        }
        if (elem == OPEN_BRACKET) {
            get();
            auto inner = parseExpr();
            get(); // Closing bracket
            return inner;
        }

        if (latest_is_variable) {
            throw std::runtime_error("Two variables in a row");
        }

        elem = get();
        variables.push_back(elem.at(0));
        latest_is_variable = true;
        return [elem](const auto& v) { return v.at(elem.at(0)); };
    }
};

expression_t parse(const std::string &expression) {
    Parser parser(expression);
    parser.parse();

    expression_t result;
    result.evaluate = parser.get_eval_func();
    result.variables = parser.get_variables();
    return result;
}
