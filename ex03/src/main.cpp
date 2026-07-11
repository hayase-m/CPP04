#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "IMateriaSource.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

#include <iostream>

int main() {
  IMateriaSource *src = new MateriaSource();
  src->learnMateria(new Ice());
  src->learnMateria(new Cure());

  ICharacter *me = new Character("me");

  AMateria *tmp;
  tmp = src->createMateria("ice");
  me->equip(tmp);
  tmp = src->createMateria("cure");
  me->equip(tmp);

  ICharacter *bob = new Character("bob");

  me->use(0, *bob);
  me->use(1, *bob);

  std::cout << "\n[edge cases]" << std::endl;
  me->use(2, *bob);
  me->use(-1, *bob);
  me->unequip(4);
  if (!src->createMateria("fire"))
    std::cout << "unknown type returns 0" << std::endl;

  std::cout << "\n[unequip ownership]" << std::endl;
  AMateria *dropped = src->createMateria("ice");
  me->equip(dropped);
  me->unequip(2);
  me->use(2, *bob);
  delete dropped;

  std::cout << "\n[full inventory]" << std::endl;
  me->equip(src->createMateria("ice"));
  me->equip(src->createMateria("cure"));
  // Inventory is full: equip takes ownership and deletes the materia.
  me->equip(src->createMateria("ice"));

  std::cout << "\n[full materia source]" << std::endl;
  src->learnMateria(new Ice());
  src->learnMateria(new Cure());
  // Source is full: learnMateria takes ownership and deletes the materia.
  src->learnMateria(new Ice());

  std::cout << "\n[character deep copy]" << std::endl;
  Character original("original");
  AMateria *cure = src->createMateria("cure");
  original.equip(cure);
  Character copied(original);
  original.unequip(0);
  delete cure;
  copied.use(0, *bob);

  Character assigned("assigned");
  assigned.equip(src->createMateria("ice"));
  assigned = copied;
  assigned.use(0, *bob);

  std::cout << "\n[materia source deep copy]" << std::endl;
  MateriaSource baseSource;
  baseSource.learnMateria(new Ice());
  MateriaSource copiedSource(baseSource);
  tmp = copiedSource.createMateria("ice");
  if (tmp) {
    tmp->use(*bob);
    delete tmp;
  }

  delete bob;
  delete me;
  delete src;

  return 0;
}
