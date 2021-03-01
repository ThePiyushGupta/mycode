#include <bits/stdc++.h>
using namespace std;

class Node {
public:
	int val;
	Node *next, *prev;
	Node(int _val) {
		val = _val;
		prev = next = NULL;
	}
};

class CircualarQueue {
public:
	Node* curr;
	CircualarQueue() {
		curr = NULL;
	}

	void insert(int val) {
		Node* temp = new Node(val);
		if (curr == NULL) {
			curr = temp;
			temp->next = temp->prev = temp;
		} else {
			temp->next = curr->next;
			curr->next->prev = temp;
			curr->next = temp;
			temp->prev = curr;
		}
	}

	void advance() {
		curr = curr->next;
	}

	void remove() {
		Node* temp = curr->next;
		temp->prev = curr->prev;
		curr->prev->next = temp;
		delete curr;
		if (curr != temp)
			curr = temp;
		else
			curr = NULL;
	}
};