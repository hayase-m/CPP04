#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
private:
  AMateria *_materias[4];

  void clearMaterias(void);
  void copyMaterias(const MateriaSource &other);

public:
  MateriaSource(void);
  MateriaSource(const MateriaSource &other);
  MateriaSource &operator=(const MateriaSource &other);
  ~MateriaSource(void);

  void learnMateria(AMateria *materia);
  AMateria *createMateria(std::string const &type);
};

#endif
