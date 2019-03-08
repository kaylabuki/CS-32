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
		root->leaf = false;
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
		int ch1 = tolower(key[0]) - 97;
		if (cur->m_ptrs[ch1] == nullptr)
		{
			for (int i = 0; i < key.length(); i++)
			{
				int ch = tolower(key[i]) - 97;
				cur->m_ptrs[ch] = new TrieNode();
			}
			cur->values.push_back(value);
		}
		//to do: other case
	}

	std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const
	{
		return nullptr; // to do
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
		bool leaf;

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
};

#endif // TRIE_INCLUDED
