/***
 Problem for week 2: Animal Shelter

An animal shelter holds only dogs and cats, and operates on a strictly "first in, first out" basis.
People must adopt either the "oldest" (based on arrival time) of all animals at the shelter, or they can select whether they
would prefer a dog or a cat (and will receive the oldest animal of that type). They cannot select which specific animal they would like.
Create the data structures to maintain this system and implement operations such as enqueue, dequeueAny, dequeueDog and dequeueCat.

 ***/

#include <iostream>
#include <queue>
#include <variant>

enum class AnimalTypes { CAT, DOG };

class Animal {
 public:
    Animal() {timeStamp += timeStamp;};
    static unsigned int timeStamp;
    void print();
};
void Animal::print() {
    std::cout << "Animal\n";
}
unsigned int Animal::timeStamp = 0;


/***** Cat base class***/
class Cat : Animal{
private:
    AnimalTypes type {AnimalTypes::CAT};
public:
    void print();
    AnimalTypes getType(){return type;};
};
void Cat::print() {
    std::cout << "Cat\n";
}

/***** Dog base class***/
class Dog : Animal {
private:
    AnimalTypes type {AnimalTypes::DOG};
public:
    void print();
    AnimalTypes getType(){return type;};
};
void Dog::print() {
    std::cout << "Dog\n";
}


/*** Animal Shelter to store dogs and cats in a queuelike data structure ***/
class AnimalShelter {

public:
    template <typename T>
    void enqueue(T t);
    template <typename T>
    T dequeueAny();
    Cat dequeueCat();
    Dog dequeueDog();

private:
    std::queue<Cat> cats;
    std::queue<Dog> dogs;
};


template <typename T>
void AnimalShelter::enqueue(T t) {
    if (t->getType() == AnimalTypes::CAT) {
        cats.push(t);
    }

    dogs.push(t);
}


template <typename T>
T AnimalShelter::dequeueAny() {
    if (cats.empty()) {
        return dequeueDog();
    }

    if (dogs.empty()) {
        return dequeueCat();
    }

    Cat oldestCat = cats.front;
    Dog oldestDog = dogs.front;

    if(oldestCat.timeStamp > oldestDog.timeStamp) {
        return dequeueCat();
    }

    return dequeueDog();
}

Dog AnimalShelter::dequeueDog() {
    if(dogs.empty()) {
        throw "Not available";
    }
    Dog dog = dogs.front();
    dogs.pop();
    return dog;
}

Cat AnimalShelter::dequeueCat() {
    if(cats.empty()) {
        throw "Not available";
    }
    Cat cat = cats.front();
    cats.pop();
    return cat;
}

int main()
{
    AnimalShelter animShel;
    std::variant<Cat, Dog> catDog;

    try {
        animShel.enqueue(new Cat());
        animShel.enqueue(new Dog());
        animShel.enqueue(new Dog());
        Cat temps = animShel.dequeueCat();
        catDog = animShel.dequeueAny();
    }
    catch(const char* errorMsg) {
        std::cout << "Error: " << errorMsg << "\n";
    }

}
