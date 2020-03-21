#include <iostream>
// #define nll std::NULL
class node {
    public:
	node *left, *right;
    int data;
	node(int n) : left(0), right(0),data(n) {
	}
};
class avl{
    public:
    node * head;
    avl(): head(0){

    };

    void insert(int n){
        node* temp = new node(n);
        if(!head) head = temp;
        else{
            node * curr = head;
            if(n>curr->data)
            while(curr)
        }
    }


};