#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

#include <iostream>

static void testPolymorphism() {
  const Animal *meta = new Animal();
  const Animal *dog = new Dog();
  const Animal *cat = new Cat();

  std::cout << std::endl;
  std::cout << dog->getType() << " " << std::endl;
  std::cout << cat->getType() << " " << std::endl;
  cat->makeSound();
  dog->makeSound();
  meta->makeSound();
  std::cout << std::endl;

  delete cat;
  delete dog;
  delete meta;
}

static void testWrongPolymorphism() {
  const WrongAnimal *wrongMeta = new WrongAnimal();
  WrongCat *wrongCat = new WrongCat();
  // Keep the derived pointer for safe delete;
  const WrongAnimal *wrongAsAnimal = wrongCat;

  std::cout << std::endl;
  std::cout << wrongAsAnimal->getType() << " " << std::endl;
  wrongAsAnimal->makeSound();
  wrongCat->makeSound();
  wrongMeta->makeSound();
  std::cout << std::endl;

  delete wrongCat;
  delete wrongMeta;
}

int main() {
  testPolymorphism();
  testWrongPolymorphism();
  return 0;
}
