#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

template<typename ValueType>
class Trie
{
public:
    Trie()
	{
		root = new TrieNode;
		for (int i = 0; i < 26; i++)
			root->m_ptrs[i] = nullptr;
	}

	~Trie()
	{
		TrieNode* cur = root;
		cur->deleteTrieNode();
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
		TrieNode* cur = root;
		for (int i = 0; i < key.length(); i++)
		{
			int ch = tolower(key[i]) - 97;
			if (cur->m_ptrs[ch] == nullptr)
			{
				int ch = tolower(key[i]) - 97;
				cur->m_ptrs[ch] = new TrieNode();
			}
			cur = cur->m_ptrs[ch];
		}
		cur->values.push_back(value);
	}

	std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const
	{
		std::vector<ValueType> retVals;
		TrieNode* cur = root;
		if (exactMatchOnly && isLeaf() && key.length() == 0)
			return values;
		int ch = tolower(key[0]) - 97;
		if (m_ptrs[ch] != nullptr)
			this->m_ptrsfind[ch]->(key.substr(1), exactMatchOnly);
	}

      // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
	template<typename ValueType>
	struct TrieNode
	{
		std::vector<TrieNode*> m_ptrs;
		std::vector<ValueType> values;

		void deleteTrieNode()
		{
			if (this == nullptr)
				return;
			else if (isLeaf())
				delete this;
			else
			{
				for (int i = 0; i < 26; i++)
					m_ptrs[i]->deleteTrieNode();
			}
		}

		bool isLeaf()
		{
			for (int i = 0; i < 26; i++)
			{
				if (m_ptrs[i] != nullptr)
					return true;
			}
			return false;
		}
	};

	TrieNode* root;

	/*std::vector<ValueType>findRec(const std::string& key, bool exactMatchOnly, bool foundMismatch)
	{
		TrieNode* cur = root;
		if (cur == nullptr)
			return;
		int ch = tolower(key[0]) - 97;
		if (m_ptrs[ch] != nullptr)
		this->m_ptrsfind[ch]->(key.substr(1), exactMatchOnly);
	}*/
};

#endif // TRIE_INCLUDED
