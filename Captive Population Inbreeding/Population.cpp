#include "Population.h"
#include "Animal.h"
#include "Zoo.h"
#include "Genome.h"
#include "MathsUtils.h"

// Constructors

Population::Population() {
	year = -1;
	zoos = {};
}

Population::Population(int startYear) {
	year = startYear;
	zoos = {};
}

// Destructor

Population::~Population() {	
	if (!zoos.empty()) {
		for (Zoo* zoo : zoos) { // For each zoo in zoos
			if (zoo != nullptr) { // If the pointer exists and still points to a zoo
				delete zoo; // Delete the reference (pointer) to the memory location of this zoo
			}
		}
	}
	zoos.clear(); // Clear up the internal memory within the "zoos" vector

	if (!animals.empty()) {
		for (Animal* animal : animals) {
			if (animal != nullptr) {
				delete animal;
			}
		}
	}
	animals.clear();

	if (genomeBlueprint != nullptr) {
		delete genomeBlueprint;
	}
}

// Getters and setters

vector<Zoo*> Population::getZoos() {
	return zoos;
}

Genome* Population::getGenomeBlueprint() {
	return genomeBlueprint;
}

int Population::getYear() {
	return year;
}

// Methods

void Population::initialisePopulation(int numZoos, int zooCapacity, int numLoci, bool chooseSelectiveMovement, bool chooseAlphaMaleMating) {
	selectiveMovement = chooseSelectiveMovement;
	alphaMaleMating = chooseAlphaMaleMating;

	int overallCapacity = numZoos * zooCapacity;
	
	for (int zooCounter = 1; zooCounter <= numZoos; zooCounter++) {
		Zoo* zoo = new Zoo("Zoo " + std::to_string(zooCounter), zooCapacity); // Create a new object of type Zoo
		zoos.push_back(zoo); // Put the new zoo pointer into the zoos vector
	}
	
	genomeBlueprint = new Genome(); // Create a new Genome blueprint
	genomeBlueprint->defineLoci(numLoci);

	int initialPopulation = overallCapacity * 0.45;

	for (int animalCounter = 0; animalCounter < initialPopulation; animalCounter++) { // For 0 to initialPopulation -1
		Animal* animal = Animal::createAnimal(nullptr,nullptr, this); // Create a new animal (with no parents)
		animal->setSex(MathsUtils::randomInt(1000) < 750 ? 1 : 0); // 75% female (sex = 1)
		animal->setAge(MathsUtils::randomInt(6)); // Random age 0 - 6
		
		bool foundZoo = false; 
		int attemptsRemaining = numZoos * 2; // To prevent endless cycle
		while (!foundZoo) { // While we have not found a suitable zoo
			Zoo* zoo = zoos[MathsUtils::randomInt(zoos.size() - 1)]; // Pick a random zoo for the zoos vector
			if (zoo->availableSpaces() > 0) { // If the zoo has a space
				foundZoo = true;
				animal->setZoo(zoo); // Set the zoo pointer on this animal
				zoo->addAnimal(animal); // Add this animal to the zoo
			}
			attemptsRemaining--; // Reduce the number of attempts remaining by 1
			
			if (!foundZoo && attemptsRemaining < 1) { // If we've not found a suitable zoo and we have no attempts left to find one
				throw std::runtime_error("No zoo found with available space"); // Throw an exception 
				// This is using generic exceptions for now. Needs error handling by caller of this method
			}
		}

		animals.push_back(animal); // Add the new animal to the vector of all animals
		
		for (int zooCounter = 0; zooCounter < numZoos; zooCounter++) { // For each zoo
			zoos[zooCounter]->setPrimaryIndividuals(); // Update primary male/female
		}
	}
}

int Population::overallPopulation()
{
	int livingAnimals = 0;
	if (!animals.empty()) { // If we have any animals
		for (Animal* animal : animals) { // For each animal
			if (animal->isAlive()) { // If the animal is alive
				livingAnimals++; // Increase the count of livingAnimals by 1
			}
		}
	}
	return livingAnimals; // Return the count of living animals
}

int Population::countExistedAnimals()
{
	return animals.size(); // This includes both living and dead animals
}

double Population::overallMeanHeterozygosity()
{
	int livingAnimals = 0;
	double cumulativeHetero = 0.0;
	if (!animals.empty()) {
		for (Animal* animal : animals) {
			if (animal->isAlive()) {
				livingAnimals++;
				cumulativeHetero += animal->heterozygosity(); // Increase the sum of cumulativeHetero by the heterozygosity of this animal
			}
		}
	}
	return cumulativeHetero / livingAnimals; // Return the mean heterozygosity
}

void Population::cycleYear() {

	fixZoosMissingGender(0); // Find any zoos that do not have any males and source a spare
	fixZoosMissingGender(1); // Find any zoos that do not have any females and source a space

	for (Zoo* zoo : zoos) { // For each zoo
		zoo->runBreeding(alphaMaleMating, this); // Run breeding on this zoo, with the chosen mating type
	}

	runDeaths();

	runMovements();

	// Age all alive individuals by one year
	for (Animal* animal : animals) {
		if (animal->isAlive()) {
			animal->setAge(animal->getAge() + 1);
		}
	}
	
	year++;	// increment year
}

