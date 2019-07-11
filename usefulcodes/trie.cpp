#include <bits/stdc++.h>
// Trie implemenation using maps requires lesser space but consumes a little bit more time
using namespace std;
class node {
public:
	map<char, node> child;
	bool iscompleteword;
	node() {
		iscompleteword = false;
	}
	~node();
};

class trie {
private:
	node* head;

public:
	trie(/* args */) {
		head = NULL;
	}
	void insert(string s) {
		node* itr = head;
		for (int c = 0; c < s.length(); c++) {
			itr = &itr->child[s[c]];
		}
        
        itr->iscompleteword = true;
	}
	~trie();
};
