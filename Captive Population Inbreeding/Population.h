#include <vector>

using std::vector; 
class Zoo;
class Animal;
class Genome;

class Population {

private:
	int year;
	vector<Zoo*> zoos;
	vector<Animal*> animals; // Full list of all animals (needed so we don't have the bias of going zoo by zoo)
	Genome* genomeBlueprint;
	bool selectiveMovement;
	bool alphaMaleMating;

public:
	// Constructors
	Population();
	Population(int startYear);

	// Destructor
	~Population();

	// Getter and setters
	vector<Zoo*> getZoos();
	Genome* getGenomeBlueprint();
	int getYear();

	// Methods
	void initialisePopulation(int numZoos, int zooCapacity, int numLoci, bool chooseSelectiveMovement, bool chooseAlphaMaleMating);
	int overallPopulation();
	int countExistedAnimals(); // Count all animals alive or dead that have ever existed
	double overallMeanHeterozygosity();
	void cycleYear();
	void fixZoosMissingGender(int gender);	
	Zoo* getLowestPopulationZoo();
	void runDeaths();
	void runMovements();
	void addAnimal(Animal* incomingAnimal);
};

