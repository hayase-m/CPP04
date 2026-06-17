#include "Cat.hpp"

#include <iostream>

Cat::Cat() : Animal(), brain(new Brain()) {
  type = "Cat";
  std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other), brain(new Brain(*other.brain)) {
  std::cout << "Cat copy constructor called" << std::endl;
}

Cat::~Cat() {
  std::cout << "Cat destructor called" << std::endl;
  delete brain;
}

Cat &Cat::operator=(const Cat &other) {
  std::cout << "Cat copy assignment operator called" << std::endl;
  if (this != &other) {
    Animal::operator=(other);
    *brain = *other.brain;
  }
  return *this;
}

void Cat::makeSound() const { std::cout << "Meow!" << std::endl; }

const Brain *Cat::getBrainAddress() const { return brain; }