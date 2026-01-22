#include "parser.hpp"
#include <iostream>

[[nodiscard]] std::optional<Token> Parser::peek(int ahead) const {
  if (m_index + ahead > m_tokens.size()) {
    return {};
  } else {
    return m_tokens.at(m_index);
  }
};

Token Parser::consume() { return m_tokens.at(m_index++); };

std::optional<NodeExpr> Parser::parse_expr() {
  if (peek().has_value() && peek().value().type == TokenType::NUMERIC) {
    return NodeExpr{.int_literal = consume()};
  } else {
    return {};
  }
}

std::optional<NodeReturn> Parser::parse() {
  std::optional<NodeReturn> return_node;
  while (peek().has_value()) {
    if (peek().value().type == TokenType::RETURN) {
      if (auto node_expr = parse_expr()) {
        return_node = NodeReturn{.expr = node_expr.value()};
      } else {
        std::cerr << "Invalid expression" << std::endl;
        exit(EXIT_FAILURE);
      }
      if (!peek().has_value() || peek().value().type != TokenType::SEMICOLON) {
        std::cerr << "Invalid expression" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }
  m_index = 0;

  return return_node;
}
