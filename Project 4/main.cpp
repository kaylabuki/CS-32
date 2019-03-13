#include "provided.h"
#include <iostream>
using namespace std;

int main()
{
	Genome genome1("Genome 1", "CGGGAAGANT");
	Genome genome2("Genome 2", "TAACAGAGAAT");
	Genome genome3("Genome 3", "GAAGGAAGAAGAA");

	GenomeMatcher matcher(3);
	matcher.addGenome(genome1);
	matcher.addGenome(genome2);
	matcher.addGenome(genome3);

	std::vector<DNAMatch> matches;
	bool result;

	cout << "Should print: " << endl;
	cout << "Genome 1 of length 5 at position 3" << endl;
	cout << "Genome 2 of length 3 at position 7" << endl;
	cout << "Genome 3 of length 5 at position 4" << endl;
	result = matcher.findGenomesWithThisDNA("GAAGATA", 3, true, matches);
	for (int i = 0; i < matches.size(); i++)
		cout << matches[i].genomeName << " of length " << matches[i].length << " at position " << matches[i].position << endl;

	cout << endl;

	/*cout << "Should print: " << endl << "Genome 1 of length 5 at position 22\nGenome 2 of length 5 at position 48\n";
	result = matcher.findGenomesWithThisDNA("GAATAC", 4, true, matches);
	for (int i = 0; i < matches.size(); i++)
		cout << matches[i].genomeName << " of length " << matches[i].length << " at position " << matches[i].position << endl;

	cout << "Should print: " << endl << "False!" << endl;
	result = matcher.findGenomesWithThisDNA("GAATAC", 6, true, matches);
	if (!result)
		cout << "False!";
	else
		cout << "True!";*/

}
