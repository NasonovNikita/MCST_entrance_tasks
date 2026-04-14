//
// Created by nosokvkokose on 26.03.26.
//
#pragma once

#ifndef PARSER_H
#define PARSER_H

#include <cstddef>
#include <string>
#include <unordered_map>
#include <functional>

constexpr size_t VARIABLES_COUNT = 26;

using evaluate_t = std::function<bool(const std::unordered_map<char, bool>&)>;

typedef struct {
    evaluate_t evaluate;
    std::vector<char> variables;
} expression_t;

expression_t parse(const std::string &expression);

#endif //PARSER_H
