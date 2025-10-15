
class GenePair{

private:
	int geneOne;
	int geneTwo;

public:
	// Constructors
	GenePair();

	// Destructor
	~GenePair();

	// Getters and setters
	int getGeneOne();
	void setGeneOne(int gene);
	int getGeneTwo();
	void setGeneTwo(int gene);

	// Methods
	bool locusHeterozygosity();
	int getRandomGene();
};