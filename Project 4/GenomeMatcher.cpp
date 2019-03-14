#include <iostream>
#include <fstream> //needed	to	open files
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <set>
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
	//Trie<pair<Genome*, int>> genomeTrie;
	struct trieValue {
		string name;
		int vectorIndex;
		int sqcPos;
	};
	Trie<trieValue> genomeTrie;

	int findLongestPrefix(string fragment, string potentialMatch, bool lookForExactMatch) const
	{
		int count = 0;
		for (int i = 0; i < fragment.size(); i++)
		{
			if (fragment[i] != potentialMatch[i] && lookForExactMatch)
				return count;
			else if (fragment[i] != potentialMatch[i])
			{
				count++;
				lookForExactMatch = true;
			}
			else
				count++;
		}
		return count;
	}

	struct g_compare
	{
		bool operator() (GenomeMatch g1, GenomeMatch g2) const
		{
			return (g1.percentMatch > g2.percentMatch);
		}
	};
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
	mSL = minSearchLength;
}

GenomeMatcherImpl::~GenomeMatcherImpl()
{
	//delete genomeTrie;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
	genomes.push_back(genome);

	for (int i = 0; i < genome.length() - mSL + 1; i++)
	{
		string subSeq = "";
		genome.extract(i, mSL, subSeq);
			//Genome ptr = genome;
			//pair<Genome*, int> newVal(&ptr, i);
		trieValue newVal;
		newVal.name = genome.name();
		newVal.sqcPos = i;
		newVal.vectorIndex = genomes.size() - 1;
		genomeTrie.insert(subSeq, newVal);
	}
}

int GenomeMatcherImpl::minimumSearchLength() const
{
	return mSL;
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	if (fragment.size() < minimumLength || minimumLength < minimumSearchLength())
		return false;
	vector<trieValue> prefixes = genomeTrie.find(fragment.substr(0, minimumLength), exactMatchOnly);
	unordered_map<string, DNAMatch> noDuplicates;
	if (fragment.size() > minimumSearchLength())
	{
		for (int i = 0; i < prefixes.size(); i++)
		{
			int index = prefixes[i].sqcPos;
			string potentialMatch = "";
			genomes[prefixes[i].vectorIndex].extract(index, fragment.size(), potentialMatch);
			int matchingLetters = findLongestPrefix(fragment, potentialMatch, exactMatchOnly);
			DNAMatch newMatch;
			newMatch.genomeName = prefixes[i].name;
			newMatch.position = index;
			newMatch.length = matchingLetters;
			unordered_map<string, DNAMatch>::iterator it = noDuplicates.find(newMatch.genomeName);
			if (it == noDuplicates.end() || it->second.length < newMatch.length)
				noDuplicates.insert_or_assign(newMatch.genomeName, newMatch);
		}
		unordered_map<string, DNAMatch>::iterator it = noDuplicates.begin();
		while (it != noDuplicates.end())
		{
			matches.push_back(it->second);
			it++;
		}
	}
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	int s = (query.length()) / fragmentMatchLength;
	vector<DNAMatch> totalMatches;
	set<GenomeMatch, g_compare> gset;
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
			gset.insert(g);
		}
		set<GenomeMatch, g_compare>::iterator it = gset.begin();
		while(it != gset.end())
			results.push_back(*it);
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
