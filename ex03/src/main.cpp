#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "IMateriaSource.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

#include <iostream>

// 所有権のルール:
// - learnMateria:
// 渡した時点で所有権がsrcへ移る。満杯でもsrc側が引き取ってdeleteする。
// - equip:
// 成功なら所有権がCharacterへ移る。満杯なら何も起きず所有権は呼び出し側のまま。
// - createMateria:
// 新しいcloneを返し、所有権は呼び出し側。deleteするかequipで手放す。
// - unequip:
// deleteしない。所有権が呼び出し側に戻るので、控えたポインタでdeleteする。
// - Character/MateriaSource: 保持中のMateriaをデストラクタでdeleteする。
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
  // 満杯のequipは何も起きない。アドレスを控えてあるので自分でdeleteする
  AMateria *overflow = src->createMateria("ice");
  me->equip(overflow);
  delete overflow;

  std::cout << "\n[full materia source]" << std::endl;
  src->learnMateria(new Ice());
  src->learnMateria(new Cure());
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
