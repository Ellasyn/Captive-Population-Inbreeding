#include <vector>

using std::vector;

class Genome {

private:
	vector<int> loci;

public:
	// Constructors
	Genome();

	// Destructor
	~Genome();

	// Getters and setters
	vector<int> getLoci();

	// Methods
	void defineLoci(int countLoci);
};