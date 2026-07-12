#include "MateriaSource.hpp"
#include "AMateria.hpp"

#include <iostream>

MateriaSource::MateriaSource(void) {
  for (int i = 0; i < 4; i++)
    _materias[i] = 0;
}

MateriaSource::MateriaSource(const MateriaSource &other) {
  for (int i = 0; i < 4; i++)
    _materias[i] = 0;
  copyMaterias(other);
}

MateriaSource &MateriaSource::operator=(const MateriaSource &other) {
  if (this != &other) {
    clearMaterias();
    copyMaterias(other);
  }
  return *this;
}

MateriaSource::~MateriaSource(void) { clearMaterias(); }

void MateriaSource::learnMateria(AMateria *materia) {
  if (!materia) {
    std::cerr << "MateriaSource: learnMateria: null materia" << std::endl;
    return;
  }
  for (int i = 0; i < 4; i++) {
    if (!_materias[i]) {
      _materias[i] = materia;
      return;
    }
  }
  std::cerr << "MateriaSource: learnMateria: source full, materia discarded"
            << std::endl;
  delete materia;
}

AMateria *MateriaSource::createMateria(std::string const &type) {
  for (int i = 0; i < 4; i++) {
    if (_materias[i] && _materias[i]->getType() == type)
      return _materias[i]->clone();
  }
  std::cerr << "MateriaSource: createMateria: unknown type: " << type
            << std::endl;
  return 0;
}

void MateriaSource::clearMaterias(void) {
  for (int i = 0; i < 4; i++) {
    delete _materias[i];
    _materias[i] = 0;
  }
}

void MateriaSource::copyMaterias(const MateriaSource &other) {
  for (int i = 0; i < 4; i++) {
    if (other._materias[i])
      _materias[i] = other._materias[i]->clone();
    else
      _materias[i] = 0;
  }
}
