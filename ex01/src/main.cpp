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
    animals[i]->makeSound();

  for (int i = 0; i < 4; i++)
    delete animals[i];

  std::cout << std::endl;

  Dog dog;
  dog.getBrain()->setIdea(0, "bone");
  Dog dogCopy(dog);
  Dog dogAssign;
  dogAssign = dog;
  std::cout << dog.getBrainAddress() << " " << dogCopy.getBrainAddress() << " "
            << dogAssign.getBrainAddress() << std::endl;
  dog.getBrain()->setIdea(0, "cat");
  std::cout << "dog: " << dog.getBrain()->getIdea(0)
            << " / copy: " << dogCopy.getBrain()->getIdea(0)
            << " / assign: " << dogAssign.getBrain()->getIdea(0) << std::endl;

  std::cout << std::endl;

  Cat cat;
  cat.getBrain()->setIdea(0, "fish");
  Cat catCopy(cat);
  Cat catAssign;
  catAssign = cat;
  std::cout << cat.getBrainAddress() << " " << catCopy.getBrainAddress() << " "
            << catAssign.getBrainAddress() << std::endl;
  cat.getBrain()->setIdea(0, "nap");
  std::cout << "cat: " << cat.getBrain()->getIdea(0)
            << " / copy: " << catCopy.getBrain()->getIdea(0)
            << " / assign: " << catAssign.getBrain()->getIdea(0) << std::endl;

  return 0;
}
