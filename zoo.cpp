#include <iostream>
#include <vector>
#include <string>

class Animal {
public:
    Animal(const std::string& name, const std::string& species, int cost) : name(name), species(species), cost(cost), hunger(0) {}

    void feed() {
        hunger = 0;
    }

    const std::string& getName() const {
        return name;
    }

    const std::string& getSpecies() const {
        return species;
    }

    int getCost() const {
        return cost;
    }

private:
    std::string name;
    std::string species;
    int cost;
    int hunger;
};

class Lion : public Animal {
public:
    Lion(const std::string& name) : Animal(name, "Lion", 300) {}
};

class Tiger : public Animal {
public:
    Tiger(const std::string& name) : Animal(name, "Tiger", 200) {}
};

class Elephant : public Animal {
public:
    Elephant(const std::string& name) : Animal(name, "Elephant", 500) {}
};

class Zoo {
    Zoo() {
    // Add animals to the catalog
    catalog.push_back(new Lion("Lion_1", 1200));
    catalog.push_back(new Tiger("Tiger_1", 1500));
    catalog.push_back(new Bear("Bear_1", 1000));
}

public:
    void addAnimal(Animal* animal) {
        animals.push_back(animal);
    }

    void removeAnimal(const std::string& name) {
        for (size_t i = 0; i < animals.size(); ++i) {
            if (animals[i]->getName() == name) {
                delete animals[i];
                animals.erase(animals.begin() + i);
                break;
            }
        }
    }

    Animal* findAnimal(const std::string& name) {
        for (Animal* animal : animals) {
            if (animal->getName() == name) {
                return animal;
            }
        }
        return nullptr;
    }
    
    void listCatalog() {
    std::cout << "Animals available for purchase:\n";
    for (const auto& animal : catalog) {
        std::cout << animal->getName() << " the " << animal->getSpecies() << " (Cost: $" << animal->getCost() << ")\n";
    }
}

    void listAnimals() {
        if (animals.empty()) {
            std::cout << "There are no animals in your zoo.\n";
        } else {
            std::cout << "Animals in your zoo:\n";
            for (const Animal* animal : animals) {
                std::cout << animal->getName() << " the " << animal->getSpecies() << '\n';
            }
        }
    }

private:
    std::vector<Animal*> animals;
    std::vector<Animal*> catalog;
};


class Player {
public:
    Player() : money(1000) {}

    void feedAnimal(Animal* animal) {
        if (animal) {
            animal->feed();
            std::cout << "You fed " << animal->getName() << " the " << animal->getSpecies() << ".\n";
        } else {
            std::cout << "Animal not found in your zoo.\n";
        }
    }

void buyAnimal(Zoo& zoo, Animal* animal) {
    if (animal == nullptr) {
        std::cout << "Animal not found in the catalog.\n";
    } else if (!canAfford(*animal)) {
        std::cout << "You don't have enough money to buy this animal.\n";
    } else {
        money -= animal->getCost();
        zoo.addAnimal(animal);
        std::cout << "You bought " << animal->getName() << " the " << animal->getSpecies() << ".\n";
    }
}

    void sellAnimal(Zoo& zoo, const std::string& name) {
        Animal* animal = zoo.findAnimal(name);
        if (animal) {
            money += animal->getCost() / 2;
            zoo.removeAnimal(name);
            std::cout << "You sold " << animal->getName() << " the " << animal->getSpecies() << ".\n";
        } else {
            std::cout << "Animal not found in your zoo.\n";
        }
    }

    int getMoney() const {
        return money;
    }

    bool canAfford(const Animal& animal) const {
        return money >= animal.getCost();
    }

private:
    int money;
};

// Function implementations
void showMenu() {
    std::cout << "1. List animals\n";
    std::cout << "2. Feed an animal\n";
    std::cout << "3. Buy an animal\n";
    std::cout << "4. Sell an animal\n";
    std::cout << "5. Exit\n";
}

void playGame(Zoo& zoo, Player& player) {
    int choice;
    std::string animalName;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                zoo.listAnimals();
                break;
            case 2:
                std::cout << "Enter the name of the animal you want to feed: ";
                std::cin.ignore();
                std::getline(std::cin, animalName);
                player.feedAnimal(zoo.findAnimal(animalName));
                break;
            case 3:
                zoo.listCatalog();
                std::cout << "Enter the name of the animal you want to buy: ";
                std::cin.ignore();
                std::getline(std::cin, animalName);
                player.buyAnimal(zoo, zoo.findAnimal(animalName));
                break;
            case 4:
                std::cout << "Enter the name of the animal you want to sell: ";
                std::cin.ignore();
                std::getline(std::cin, animalName);
                player.sellAnimal(zoo, animalName);
                break;
            case 5:
                std::cout << "Thanks for playing! Goodbye.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

int main() {
    Zoo zoo;
    Player player;
    playGame(zoo, player);
    return 0;
}
