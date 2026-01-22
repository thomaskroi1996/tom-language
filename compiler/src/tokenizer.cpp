#include "tokenizer.hpp"
#include <iostream>
#include <string>
#include <vector>

std::vector<Token> Tokenizer::tokenize(std::string str) {
  std::string buf;

  std::vector<Token> tokens;

  for (int i = 0; i < str.length(); i++) {
    char c = str.at(i);
    if (std::isalpha(c)) {
      buf.push_back(c);
      i++;
      while (std::isalnum(str.at(i))) {
        buf.push_back(str.at(i));
        i++;
      }
      i--;

      if (buf == "return") {
        tokens.push_back({.type = TokenType::RETURN});
        buf.clear();
      } else {
        std::cout << "Token not recognised" << std::endl;
        exit(EXIT_FAILURE);
      }
    } else if (std::isdigit(c)) {
      while (std::isdigit(str.at(i))) {
        buf.push_back(str.at(i));
        i++;
      }
      i--;
      tokens.push_back({.type = TokenType::NUMERIC, .value = buf});
      buf.clear();
    } else if (c == ';') {
      tokens.push_back({.type = TokenType::SEMICOLON});
    } else if (std::isspace(c)) {
      continue;
    } else {
      std::cout << "unknown character" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  return tokens;
}

[[nodiscard]] std::optional<char> Tokenizer::peek(int ahead) const {
  if (m_index + ahead >= m_src.length()) {
    return {};
  } else {
    return m_src.at(m_index);
  }
};

char Tokenizer::consume() { return m_src.at(m_index++); };
