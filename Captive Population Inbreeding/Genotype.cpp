#include "Genotype.h"
#include "Genome.h"
#include "GenePair.h"
#include "MathsUtils.h"

// Constructors

Genotype::Genotype(){
}

//Destructor

Genotype::~Genotype() {	
	if (!genes.empty()) {
		for (GenePair* genePair : genes) {
			delete genePair;
		}
	}

	genes.clear();	
}

// Getters and setters

vector<GenePair*> Genotype::getGenes(){
	return genes;
}

double Genotype::getHeterozygosity(){
	return heterozygosity;
}

// Methods

void Genotype::allocateGenes(Genome* genomeBlueprint){
	vector<int> loci = genomeBlueprint->getLoci();

	int countHeterozygosity = 0;
	for (int locusCounter = 0; locusCounter < loci.size(); locusCounter++) { // For 0 to the number of loci - 1
		int locus = loci[locusCounter]; // Get the locus at this position in the vector of loci
		GenePair* genePair = new GenePair(); // Create a new GenePair
		genePair->setGeneOne(MathsUtils::randomInt(locus)); // Assign a random gene at this locus
		genePair->setGeneTwo(MathsUtils::randomInt(locus));
		genes.push_back(genePair); // Add the new gene pair to the vector of genes

		if (genePair->locusHeterozygosity()) { // Calculate the heterozygosity of the gene pair
			countHeterozygosity++;
		}
	}

	heterozygosity = (double) countHeterozygosity / loci.size(); // Cast one of the terms to a double to prevent integer rounding
}

void Genotype::inheritGenes(vector<GenePair*> mothersGenes, vector<GenePair*> fathersGenes)
{
	int countHeterozygosity = 0;
	for (int locusCounter = 0; locusCounter < mothersGenes.size(); locusCounter++) { // For 0 to the number of loci in the mother's genes - 1
		GenePair* mothersGenePair = mothersGenes[locusCounter]; // Get the mothers gene pair at that locus
		GenePair* fathersGenePair = fathersGenes[locusCounter];
		
		GenePair* genePair = new GenePair(); // Create a new gene pair
		genePair->setGeneOne(mothersGenePair->getRandomGene()); // Set gene one to be a random gene from the mother
		genePair->setGeneTwo(fathersGenePair->getRandomGene());
		genes.push_back(genePair); // Add the new gene pair to the vector of genes

		if (genePair->locusHeterozygosity()) { // Calculate the heterozygosity of the gene pair
			countHeterozygosity++;
		}
	}

	heterozygosity = (double) countHeterozygosity / mothersGenes.size(); // Cast one of the terms to a double to prevent integer rounding
}

double Genotype::totalHeterozygosity() {
	double totalHetero = 0.0;
	if (!genes.empty()) { // If there are genes
		for (GenePair* genePair : genes) { // For each gene pair
			if (genePair->locusHeterozygosity()) { // If heterozygous at this locus
				totalHetero++; // Increase the total hetero count by one
			}
		}
	}
	return totalHetero / genes.size(); // Calculate and return the total heterozygosity
}
