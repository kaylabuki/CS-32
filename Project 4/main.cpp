#include <iostream>
#include <fstream> //needed	to	open files
#include <string>
#include <vector>
#include "provided.h"
#include "Trie.h"
using namespace std;

int main()
{
	//string filename = "C:\\Users\kayla\source\repos\CS 32\Project4\Project4\data\Desulfurococcus_mucosus.txt";
	//string filename = "Desulfurococcus_mucosus.txt";
	string filename = "C:/Users/kayla/source/repos/CS_32/Project4/Project4/data/Desulfurococcus_mucosus.txt";
	ifstream strm(filename);
	if (!strm)
		cout << "cannot open file" << endl;
	
	string badfile = "C:/Users/kayla/source/repos/CS_32/Project4/Project4/data/badformat.txt";
	ifstream badstrm(badfile);
	if (!badstrm)
		cout << "cannot open file" << endl;

	vector<Genome> vg;

	bool success = Genome::load(strm, vg);
	if (success)
		cout << "Success on good stream!" << endl;
	else
		cout << "Fail on good stream." << endl;

	bool bad = Genome::load(badstrm, vg);
	if (!bad)
		cout << "Fail on bad stream!" << endl;
	else
		cout << "Success on bad stream." << endl;


}