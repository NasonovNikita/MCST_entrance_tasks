//
// Created by nosokvkokose on 26.03.26.
//

#include "parser.h"

#include <utility>
#include <unordered_set>
#include <stdexcept>
#include <regex>

enum class ExpressionType {
    UNARY,
    BINARY,
    BRACKET
};

class Expression {
public:
    Expression(const ExpressionType type, std::regex form, const int order)
        : type(type), form(std::move(form)), order(order) {
    }

private:
    ExpressionType type;
    std::regex form;
    int order;
};

const std::unordered_set<Expression> expressions = {Expression(ExpressionType::BRACKET, std::regex(R"("), 0)};

Node::Ptr parse(std::string expression) {

}


bool evaluate(const Node& tree, const std::map<char, bool>& values) {

}
