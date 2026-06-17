#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

#include <iostream>

int main() {
  Animal *animals[4];
  animals[0] = new Dog();
  animals[1] = new Dog();
  animals[2] = new Cat();
  animals[3] = new Cat();

  for (int i = 0; i < 4; i++)
    delete animals[i];

  std::cout << std::endl;

  Dog dog;
  Dog dogCopy(dog);
  Dog dogAssign;
  dogAssign = dog;
  std::cout << dog.getBrainAddress() << " " << dogCopy.getBrainAddress() << " "
            << dogAssign.getBrainAddress() << std::endl;

  std::cout << std::endl;

  Cat cat;
  Cat catCopy(cat);
  Cat catAssign;
  catAssign = cat;
  std::cout << cat.getBrainAddress() << " " << catCopy.getBrainAddress() << " "
            << catAssign.getBrainAddress() << std::endl;

  return 0;
}
