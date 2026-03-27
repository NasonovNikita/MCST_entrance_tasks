//
// Created by nosokvkokose on 26.03.26.
//

#ifndef PARSER_H
#define PARSER_H

#include <cstddef>
#include <string>
#include <memory>

constexpr size_t VARIABLES_COUNT = 26;

enum class NodeType {
    AND,
    OR,
    NOT,
    VAL
};


struct Node {
    using Ptr = std::unique_ptr<Node>;

    Ptr left = nullptr;
    Ptr right = nullptr;
    NodeType type;
    char val;

    explicit Node(const char value) : type(NodeType::VAL), val(value) {}

    Node(const NodeType type, Ptr left, Ptr right)
        : left(std::move(left)), right(std::move(right)), type(type), val('\0') {}
};

// Parses a logical expression with AND, OR, NOT, brackets, and variables A-Z
Node::Ptr parse(const std::string& expression);

bool evaluate(const Node& tree, const std::array<bool, VARIABLES_COUNT>& values);

#endif //PARSER_H
