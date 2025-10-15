#include "Animal.h"
#include "Population.h"
#include "Zoo.h"
#include "MathsUtils.h"

class Animal;

// Constructors

Zoo::Zoo(string zooName, int zooCapacity) {
	name = zooName;
	capacity = zooCapacity;
}

// Destructor

Zoo::~Zoo() {
	if (!animals.empty()) {
		animals.clear();
	}
}

// Getters and setters

string Zoo::getName() {
	return name;
}

// Methods 

void Zoo::addAnimal(Animal* incomingAnimal) {
	animals.push_back(incomingAnimal); // Add the incoming animal to this zoo's animal vector
}

void Zoo::removeAnimal(Animal* outgoingAnimal) {
	int outgoingAnimalPosition = -1;
	for (int counter = 0; counter < animals.size(); counter++) { // For 0  to number of animals in this zoo - 1
		Animal* animal = animals[counter]; // Get the animal at this position number
		if (animal->getId() == outgoingAnimal->getId()) { // If this animal's ID matches the ID we're looking for
			outgoingAnimalPosition = counter; // keep a note of the position of the animal we are looking for
			break;
		}
	}
	animals.erase(animals.begin() + outgoingAnimalPosition); // Get the first animal, move to the poition of the animal we want to remove, then erase it from the vector of animals in this zoo
}

// Todo: this should account for animals less than one year old and during movements
void Zoo::setPrimaryIndividuals()
{
	ZooAnimalGenders* genders = getMalesAndFemales(); // Split the zoo's population into a vector of males and a vector of females
	vector<Animal*> males = genders->getMales();
	vector<Animal*> females = genders->getFemales();

	if (!males.empty()){ // If we have any males in this zoo
		bool hasPrimaryMale = false;
		for (Animal* animal : males) { // For each male animal
			if (animal->isAlive() && animal->isPrimary()) { // If the male is alive and is the primary
				hasPrimaryMale = true; // Flag that this zoo already has a primary male
				break;
			}
		}
	
		if (!hasPrimaryMale) { // If this zoo doesn't already have a primary male
			Animal* selectedMale = nullptr;
			for (int counter = 0; counter < males.size(); counter++) { // For 0 to number of males - 1
				if (males[counter]->isAlive()) { // If the male is alive
					selectedMale = males[counter]; // Set this male to selectedMale
					break;
				}
			}
			if (selectedMale != nullptr) { // If we've found a male to make primary
				selectedMale->setPrimary(true); // Make the male the primary for this zoo
			}
		}
	}

	if (!females.empty()) {
		bool hasPrimaryFemale = false;
		for (Animal* animal : females) {
			if (animal->isAlive() && animal->isPrimary()) {
				hasPrimaryFemale = true;
				break;
			}
		}
		if (!hasPrimaryFemale) {
			Animal* selectedFemale = nullptr;
			for (int counter = 0; counter < females.size(); counter++) {
				if (females[counter]->isAlive()) {
					selectedFemale = females[counter];
					break;
				}
			}
			if (selectedFemale != nullptr) {
				selectedFemale->setPrimary(true);
			}
		}
	}
}

int Zoo::population() {
	int aliveAnimals = 0;
	if (!animals.empty()) { // If there are animals in this zoo
		for (Animal* animal : animals) { // For each animal
			if (animal->isAlive()) { // If the animal is alive
				aliveAnimals++; // Increase the count of alive animals by one
			}
		}
	}
	return aliveAnimals; // Return the count of living animals
}

int Zoo::availableSpaces()
{
	return capacity - population(); // Capcity minus number of animals in this zoo
}

int Zoo::countMales()
{
	return countAnimalsOfSex(0);
}

int Zoo::countFemales()
{
	return countAnimalsOfSex(1);
}

int Zoo::countAnimalsOfSex(int sex) {
	int individuals = 0;
	for (Animal* animal : animals) { // For each animal
		if (animal->isAlive() && animal->getSex() == sex) { // If this animal is alive and of the chosen sex
			individuals++; // Increase the count of individuals of the chosen sex by one
		}
	}
	return individuals;
}

Zoo::ZooAnimalGenders* Zoo::getMalesAndFemales() {
	vector<Animal*> males;
	vector<Animal*> females;
	for (Animal* animal : animals) {
		if(animal->isAlive()){
			if (animal->getSex() == 0) { // If the animal is male
				males.push_back(animal);
			} else {
				females.push_back(animal);
			}
		}
	}

	ZooAnimalGenders* genders = new ZooAnimalGenders(); 
	genders->setMales(males);
	genders->setFemales(females);

	return genders;
}

