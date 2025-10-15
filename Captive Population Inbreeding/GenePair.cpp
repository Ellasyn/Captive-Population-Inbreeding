#include "GenePair.h"
#include "MathsUtils.h"

// Constructors

GenePair::GenePair() {

}

// Destructor

GenePair::~GenePair() {

}

// Getters and setters

int GenePair::getGeneOne() {
	return geneOne;
}

void GenePair::setGeneOne(int gene) {
	geneOne = gene;
}

int GenePair::getGeneTwo() {
	return geneTwo;
}

void GenePair::setGeneTwo(int gene) {
	geneTwo = gene;
}

// Methods

bool GenePair::locusHeterozygosity()
{
	return geneOne != geneTwo; // Return boolean true if gene one is not equal to gene two
}

int GenePair::getRandomGene()
{
	return MathsUtils::randomInt(1000) % 2 == 0 ? geneOne : geneTwo; // Generate a random number, if it's even return gene one, else return gene two
}
