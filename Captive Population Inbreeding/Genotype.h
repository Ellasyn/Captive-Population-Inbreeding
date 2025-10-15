#include <vector>

using std::vector;
class Genome;
class GenePair;

class Genotype {

private:
	vector<GenePair*> genes;
	double heterozygosity;

public:
	// Constructors
	Genotype();

	// Destructor
	~Genotype();

	// Getters and setters
	vector<GenePair*> getGenes();
	double getHeterozygosity();

	// Methods
	void allocateGenes(Genome* genomeBlueprint);	
	void inheritGenes(vector<GenePair*> mothersGenes, vector<GenePair*> fathersGenes);
	double totalHeterozygosity();
};