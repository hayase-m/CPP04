#include "Character.hpp"
#include "AMateria.hpp"

#include <iostream>

Character::Character(void) : _name("") {
  for (int i = 0; i < 4; i++)
    _inventory[i] = 0;
}

Character::Character(std::string const &name) : _name(name) {
  for (int i = 0; i < 4; i++)
    _inventory[i] = 0;
}

Character::Character(const Character &other) : _name(other._name) {
  for (int i = 0; i < 4; i++)
    _inventory[i] = 0;
  copyInventory(other);
}

Character &Character::operator=(const Character &other) {
  if (this != &other) {
    clearInventory();
    _name = other._name;
    copyInventory(other);
  }
  return *this;
}

Character::~Character(void) { clearInventory(); }

std::string const &Character::getName(void) const { return _name; }

void Character::equip(AMateria *materia) {
  if (!materia) {
    std::cerr << "Character: equip: null materia" << std::endl;
    return;
  }
  for (int i = 0; i < 4; i++) {
    if (!_inventory[i]) {
      _inventory[i] = materia;
      return;
    }
  }
  std::cerr << "Character: equip: inventory full, materia discarded" << std::endl;
  delete materia;
}

void Character::unequip(int idx) {
  if (idx < 0 || idx >= 4) {
    std::cerr << "Character: unequip: invalid index " << idx << std::endl;
    return;
  }
  if (!_inventory[idx]) {
    std::cerr << "Character: unequip: slot " << idx << " is empty" << std::endl;
    return;
  }
  _inventory[idx] = 0;
}

void Character::use(int idx, ICharacter &target) {
  if (idx < 0 || idx >= 4) {
    std::cerr << "Character: use: invalid index " << idx << std::endl;
    return;
  }
  if (!_inventory[idx]) {
    std::cerr << "Character: use: slot " << idx << " is empty" << std::endl;
    return;
  }
  _inventory[idx]->use(target);
}

void Character::clearInventory(void) {
  for (int i = 0; i < 4; i++) {
    delete _inventory[i];
    _inventory[i] = 0;
  }
}

void Character::copyInventory(const Character &other) {
  for (int i = 0; i < 4; i++) {
    if (other._inventory[i])
      _inventory[i] = other._inventory[i]->clone();
    else
      _inventory[i] = 0;
  }
}
