#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
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

std::vector<Token> tokenize(std::string str) {
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

std::string tokens_to_asm(const std::vector<Token> &tokens) {
  std::stringstream asm_;
  asm_ << "global _start\n_start:\n";

  for (int i = 0; i < tokens.size(); i++) {
    Token t = tokens.at(i);
    if (t.type == TokenType::RETURN) {
      if (i + 1 < tokens.size() &&
          tokens.at(i + 1).type == TokenType::NUMERIC) {
        if (i + 2 < tokens.size() &&
            tokens.at(i + 2).type == TokenType::SEMICOLON) {
          asm_ << "    mov rax, 60\n";
          asm_ << "    mov rdi, " << tokens.at(i + 1).value.value() << "\n";
          asm_ << "    syscall";
        }
      }
    }
  }
  return asm_.str();
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Error: Correct usage: ./tom_compiler source.tom";
    exit(EXIT_FAILURE);
  }

  std::string contents;
  {
    std::fstream input(argv[1], std::ios::in);
    std::stringstream buffer;
    buffer << input.rdbuf();
    contents = buffer.str();
  }

  std::cout << contents << std::endl;

  std::vector<Token> t = tokenize(contents);
  {
    std::fstream output("out.asm", std::ios::out);
    output << tokens_to_asm(t);
  }
}
