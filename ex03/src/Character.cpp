#include "Character.hpp"
#include "AMateria.hpp"

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
  if (!materia)
    return;
  for (int i = 0; i < 4; i++) {
    if (!_inventory[i]) {
      _inventory[i] = materia;
      return;
    }
  }
  // Ownership always moves here: when full, destroy so the caller never leaks.
  delete materia;
}

void Character::unequip(int idx) {
  if (idx < 0 || idx >= 4 || !_inventory[idx])
    return;
  // unequip must not delete; the caller has to keep and delete this pointer.
  _inventory[idx] = 0;
}

void Character::use(int idx, ICharacter &target) {
  if (idx < 0 || idx >= 4 || !_inventory[idx])
    return;
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
