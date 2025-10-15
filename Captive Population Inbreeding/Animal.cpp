#include "Animal.h"
#include "Zoo.h" 
#include "Genome.h"
#include "Genotype.h"
#include "Population.h"
#include "MathsUtils.h"

// Constructors

Animal::Animal(int animalId) {
	id = animalId;
	alive = true;
	age = 0;
	primary = false;
}

Animal::Animal(int animalId, Zoo* allocatedZoo) {
	id = animalId;
	alive = true;
	age = 0;
	primary = false;
	zoo = allocatedZoo;
}

// Destructor

Animal::~Animal() {
	if (genotype != nullptr) {
		delete genotype;
	}
	if (mother != nullptr) {
		delete mother;
	}
	if (father != nullptr) {
		delete father;
	}
}

// Getters and setters

int Animal::getId()
{
	return id;
}

Zoo* Animal::getZoo(){
	return zoo;
}

void Animal::setZoo(Zoo* nextZoo) {
	zoo = nextZoo;
}

int Animal::getSex()
{
	return sex;
}

void Animal::setSex(int givenSex)
{
	sex = givenSex;
}

int Animal::getAge()
{
	return age;
}

void Animal::setAge(int givenAge)
{
	age = givenAge;
}

bool Animal::isAlive()
{
	return alive;
}

void Animal::setAlive(bool isAlive)
{
	alive = isAlive;
}

bool Animal::isPrimary()
{
	return primary;
}

void Animal::setPrimary(bool assignedPrimary)
{
	primary = assignedPrimary;
}

Animal* Animal::getMother()
{
	return mother;
}

void Animal::setMother(Animal* assignedMother)
{
	mother = assignedMother;
}

Animal* Animal::getFather()
{
	return father;
}

void Animal::setFather(Animal* assignedFather)
{
	father = assignedFather;
}

Genotype* Animal::getGenotype()
{
	return genotype;
}

// Methods

double Animal::heterozygosity()
{
	return genotype->totalHeterozygosity();
}

void Animal::allocateGenes(Genome* genomeBlueprint) {
	genotype = new Genotype(); // Create a new Genotype
	genotype->allocateGenes(genomeBlueprint);
}

void Animal::inheritGenes() {
	vector<GenePair*> mothersGenes = mother->getGenotype()->getGenes();
	vector<GenePair*> fathersGenes = father->getGenotype()->getGenes();

	genotype = new Genotype();
	genotype->inheritGenes(mothersGenes, fathersGenes);
}

Animal* Animal::createAnimal(Animal* mother, Animal* father, Population* population) {
	Animal* animal = new Animal(population->countExistedAnimals() + 1); // Create new animal, with an ID

	animal->setMother(mother);
	animal->setFather(father);
	if (mother == nullptr || father == nullptr) { // If this animal doesn't have a mother OR doesn't have a father
		animal->allocateGenes(population->getGenomeBlueprint()); // Allocate genes based on default genome blueprint
	} else { // If animal has a mother AND has a father
		animal->inheritGenes(); // Inherit genes from mother and father
	}

	return animal; // Return the new animal (pointer)
}