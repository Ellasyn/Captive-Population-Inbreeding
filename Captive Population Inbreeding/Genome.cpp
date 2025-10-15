#include "Genome.h"
#include "MathsUtils.h"

// Constructors 

Genome::Genome() {	

}

// Destructor
Genome::~Genome() {
	loci.clear();
}

// Getters and setters

vector<int> Genome::getLoci() {
	return loci;
}

// Methods 

void Genome::defineLoci(int countLoci) {
	for (int lociCounter = 0; lociCounter < countLoci; lociCounter++) { // For 0 to countLoci - 1
		loci.push_back(MathsUtils::randomInt(4) + 2); // Generate a random number between 2 and 6
	}
}
