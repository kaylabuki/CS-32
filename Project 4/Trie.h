#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

#include <iostream>
using namespace std;

template<typename ValueType>
class Trie
{
public:
	Trie()
	{
		root = new TrieNode;
	}

	~Trie()
	{
		destructorHelper(root);
	}

	void reset()
	{
		destructorHelper(root);
		root = new TrieNode;
	}

	void insert(const std::string& key, const ValueType& value)
	{
		TrieNode* cur = root;
		for (int i = 0; i < key.size(); i++)
		{
			int ch = key[i];
			if (cur->children[ch] == nullptr)
				cur->children[ch] = new TrieNode;
			if (cur != root)
				cur->children[ch]->parent = cur;
			cur = cur->children[ch];
		}
		(cur->values).push_back(value);
	}

	std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const
	{
		std::vector<ValueType> retVals;
		bool found = false;
		root->findRec(key, exactMatchOnly, retVals, found);
		if (!found)
			retVals.clear();
		return retVals;
	}

	// C++11 syntax for preventing copying and assignment
	Trie(const Trie&) = delete;
	Trie& operator=(const Trie&) = delete;
private:
	struct TrieNode
	{
		std::vector<TrieNode*> children;
		std::vector<ValueType> values;
		TrieNode* parent;

		TrieNode()
		{
			for (int i = 0; i < 127; i++)
				children.push_back(nullptr);
			parent = nullptr;
		}

		bool isLeaf()
		{
			for (int i = 0; i < 127; i++)
			{
				if (children[i] != nullptr)
					return false;
			}
			return true;
		}

		void findRec(const std::string& key, bool exactMatchOrFoundMismatch, std::vector<ValueType>& vec, bool& found)
		{
			int ch = key[0];
			if (key.length() == 1)
			{
				if (children[ch])
				{
					for (int i = 0; i < children[ch]->values.size(); i++)
						vec.push_back(children[ch]->values[i]);
					found = true;
					return;
				}
				/*for (int i = 0; i < children[i]->values.size(); i++)
					vec.push_back(children[i]->values[i]);
				found = true;
				return;*/
			}
			if (!children[ch] && exactMatchOrFoundMismatch)
				return;
			else if (exactMatchOrFoundMismatch)
				children[ch]->findRec(key.substr(1), exactMatchOrFoundMismatch, vec, found);
			else
			{
				for (int i = 0; i < 127; i++)
				{
					if (children[i])
					{
						if (i == ch)
							children[i]->findRec(key.substr(1), exactMatchOrFoundMismatch, vec, found);
						else if (children[i]->parent != nullptr)
							children[i]->findRec(key.substr(1), true, vec, found);
					}
				}
			}
		}
	};

	void destructorHelper(TrieNode* cur)
	{
		if (cur == nullptr)
			return;
		for (int i = 0; i < 127; i++)
			destructorHelper(cur->children[i]);
		delete cur;
	}

	TrieNode* root;
};

#endif // TRIE_INCLUDED
