#include "provided.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
using namespace std;
#include "provided.h"

int main()
{
	GenomeMatcher gm(3);

	/*Genome g1("g1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC");
	gm.addGenome(g1);
	Genome g2("g2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG");
	gm.addGenome(g2);
	Genome g3("g3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA");
	gm.addGenome(g3);*/
/*
	vector<DNAMatch> vec;
	if (gm.findGenomesWithThisDNA("GAAG", 4, true, vec))
	{
		for (int i = 0; i < vec.size(); i++)
			cout << vec[i].genomeName << " of length " << vec[i].length << " at position " << vec[i].position << endl;
	}
	cout << endl;
	if (gm.findGenomesWithThisDNA("GAATAC", 4, true, vec))
	{
		for (int i = 0; i < vec.size(); i++)
			cout << vec[i].genomeName << " of length " << vec[i].length << " at position " << vec[i].position << endl;
	}
	cout << endl;
	if (gm.findGenomesWithThisDNA("GAATAC", 6, true, vec))
		cout << "Something's not right..." << endl;
	else
		cout << "No matches, correct!" << endl;*/
	cout << endl << endl << endl << "Testing findRelatedGenomes:" << endl;

	Genome g1("g1", "GAT");
	gm.addGenome(g1);
	Genome g3("g3", "GATCATNAT");
	gm.addGenome(g3);
	Genome g2("g2", "GATCAT");
	gm.addGenome(g2);
	Genome query("Query", "CATGATNAT");
	vector<GenomeMatch> results;
	if (gm.findRelatedGenomes(query, 3, true, 30, results))
	{
		for(int i = 0; i < results.size(); i++)
			cout << "Genome " << results[i].genomeName << " with percent match " << results[i].percentMatch << endl;
	}
}
