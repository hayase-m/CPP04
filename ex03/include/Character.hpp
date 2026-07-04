#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"

class Character : public ICharacter {
private:
  std::string _name;
  AMateria *_inventory[4];

  void clearInventory(void);
  void copyInventory(const Character &other);

public:
  Character(void);
  Character(std::string const &name);
  Character(const Character &other);
  Character &operator=(const Character &other);
  ~Character(void);

  std::string const &getName(void) const;
  void equip(AMateria *materia);
  void unequip(int idx);
  void use(int idx, ICharacter &target);
};

#endif
