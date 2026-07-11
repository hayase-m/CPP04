#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "IMateriaSource.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

#include <iostream>

// 所有権のルール:
// - learnMateria/equip: 渡した時点で所有権が移る。満杯なら受け取った側がdeleteする。
// - createMateria: 新しいcloneを返し、所有権は呼び出し側。deleteするかequipで手放す。
// - unequip: deleteしない。所有権が呼び出し側に戻るので、控えたポインタでdeleteする。
// - Character/MateriaSource: 保持中のMateriaをデストラクタでdeleteする。
int main() {
  IMateriaSource *src = new MateriaSource();
  // newしたMateriaの所有権はlearnMateriaに渡した時点でsrcへ移る
  src->learnMateria(new Ice());
  src->learnMateria(new Cure());

  ICharacter *me = new Character("me");

  AMateria *tmp;
  // createMateriaが返すcloneは呼び出し側の所有。equipした時点でmeへ移る
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
  // unequipはdeleteせず所有権をこちらに返すだけ。控えたポインタで自分でdelete
  me->unequip(2);
  me->use(2, *bob);
  delete dropped;

  std::cout << "\n[full inventory]" << std::endl;
  me->equip(src->createMateria("ice"));
  me->equip(src->createMateria("cure"));
  // 在庫満杯でも所有権はequipに移り、equipが内部でdeleteする（こちらは触らない）
  me->equip(src->createMateria("ice"));

  std::cout << "\n[full materia source]" << std::endl;
  src->learnMateria(new Ice());
  src->learnMateria(new Cure());
  // 満杯でも所有権はlearnMateriaに移り、内部でdeleteされる
  src->learnMateria(new Ice());

  std::cout << "\n[character deep copy]" << std::endl;
  Character original("original");
  AMateria *cure = src->createMateria("cure");
  original.equip(cure);
  // copiedはcloneした別のMateriaを所有する（originalと共有しない）
  Character copied(original);
  original.unequip(0);
  delete cure;
  copied.use(0, *bob);

  Character assigned("assigned");
  assigned.equip(src->createMateria("ice"));
  // 代入は自分が所有していた装備をdeleteしてから、copiedのcloneを所有し直す
  assigned = copied;
  assigned.use(0, *bob);

  std::cout << "\n[materia source deep copy]" << std::endl;
  MateriaSource baseSource;
  baseSource.learnMateria(new Ice());
  MateriaSource copiedSource(baseSource);
  // このcloneの所有権は呼び出し側なので、使い終わったら自分でdelete
  tmp = copiedSource.createMateria("ice");
  if (tmp) {
    tmp->use(*bob);
    delete tmp;
  }

  // 装備中・習得済みのMateriaは各デストラクタがまとめてdeleteする
  delete bob;
  delete me;
  delete src;

  return 0;
}
