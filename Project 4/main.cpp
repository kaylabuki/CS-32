#include "provided.h"
#include <iostream>
using namespace std;

int main()
{
	Genome genome1("Genome 1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC");
	Genome genome2("Genome 2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG");
	Genome genome3("Genome 3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA");

	GenomeMatcher matcher(4);
	matcher.addGenome(genome1);
	matcher.addGenome(genome2);
	matcher.addGenome(genome3);

	std::vector<DNAMatch> matches;
	bool result;

	cout << "Should print: " << endl << "Genome 1 of length 4 at position 60\nGenome 2 of length 4 at position 54\nGenome 3 of length 4 at position 29\n";
	result = matcher.findGenomesWithThisDNA("GAAG", 4, true, matches);
	for (int i = 0; i < matches.size(); i++)
		cout << matches[i].genomeName << " of length " << matches[i].length << " at position " << matches[i].position << endl;

	cout << endl;

	cout << "Should print: " << endl << "Genome 1 of length 5 at position 22\nGenome 2 of length 5 at position 48\n";
	result = matcher.findGenomesWithThisDNA("GAATAC", 4, true, matches);
	for (int i = 0; i < matches.size(); i++)
		cout << matches[i].genomeName << " of length " << matches[i].length << " at position " << matches[i].position << endl;

	cout << "Should print: " << endl << "False!" << endl;
	result = matcher.findGenomesWithThisDNA("GAATAC", 6, true, matches);
	if (!result)
		cout << "False!";
	else
		cout << "True!";

}
