#include "Coordinator.h"
#include "Population.h"
#include "Zoo.h"

// Constructors

Coordinator::Coordinator(){

}

// Destructor

Coordinator::~Coordinator(){
	if (population != nullptr) {
		delete population;
	}
}

// Methods

void Coordinator::setOptionsWindow(OptionsWindow^ optionsWindow){
	window = optionsWindow;
}

void Coordinator::initialisePopulation(int startYear, int numZoos, int zooCapacity, int numLoci, bool selectiveMovement, bool alphaMaleMating) {
	if (population != nullptr) { // If reinitialising, remove existing population
		delete population;	
		population = nullptr;
	}
	
	population = new Population(startYear); // Create a new population
	population->initialisePopulation(numZoos, zooCapacity, numLoci, selectiveMovement, alphaMaleMating);
	window->addOutputResultLine("Intialised successfully");
	updateDisplay(); // Output current state
}

void Coordinator::cycleYear(int numYears) {
	// To do: validation of numYears
	for (int yearCounter = 0; yearCounter < numYears; yearCounter++) { // For each year we want to cycle through
		population->cycleYear();
		updateDisplay();
	}
}

void Coordinator::updateDisplay() {
	vector<string> textLines = {};
	
	textLines.push_back("Year : " + std::to_string(population->getYear()));
	textLines.push_back("Total pop : " + std::to_string(population->overallPopulation()));
	vector<Zoo*> zoos = population->getZoos();
	if (!zoos.empty()) { // If zoos is not empty
		for (Zoo* zoo : zoos) { // For each zoo in the zoos vector
			textLines.push_back(zoo->getName() + " pop " + std::to_string(zoo->population()));
		}
	}
	textLines.push_back("Overall heterozygosity " + std::to_string(population->overallMeanHeterozygosity()));

	window->addOutputResult(textLines); // Update text display on the main window
}
