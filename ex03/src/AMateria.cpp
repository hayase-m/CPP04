#include "AMateria.hpp"

AMateria::AMateria(std::string const &type) : type(type) {}

AMateria::AMateria(void) : type("") {}

AMateria::AMateria(const AMateria &other) : type(other.type) {}

AMateria &AMateria::operator=(const AMateria &other) {
  // typeはクラス固有の識別子なのでコピーしない(subjectのヒント準拠)
  (void)other;
  return *this;
}

AMateria::~AMateria(void) {}

std::string const &AMateria::getType(void) const { return type; }

void AMateria::use(ICharacter &target) { (void)target; }
