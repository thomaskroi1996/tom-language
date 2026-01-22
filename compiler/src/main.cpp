#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "code_gen.hpp"
#include "parser.hpp"
#include "tokenizer.hpp"

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
  
  Parser parser(std::move(t));
  std::optional<NodeReturn> tree = parser.parse();

  if (!tree.has_value()) {
    std::cerr << "No return statement found" << std::endl;
    exit(EXIT_FAILURE);
  }

  Generator generator(tree.value());

  {
    std::fstream output("out.asm", std::ios::out);
    output << generator.generate();
  }
}
