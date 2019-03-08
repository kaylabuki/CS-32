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
		A = 0, C = 1, G = 2, N = 3, T = 4;
		root = new TrieNode;
		for (int i = 0; i < 5; i++)
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
		// to do
	}

	void insert(const std::string& key, const ValueType& value)
	{
		// to do
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
		vector<TrieNode*> m_ptrs;
		vector<ValueType> values;
		bool leaf;

		void deleteTrieNode()
		{
			if (leaf)
				delete;
			else
			{
				for (int i = 0; i < 4; i++)
					m_ptrs[i]->deleteTrieNode();
			}
		}
	};
	int A, C, G, N, T;
	TrieNode* root;
};

#endif // TRIE_INCLUDED
