#include "MateriaSource.hpp"
#include "AMateria.hpp"

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
  if (!materia)
    return;
  for (int i = 0; i < 4; i++) {
    if (!_materias[i]) {
      _materias[i] = materia;
      return;
    }
  }
}

AMateria *MateriaSource::createMateria(std::string const &type) {
  for (int i = 0; i < 4; i++) {
    if (_materias[i]->getType() == type)
      return _materias[i]->clone();
  }
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
    if (_materias[i])
      this->_materias[i] = other._materias[i]->clone();
    else
      this->_materias[i] = 0;
  }
}
