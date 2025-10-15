class Zoo;
class Genotype;
class Genome;
class Population;

class Animal {
private: 
	int id;
	Zoo* zoo; // Memory reference (pointer) to a "Zoo" object
	bool alive;
	int sex; //  0 = Male, 1 = Female
	int age;
	Genotype* genotype;
	bool primary;
	Animal* mother;
	Animal* father;

public:
	// Constructors
	Animal(int animalId);
	Animal(int animalId, Zoo* zoo);

	// Destructor
	~Animal();

	// Getter and setters
	int getId();	
	Zoo* getZoo();
	void setZoo(Zoo* nextZoo);
	int getSex();
	void setSex(int givenSex);
	int getAge();
	void setAge(int givenAge);
	bool isAlive();	
	void setAlive(bool isAlive);
	bool isPrimary();
	void setPrimary(bool assignedPrimary);
	Animal* getMother();
	void setMother(Animal* assignedMother);
	Animal* getFather();
	void setFather(Animal* assignedFather);
	Genotype* getGenotype();

	// Methods	
	double heterozygosity();
	void allocateGenes(Genome* genomeBlueprint);
	void inheritGenes();

	//Static methods
	static Animal* createAnimal(Animal* mother, Animal* Father, Population* population); // static method because it is not specific to a particular Animal we've created
};