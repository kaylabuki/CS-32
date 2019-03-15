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

	struct smaller_percentage
	{
		bool operator ()(const GenomeMatch& p1, const GenomeMatch& p2) const
		{
			return p1.percentMatch > p2.percentMatch;
		}
	};
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
	mSL = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
	genomes.push_back(genome);

	for (int i = 0; i < genome.length() - mSL + 1; i++)
	{
		string subSeq = "";
		genome.extract(i, mSL, subSeq);
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
	matches.clear();
	if (fragment.size() < minimumLength || minimumLength < minimumSearchLength())
		return false;
	vector<trieValue> prefixes = genomeTrie.find(fragment.substr(0, minimumSearchLength()), exactMatchOnly);
	unordered_map<string, DNAMatch> noDuplicates;
	for (int i = 0; i < prefixes.size(); i++)
	{
		int index = prefixes[i].sqcPos;
		string potentialMatch = "";
		genomes[prefixes[i].vectorIndex].extract(index, fragment.size(), potentialMatch);
		int matchingLetters = findLongestPrefix(fragment, potentialMatch, exactMatchOnly);
		if (matchingLetters >= minimumLength)
		{
			DNAMatch newMatch;
			newMatch.genomeName = prefixes[i].name;
			newMatch.position = index;
			newMatch.length = matchingLetters;
			unordered_map<string, DNAMatch>::iterator it = noDuplicates.find(newMatch.genomeName);
			if (it == noDuplicates.end() || it->second.length < newMatch.length)
				noDuplicates.insert_or_assign(newMatch.genomeName, newMatch);
		}
	}
	unordered_map<string, DNAMatch>::iterator it = noDuplicates.begin();
	while (it != noDuplicates.end())
	{
		matches.push_back(it->second);
		it++;
	}
	if (matches.empty())
		return false;
	return true;
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	if (fragmentMatchLength < minimumSearchLength())
		return false;
	int s = (query.length() / fragmentMatchLength);
	map<string, int> genomeMatchCount;
	vector<DNAMatch> potentialRelatedGenomes;
	map<string, GenomeMatch> gmap;
	for (int i = 0; i < (query.length() - fragmentMatchLength + 1); i += fragmentMatchLength)
	{
		string frag;
		query.extract(i, fragmentMatchLength, frag);
		vector<DNAMatch> matches;
		if (findGenomesWithThisDNA(frag, fragmentMatchLength, exactMatchOnly, matches))
		{
			for (int i = 0; i < matches.size(); i++)
			{
				potentialRelatedGenomes.push_back(matches[i]);
				map<string, int>::iterator it = genomeMatchCount.find(matches[i].genomeName);
				if (it == genomeMatchCount.end())
					genomeMatchCount.insert({ matches[i].genomeName, 1 });
				else
					it->second++;
			}
		}
	}

	for (int i = 0; i < potentialRelatedGenomes.size(); i++)
	{
		double p = 0;
		string nm = potentialRelatedGenomes[i].genomeName;
		int matches = genomeMatchCount.at(nm);
		if (s != 0)
			p = 100.0 * matches / s;
		if (p >= matchPercentThreshold)
		{
			GenomeMatch g;
			g.genomeName = nm;
			g.percentMatch = p;
			map<string, GenomeMatch>::iterator it = gmap.find(nm);
			if (it != gmap.end())
			{
				if (it->second.percentMatch < p)
					gmap[nm].percentMatch = p;
			}
			else
				gmap.emplace(nm, g);
		}
	}
	map<string, GenomeMatch>::iterator it = gmap.begin();
	while (it != gmap.end())
	{
		results.push_back(it->second);
		it++;
	}
	sort(results.begin(), results.end(), smaller_percentage());
	if (results.empty())
		return false;
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
