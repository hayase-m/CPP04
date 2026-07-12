#include "Dog.hpp"

#include <iostream>

Dog::Dog() : Animal(), brain(new Brain()) {
  type = "Dog";
  std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other), brain(new Brain(*other.brain)) {
  std::cout << "Dog copy constructor called" << std::endl;
}

Dog::~Dog() {
  std::cout << "Dog destructor called" << std::endl;
  delete brain;
}

Dog &Dog::operator=(const Dog &other) {
  std::cout << "Dog copy assignment operator called" << std::endl;
  if (this != &other) {
    Animal::operator=(other);
    *brain = *other.brain;
  }
  return *this;
}

void Dog::makeSound() const { std::cout << "Woof!" << std::endl; }

const Brain *Dog::getBrainAddress() const { return brain; }

Brain *Dog::getBrain() { return brain; }