void Population::fixZoosMissingGender(int gender) {
	for (Zoo* zoo : zoos) {
		if (zoo->countAnimalsOfSex(gender) == 0) { // If zoo has zero animals of the given gender
			for (Animal* animal : animals) { // loop through all animals in the population
				if (animal->isAlive() == true && animal->getSex() == gender && animal->isPrimary() == false) { // If animal is alive, same gender, and not primary individual
					Zoo* oldZoo = animal->getZoo(); // Get the animal's original zxoo
					oldZoo->removeAnimal(animal); // Remove the animal from the original zoo
					animal->setZoo(zoo);// Set the new zoo pointer on the animal
					zoo->addAnimal(animal); // Add the animal to the zoo
					zoo->setPrimaryIndividuals(); // Update the primary male/female of the new zoo
					break;
				}
			}
		}
	}
}

Zoo* Population::getLowestPopulationZoo(){
	int minZooPopulation = -1;
	Zoo * lowestPopulationZoo = nullptr;
	if (!zoos.empty()){
		for (Zoo* zoo : zoos) { // For each zoo
			int zooPopulation = zoo->population(); // Get the zoo's population
			if (minZooPopulation == -1 || zooPopulation < minZooPopulation) { // If we're checking the first zoo in the list (minZooPopulation will still be -1) OR the next zoo has lower population than our current minimum
				lowestPopulationZoo = zoo; // Set the current zoo to be the lowestPopulationZoo flag
				minZooPopulation = zooPopulation; // Set the population of this zoo to be the minZooPopulation flag
			}
		}
	}
	return lowestPopulationZoo; // Return the zoo with the lowest population (or nullptr if no zoos exist)
}

void Population::runDeaths() {	
	for (Animal* animal : animals) { // For each animal in the population
		if (animal->isAlive()) { // If the animal is alive
			int randomNum = MathsUtils::randomInt(1000); // Generate a random number 0 - 1000
			double modage = (1.7 * animal->getAge()); // Modify the animal's age for a weighted probability of survival
			if ((randomNum / 1000.0) < ((modage + 1) * 0.008)) { // If the random number is less than the modified age * 0.008
				animal->setAlive(false); // Mark the animal as dead
				animal->setPrimary(false); // Remove any primary flag from the animal
				animal->getZoo()->setPrimaryIndividuals(); // Reset the primary male/female on this animal's zoo				
			};
		}
	}	
}

void Population::runMovements() {
	for (int pairCounter = 0; pairCounter < zoos.size() / 2; pairCounter++) { // For 0 to half the number of zoos - 1

		Animal* animalOne;
		Animal* animalTwo;

		bool foundAnimalOne = false;
		int searchesRemaining = animals.size() * 2; //Check at most 2 * the amount of animals we have before giving up
		while (!foundAnimalOne) { // While we have not found a suitable animal
			animalOne = animals[MathsUtils::randomInt(animals.size() - 1)]; // Pick a random animal from the vector of all animals
			searchesRemaining--; // Reduce the number of searches remaining by 1

			if (animalOne->isAlive()) { // If this animal is alive
				foundAnimalOne = true;
			} else if (searchesRemaining == 0) { // If we've run out of searches to find a suitable animal
				throw std::runtime_error("No alive animal found to move"); // Throw an exception and stop executing
			}
		}
		
		bool foundAnimalTwo = false;
		searchesRemaining = animals.size() * 2; //Check at most 2 * the amount of animals we have before giving up
		while (!foundAnimalTwo) { // While we have not found a suitable second animal
			animalTwo = animals[MathsUtils::randomInt(animals.size() - 1)]; // Pick a random animal from the vector of all animals
			searchesRemaining--; // Reduce the number of searches remaining by 1

			bool aliveAndDifferentZoo = animalTwo->isAlive() && animalTwo->getZoo()->getName().compare(animalOne->getZoo()->getName()) != 0; // If the animal is alive, and not in the same zoo

			if (!selectiveMovement && aliveAndDifferentZoo) {// If random movement is selected, and alive/different zoo
				foundAnimalTwo = true;
			} else if (selectiveMovement && aliveAndDifferentZoo && animalTwo->getSex() == animalOne->getSex() && animalTwo->getAge() <= animalOne->getAge() + 3 && animalTwo->getAge() >= animalOne->getAge() - 3) { // If selective movement is selected, and alive/different zoo and age is +-3 years
				foundAnimalTwo = true;
			}
			else if (searchesRemaining == 0) {
				throw std::runtime_error("No alive animal from a different zoo found"); // Throw and exception and stop executing
			}
		}
		
		animalOne->setPrimary(false); // Remove primary flag from the animal
		animalTwo->setPrimary(false);

		Zoo* animalZooOne = animalOne->getZoo(); // Get animal one's original zoo
		animalOne->setZoo(animalTwo->getZoo()); // Set animal one's zoo to be animal two's zoo
		animalTwo->setZoo(animalZooOne); // Set animal two's zoo to be animal one's zoo

		animalOne->getZoo()->addAnimal(animalOne); // Add animal one to it's new zoo
		animalTwo->getZoo()->addAnimal(animalTwo);
		animalOne->getZoo()->removeAnimal(animalTwo); // Remove animal two from animal one's zoo
		animalTwo->getZoo()->removeAnimal(animalOne);

		animalOne->getZoo()->setPrimaryIndividuals(); // Update primary male/female on animal one's zoo
		animalTwo->getZoo()->setPrimaryIndividuals();

	};
}

void Population::addAnimal(Animal* incomingAnimal) {
	animals.push_back(incomingAnimal); // Add an animal to the vector of all animals
}