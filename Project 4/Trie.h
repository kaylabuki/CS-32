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
		root = new TrieNode<ValueType>;
	}

	~Trie()
	{
		destructorHelper(root);
	}

	void reset()
	{
		TrieNode* cur = root;
		delete this;
		Trie newTrie = new Trie();
		newTrie->root = cur;
	}

	void insert(const std::string& key, const ValueType& value)
	{
		TrieNode<ValueType>* cur = root;
		for (int i = 0; i < key.size(); i++)
		{
			int ch = key[i];
			if (cur->children[ch] == nullptr)
				cur->children[ch] = new TrieNode<ValueType>;
			if(cur != root)
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
	template<typename ValueType>
	struct TrieNode
	{
		std::vector<TrieNode*> children;
		std::vector<ValueType> values;
		TrieNode<ValueType>* parent;

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
			if (key.length() == 0)
			{
				for (int i = 0; i < values.size(); i++)
					vec.push_back(values[i]);
				found = true;
				return;
			}
			int ch = key[0];
			if (!children[ch] && exactMatchOrFoundMismatch)
				return;
			else if(exactMatchOrFoundMismatch)
				children[ch]->findRec(key.substr(1), exactMatchOrFoundMismatch, vec, found);
			else
			{
				for (int i = 0; i < 127; i++)
				{
					if (children[i])
					{
						if (i == ch)
							children[i]->findRec(key.substr(1), exactMatchOrFoundMismatch, vec, found);
						else if(children[i]->parent != nullptr)
							children[i]->findRec(key.substr(1), true, vec, found);
					}
				}
			}
		}
	};
	
	void destructorHelper(TrieNode<ValueType>* cur)
	{
		if (cur == nullptr)
			return;
		for (int i = 0; i < 127; i++) // CHANGE BACK TO 0 to 127
			destructorHelper(cur->children[i]);
		delete cur;
	}

	TrieNode<ValueType>* root;
};

#endif // TRIE_INCLUDED
