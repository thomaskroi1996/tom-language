#ifndef PARSER_HPP
#define PARSER_HPP

#include "tokenizer.hpp"

struct NodeExpr {
  Token int_literal;
};

struct NodeReturn {
  NodeExpr expr;
};

class Parser {
public:
  inline explicit Parser(std::vector<Token> tokens)
      : m_tokens(std::move(tokens)) {}

  std::optional<NodeReturn> parse();
  std::optional<NodeExpr> parse_expr();

private:
  const std::vector<Token> m_tokens;
  [[nodiscard]] std::optional<Token> peek(int ahead = 1) const;
  Token consume();
  size_t m_index = 0;
};

#endif
