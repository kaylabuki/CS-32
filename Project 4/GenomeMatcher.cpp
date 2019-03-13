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
	//Trie<DNAMatch>* genomeTrie;
	Trie<pair<Genome, int>>* genomeTrie;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
	mSL = minSearchLength;
	//genomeTrie = new Trie<DNAMatch>;
	genomeTrie = new Trie<pair<Genome, int>>;
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
		//DNAMatch dna;
		/*dna.genomeName = genome.name();
		dna.length = mSL;
		dna.position = i;
		genomeTrie->insert(subSeq, dna);*/
		
		pair<Genome, int> newVal(genome, i);
		genomeTrie->insert(subSeq, newVal);
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
	//vector<DNAMatch> shortMatches = genomeTrie->find(fragment.substr(0, minimumLength), exactMatchOnly);
	vector<pair<Genome, int>> shortMatches = genomeTrie->find(fragment.substr(0, minimumLength), exactMatchOnly);
	if (fragment.size() > minimumLength)
	{
		for (int i = 0; i < shortMatches.size(); i++)
		{
			int moreMatchingLetters = 0;
			int index = shortMatches[i].second;
			for (int j = minimumSearchLength(); j < fragment.size(); j++)
			{
				string longerMatch = "";
				if (shortMatches[i].first.extract(index, i, longerMatch))
				{
					if (longerMatch == fragment.substr(minimumSearchLength(), i))
						moreMatchingLetters++;
				}
			}
			DNAMatch newMatch;
			newMatch.genomeName = shortMatches[i].first.name();
			newMatch.position = shortMatches[i].second;
			newMatch.length = minimumSearchLength() + moreMatchingLetters;
			matches.push_back(newMatch);
		}
	}
	/*if (fragment.size() > minimumLength)
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
	}*/
	if (shortMatches.empty())
		return false;
	/*if (!longMatches.empty())
		matches = longMatches;*/
	//matches = shortMatches;
	/*vector<DNAMatch>::iterator it = matches.begin()+1;
	while (it != matches.end())
	{
		if ((it - 1)->genomeName == it->genomeName)
		{
			it = matches.erase(it);
		}
		else
			it++;
	}*/
	//matches.erase(unique(matches.begin(), matches.end()), matches.end());
	return true;
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	int s = (query.length()) / fragmentMatchLength;
	vector<DNAMatch> totalMatches;
	for (int i = 0; i < query.length() - fragmentMatchLength; fragmentMatchLength*(i++))
	{
		string frag;
		query.extract(i, fragmentMatchLength, frag);
		vector<DNAMatch> matches;
		if (findGenomesWithThisDNA(frag, fragmentMatchLength, exactMatchOnly, matches))
		{
			for (int i = 0; i < matches.size(); i++)
				totalMatches.push_back(matches[i]);
		}
	}

	for(int i = 0; i < genomes.size(); i++)
	{
		int gMatches = 0;
		string nm = genomes[i].name();
		for (int j = 0; j < totalMatches.size(); j++)
		{
			if (totalMatches[i].genomeName == nm)
				gMatches++;
		}
		double p = 0;
		if(s != 0)
			p = gMatches / s;
		if (p >= matchPercentThreshold)
		{
			GenomeMatch g;
			g.genomeName = nm;
			g.percentMatch = p;
			results.push_back(g);
		}
		//sort(results.begin(), results.end(), greater<GenomeMatch>());
	}
	return true;
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
