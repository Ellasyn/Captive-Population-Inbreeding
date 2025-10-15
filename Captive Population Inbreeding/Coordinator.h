#include <vcclr.h>
#include <vector>
#include <string>
#include "OptionsWindow.h"

class Population;
using std::vector;
using std::string;

class Coordinator {
private:
	gcroot<OptionsWindow^> window;
	Population* population = nullptr;

public:
	// Constructors
	Coordinator();
	
	// Destructor
	~Coordinator();

	// Methods
	void setOptionsWindow(OptionsWindow^ optionsWindow);
	void initialisePopulation(int startYear, int numZoos, int zooCapcity, int numLoci, bool selectiveMovement, bool alphaMaleMating);
	void cycleYear(int numYears);
	void updateDisplay();

};