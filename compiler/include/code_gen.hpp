#ifndef CODE_GEN_HPP
#define CODE_GEN_HPP

#include "parser.hpp"

class Generator {
public:
  inline Generator(NodeReturn root) : m_root(std::move(root)) {}

  [[nodiscard]] std::string generate() const;

private:
  const NodeReturn m_root;
};

#endif
