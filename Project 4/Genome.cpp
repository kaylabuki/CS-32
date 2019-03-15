#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
using namespace std;

class GenomeImpl
{
public:
	GenomeImpl(const string& nm, const string& sequence);
	static bool load(istream& genomeSource, vector<Genome>& genomes);
	int length() const;
	string name() const;
	bool extract(int position, int length, string& fragment) const;
private:
	string m_name;
	string m_sequence;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
	m_name = nm;
	m_sequence = sequence;
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
	genomes.clear();
	string newGenome, nm, sequence = "";
	bool passedFirst = false;
	while (getline(genomeSource, newGenome))
	{
		if (newGenome == "")
			return false;
		else if (newGenome[0] == '>')
		{
			if (newGenome.substr(1) == "")
				return false;
			if (sequence != "")
			{
				Genome ng(nm, sequence);
				genomes.push_back(ng);
			}
			else if (passedFirst)
				return false;
			nm = newGenome.substr(1);
			sequence = "";
		}
		else
		{
			if (nm == "")
				return false;
			for (int i = 0; i < newGenome.length(); i++)
			{
				switch (newGenome[i])
				{
				case 'A':
				case 'C':
				case 'T':
				case 'G':
				case 'N':
				{
					sequence += newGenome[i];
					break;
				}
				default:
				{
					return false;
				}
				}
			}
			passedFirst = true;
		}
		//newGenome = "";
	}

	if (nm != "" && sequence != "")
	{
		Genome ng(nm, sequence);
		genomes.push_back(ng);
	}

	return passedFirst;
}

int GenomeImpl::length() const
{
	return m_sequence.length();
}

string GenomeImpl::name() const
{
	return m_name;
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
	int i = position;
	for (; i < position + length && i < this->length(); i++)
	{
		fragment += m_sequence[i];
	}
	if (i < (length - 1))
		return false;
	else
		return true;
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
	m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
	delete m_impl;
}

Genome::Genome(const Genome& other)
{
	m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
	GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
	delete m_impl;
	m_impl = newImpl;
	return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
	return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
	return m_impl->length();
}

string Genome::name() const
{
	return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
	return m_impl->extract(position, length, fragment);
}
