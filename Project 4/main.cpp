#include <iostream>
#include <fstream> //needed	to	open	files
#include <string>
#include <vector>
#include "provided.h"
using namespace std;

int main()
{
	string filename = "C:\\Users\\kayla\\source\\repos\\CS32\\Project4\\Project4\\data\\Desulfurococcus_mucosus.txt";
	ifstream strm(filename);
	vector<Genome> vg;
	bool success = false;
	success = Genome::load(strm, vg);
	if (success)
		cout << "Success!" << endl;
	else
		cout << "Fail." << endl;
}