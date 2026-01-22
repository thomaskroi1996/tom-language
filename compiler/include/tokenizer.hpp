#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <optional>
#include <string>
#include <vector>

enum class TokenType {
  RETURN,
  NUMERIC,
  SEMICOLON,
};

struct Token {
  TokenType type;
  std::optional<std::string> value;
};

class Tokenizer {
public:
  Tokenizer(std::string src) : m_src(std::move(src)) {};

  std::vector<Token> tokenize(std::string str);

private:
  [[nodiscard]] std::optional<char> peek(int ahead = 1) const;
  char consume();
  const std::string m_src;
  int m_index;
};

#endif
