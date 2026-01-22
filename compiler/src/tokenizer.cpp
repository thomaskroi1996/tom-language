#include "tokenizer.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

std::vector<Token> Tokenizer::tokenize(std::string str) {
  std::string buf;

  std::vector<Token> tokens;

  while (peek().has_value()) {
    if (std::isalpha(peek().value())) {
      buf.push_back(consume());
      while (std::isalpha(peek().value())) {
        buf.push_back(consume());
      }
      if (buf == "return") {
        tokens.push_back({.type = TokenType::RETURN});
        buf.clear();
      } else {
        std::cout << "Token not recognised" << std::endl;
        exit(EXIT_FAILURE);
      }
    } else if (std::isdigit(peek().value())) {
      while (std::isdigit(peek().value())) {
        buf.push_back(consume());
      }
      tokens.push_back({.type = TokenType::NUMERIC, .value = buf});
      buf.clear();
    } else if (peek().value() == ';') {
      tokens.push_back({.type = TokenType::SEMICOLON});
      consume();
    } else if (std::isspace(peek().value())) {
      consume();
      continue;
    } else {
      std::cout << "unknown character" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  m_index = 0;

  return tokens;
}

[[nodiscard]] std::optional<char> Tokenizer::peek(int ahead) const {
  if (m_index + ahead > m_src.length()) {
    return {};
  } else {
    return m_src.at(m_index);
  }
};

char Tokenizer::consume() { return m_src.at(m_index++); };
