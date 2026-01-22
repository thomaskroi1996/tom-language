#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "tokenizer.hpp"

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

  Tokenizer tokenizer = Tokenizer(contents);
  std::vector<Token> t = tokenizer.tokenize(contents);
  {
    std::fstream output("out.asm", std::ios::out);
    output << tokens_to_asm(t);
  }
}
