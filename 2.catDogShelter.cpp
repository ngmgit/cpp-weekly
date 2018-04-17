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
#include <optional>
#include <utility>

enum class AnimalTypes { CAT, DOG };

class Animal {
 public:
    Animal();
    void print();
};
void Animal::print() {
    std::cout << "Animal\n";
}


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
    void enqueue(Cat cat);
    void enqueue(Dog dog);
    std::optional< std::variant<Cat, Dog> > dequeueAny();
    std::optional<Cat> dequeueCat();
    std::optional<Dog> dequeueDog();
    bool empty();

private:
    static unsigned int timeStamp;
    std::queue<std::pair<int, Cat>> cats;
    std::queue<std::pair<int, Dog>> dogs;
};
unsigned int AnimalShelter::timeStamp = 0;

void AnimalShelter::enqueue(Cat cat) {
    cats.push(std::make_pair(timeStamp++, cat));
}

void AnimalShelter::enqueue(Dog dog) {
    dogs.push(std::make_pair(timeStamp++, dog));
}

std::optional< std::variant<Cat, Dog> > AnimalShelter::dequeueAny() {
    if (cats.empty()) {
        return dequeueDog();
    }

    if (dogs.empty()) {
        return dequeueCat();
    }

    std::pair<unsigned int, Cat> oldestCat = cats.front();
    std::pair<unsigned int, Dog> oldestDog = dogs.front();

    if(std::get<0>(oldestCat) > std::get<0>(oldestDog)) {
        return dequeueCat();
    }

    return dequeueDog();
}

std::optional<Dog> AnimalShelter::dequeueDog() {
    if(dogs.empty()) {
        return {};
    }
    std::pair<unsigned int, Dog> dog = dogs.front();
    dogs.pop();
    return std::get<1>(dog);
}

std::optional<Cat> AnimalShelter::dequeueCat() {
    if(cats.empty()) {
        return {};
    }
    std::pair<unsigned int, Cat> cat = cats.front();
    cats.pop();
    return std::get<1>(cat);
}

bool AnimalShelter::empty() {
    return cats.empty() && dogs.empty();
}

int main()
{
    AnimalShelter animShel;


    try {
        animShel.enqueue(Cat{});
        animShel.enqueue(Dog{});
        animShel.enqueue(Dog{});
        std::optional<Cat> cat1 = animShel.dequeueCat();

        animShel.enqueue(Cat{});

        std::optional< std::variant<Cat, Dog> > catDog = animShel.dequeueAny();
        std::optional<Cat> cat2 = animShel.dequeueCat();
        std::optional<Dog> dog2 = animShel.dequeueDog();
    }
    catch(const char* errorMsg) {
        std::cout << "Error: " << errorMsg << "\n";
    }

}
