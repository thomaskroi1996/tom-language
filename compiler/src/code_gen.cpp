#include <sstream>

#include "code_gen.hpp"

[[nodiscard]] std::string Generator::generate() const {
  std::stringstream asm_;

  asm_ << "global _start\n_start:\n";
  asm_ << "    mov rax, 60\n";
  asm_ << "    mov rdi, " << m_root.expr.int_literal.value.value() << "\n";
  asm_ << "    syscall";

  return asm_.str();
}
