#include <vector>
#include <string>

class Animal;
class Population;
using std::vector;
using std::string;

class Zoo {

private:
	string name;
	vector<Animal*> animals;
	int capacity;
	const int meanLitterSize = 2; // In future, this should be adjustable via the form

	// Private inner/sub class
	class ZooAnimalGenders {

	private:
		vector<Animal*> males;
		vector<Animal*> females;

	public:
		// Constructors
		ZooAnimalGenders();

		// Destructor
		~ZooAnimalGenders();

		// Getters and setters
		vector<Animal*> getMales();
		void setMales(vector<Animal*> individuals);
		vector<Animal*> getFemales();		
		void setFemales(vector<Animal*> individuals);
	};

public:
	// Constructors
	Zoo(string zooName, int capacity);

	// Destructor
	~Zoo();

	// Getters and Setters
	string getName();
	
	// Methods
	void addAnimal(Animal* incomingAnimal);
	void removeAnimal(Animal* outgoingAnimal);
	void setPrimaryIndividuals();
	int population();
	int availableSpaces();
	int countMales();
	int countFemales();
	int countAnimalsOfSex(int sex);
	ZooAnimalGenders* getMalesAndFemales();
	void runBreeding(bool alphaMaleMating, Population* population);

private: // Private methods
	void Zoo::breedPair(Animal* male, Animal* female, Population* population);
	int Zoo::generateLitterSize(Animal* male, Animal* female);
};