void Zoo::runBreeding(bool alphaMaleMating, Population * population)
{
	ZooAnimalGenders* genders = getMalesAndFemales(); // Split the animals in this zoo into a vector of males and a vector of females
	vector<Animal*> males = genders->getMales();
	vector<Animal*> females = genders->getFemales();

	Animal* alphaMale; // If doing alpha male mating, find the primary male once so we don't have to keep looking through the males for him
	if (alphaMaleMating == true) { // If alpha male mating is selected
		for (Animal* male : males) { // For each male
			if (male->isPrimary()) { // If the male is the primary
				alphaMale = male; // Set this male to alphaMale
				break; 
			}
		}

		if (alphaMale == nullptr) {
			throw std::runtime_error("No alpha male found"); // Throw an exception and stop executing
		}
	}

	for (Animal* female : females) { // For each female in the zoo
		if (female->getAge() > 0){ // If the female is at least one year old
			Animal* selectedMale;

			if (alphaMaleMating == true) { // If alpha male mating is selected, use the alpha male
				selectedMale = alphaMale;
			} else { // If random mating is selected
				bool foundMale = false;
				int searchesRemaining = males.size() * 2; // Search for at maximum twice the number of times for the amount of males in this zoo
				while (!foundMale) { // While we have not found a suitable male
					if (males.size() == 0) { // If there are no males in this zoo, stop looking
						selectedMale = nullptr;
						foundMale = true;
					} else{ // If there are males in this zoo
						selectedMale = males[MathsUtils::randomInt(males.size() - 1)]; // Choose a random male
						searchesRemaining--; // Reduce the number of searches remaining by one

						if (selectedMale->getAge() > 0) { // If this male is at least one year old
							foundMale = true;
						} else if (searchesRemaining == 0) { // If we have run out of searches, stop looking
							selectedMale = nullptr;
							foundMale = true;
						}
					}
				}
			}
			if (selectedMale != nullptr) { // If we have a suitable male
				breedPair(selectedMale, female, population); // Breed the selected male with this female
			}
		}
	}
}

void Zoo::breedPair(Animal* male, Animal* female, Population* population) {
	int litterSize = generateLitterSize(male, female); // Generate a litter size	

	for (int offspring = 0; offspring < litterSize; offspring++) { // For 0 to litterSize - 1
		Animal* animal = Animal::createAnimal(male, female, population); // Create a new animal from the mother and father
		if (this->availableSpaces() > 0) { // If this zoo can accomodate the new animal
			animal->setZoo(this); // Set the animal's zoo pointer to this zoo
			this->addAnimal(animal); // Add the animal to this zoo
		} else { // If there are no spaces left in this zoo
			Zoo* lowestPopulationZoo = population->getLowestPopulationZoo(); // Find the zoo with the lowest population
			if (lowestPopulationZoo != nullptr && lowestPopulationZoo->availableSpaces() > 0) { // If there is a lowest population zoo and it has available spaces
				animal->setZoo(lowestPopulationZoo); // Set the animal's zoo pointer to the lowest population zoo
				lowestPopulationZoo->addAnimal(animal);
				lowestPopulationZoo->setPrimaryIndividuals(); // Update the primary male/female on the lowest population zoo
			} else {
				throw std::runtime_error("No zoo found with available space");
			}
		}
		animal->setSex(MathsUtils::randomInt(1000) < 500 ? 1 : 0); // 50% chance male/female
		animal->setAge(0);
		population->addAnimal(animal); // Add the animal to the vector of all animals
	}
}

int Zoo::generateLitterSize(Animal* male, Animal* female) {
	double meanHetero = (male->heterozygosity() + female->heterozygosity()) / 2.0; // Calculate the mean heterozygosity between the parents
	int adjustedMeanLitterSize = int(meanLitterSize * 2 * (meanHetero)); // calculate an adjusted mean litter size for these parents
	if (adjustedMeanLitterSize == 0) { 
		adjustedMeanLitterSize = meanLitterSize; 
	};

	int litterSize = -1;
	double u;
	do {
		litterSize++;
		u = MathsUtils::randomInt(1000) / 1000.0;
	} while (u < MathsUtils::poisson(litterSize, adjustedMeanLitterSize)); // Generate a litter size based on a poisson distribution probability with a mean of adjustedMeanLitterSize

	return litterSize;
}

// Private inner/sub class ZooAnimalGenders

// Constructors

Zoo::ZooAnimalGenders::ZooAnimalGenders(){

}

// Destructor

Zoo::ZooAnimalGenders::~ZooAnimalGenders() {
	if (!males.empty()) {
		for (Animal* male : males) {
			if (male != nullptr) {
				delete male;
			}
		}
	}
	males.clear();

	if (!females.empty()) {
		for (Animal* female : females) {
			if (female != nullptr) {
				delete female;
			}
		}
	}
	females.clear();
}

// Getters and setters 

vector<Animal*> Zoo::ZooAnimalGenders::getMales() {
	return males;
}

void Zoo::ZooAnimalGenders::setMales(vector<Animal*> individuals) {
	males = individuals;
}

vector<Animal*> Zoo::ZooAnimalGenders::getFemales() {
	return females;
}

void Zoo::ZooAnimalGenders::setFemales(vector<Animal*> individuals) {
	females = individuals;
}

