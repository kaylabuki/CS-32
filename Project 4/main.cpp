#include <iostream>
#include <fstream> //needed	to	open files
#include <string>
#include <vector>
#include "provided.h"
#include "Trie.h"
using namespace std;

int main()
{
	/*
	cout << "Testing Genome.cpp:" << endl << endl;
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
	cout << "Genome.cpp = success!" << endl << endl;

	*/

	/*cout << "Testing Trie:" << endl << endl;
	cout << "Creating new Trie:" << endl;
	Trie<int> t;
	cout << "Trie created!" << endl;
	t.insert("abc", 3);
	t.insert("abd", 4);
	t.insert("acd", 5);
	t.insert("bbc", 7);
	cout << endl << "Test 1, should print 3:" << endl;
	vector<int> vec1 = t.find("abc", true);
	for (int i = 0; i < vec1.size(); i++)
		cout << vec1[i] << " ";
	cout << endl << "Test 2, should print 4:" << endl;
	vec1 = t.find("abd", true);
	for (int i = 0; i < vec1.size(); i++)
		cout << vec1[i] << " ";
	cout << endl << "Test 3, should print 5:" << endl;
	vec1 = t.find("acd", true);
	for (int i = 0; i < vec1.size(); i++)
		cout << vec1[i] << " ";
	cout << endl << "Test 4, should print 3 4:" << endl;
	vec1 = t.find("abc", false);
	for (int i = 0; i < vec1.size(); i++)
		cout << vec1[i] << " ";
	cout << endl << "Test 5, should print 4 5:" << endl;
	vec1 = t.find("acd", false);
	for (int i = 0; i < vec1.size(); i++)
		cout << vec1[i] << " ";
	cout << endl << "Test 6, should print 3 4 5:" << endl;
	vec1 = t.find("abd", false);
	for (int i = 0; i < vec1.size(); i++)
		cout << vec1[i] << " ";
	cout << endl << "Test 7, should print nothing:" << endl;
	vec1 = t.find("a", false);
	for (int i = 0; i < vec1.size(); i++)
		cout << vec1[i] << " ";
	cout << endl << "Test 8, should print nothing:" << endl;
	vec1 = t.find("z", false);
	for (int i = 0; i < vec1.size(); i++)
		cout << vec1[i] << " ";*/
}