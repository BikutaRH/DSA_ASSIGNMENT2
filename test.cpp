#include <iostream>
using namespace std;
 
class Pet {
protected:
    string Name;
public:
    int a = 1;
    Pet(string n) { Name = n; }
    virtual string getSound() { return "";};
    void makeSound(void) { cout << Name << "says: " << getSound() << endl; }
};
 
class Cat : public Pet {
public:
    Cat(string n) : Pet(n) { }
    string getSound() { return "Meow! Meow!";};
    int getint(){
        return 1;
    }
};
 
class Dog : public Pet {
public:
    Dog(string n) : Pet(n) { }
    string getSound() { return "Woof! Woof!";};
};
 
int main(void) {
    Pet *a_pet = new Cat("Kitty");;
    a_pet->makeSound();
    cout << a_pet->a;
    delete a_pet;
 
    a_pet = new Dog("Doggie");
    a_pet->makeSound();
    delete a_pet;
 
    return 0;
}