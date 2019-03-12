#include <iostream>
#include <fstream> //needed	to	open files
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "provided.h"
#include "Trie.h"
using namespace std;

class GenomeMatcherImpl
{
public:
	GenomeMatcherImpl(int minSearchLength);
	~GenomeMatcherImpl();
	void addGenome(const Genome& genome);
	int minimumSearchLength() const;
	bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
	bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
	int mSL;
	vector<Genome> genomes;
	Trie<DNAMatch>* genomeTrie;
	bool compareDNA(DNAMatch& dna1, DNAMatch& dna2)
	{
		return (dna1.genomeName == dna2.genomeName && dna1.length == dna2.length && dna1.position == dna2.position);
	}
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
	mSL = minSearchLength;
	genomeTrie = new Trie<DNAMatch>;
}

GenomeMatcherImpl::~GenomeMatcherImpl()
{
	delete genomeTrie;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
	genomes.push_back(genome);

	for (int i = 0; i < genome.length() - mSL; i++)
	{
		string subSeq = "";
		genome.extract(i, mSL, subSeq);
		DNAMatch dna;
		dna.genomeName = genome.name();
		dna.length = mSL;
		dna.position = i;
		//vector<DNAMatch> vec = genomeTrie->find(subSeq, true);
		//if (find(vec.begin(), vec.end(), ) != vec.end())
		genomeTrie->insert(subSeq, dna);
	}
}

int GenomeMatcherImpl::minimumSearchLength() const
{
	return mSL;
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	if (fragment.size() < minimumLength)
		return false;
	if (minimumLength < minimumSearchLength())
		return false;
	vector<DNAMatch> shortMatches = genomeTrie->find(fragment.substr(0, minimumLength), exactMatchOnly);
	if (fragment.size() > minimumLength)
	{
		for (int i = 0; i < shortMatches.size(); i++)
		{
			for (int j = 0; j < genomes.size(); j++)
			{
				string frag = "";
				for (int k = 1; k < fragment.size() - minimumLength; k++)
				{
					if (genomes[j].extract(shortMatches[i].position + minimumLength, k, frag))
					{
						if (frag == fragment.substr(minimumLength, k))
							shortMatches[i].length = minimumLength + k;
					}
				}
			}
		}
	}
	if (shortMatches.empty())
		return false;
	/*if (!longMatches.empty())
		matches = longMatches;*/
	matches = shortMatches;
	vector<DNAMatch>::iterator it = matches.begin()+1;
	while (it != matches.end())
	{
		if ((it - 1)->genomeName == it->genomeName)
		{
			it = matches.erase(it);
		}
		else
			it++;
	}
	return true;
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	return false;  // This compiles, but may not be correct
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
	m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
	delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
	m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
	return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
