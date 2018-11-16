/* ****************************************************************************************************************

                                               B-Trees
All leaves are at the same level
A B-Tree is defined by the term minimum degree ‘t’. The value of t depends upon disk block size.
Every node except root must contain at least t-1 keys. Root may contain minimum 1 key.
All nodes (including root) may contain at most 2t – 1 keys.
Number of children of a node is equal to the number of keys in it plus 1
All keys of a node are sorted in increasing order. The child between two keys k1 and k2 contains all keys in the range from k1 and k2.
B-Tree grows and shrinks from the root which is unlike Binary Search Tree. Binary Search Trees grow downward and also shrink from downward
Like other balanced Binary Search Trees, time complexity to search, insert and delete is O(Logn)
    __________________________________________________________________________________________________________

INSERTION
1) Initialize x as root.
2) While x is not leaf, do following
..a) Find the child of x that is going to to be traversed next. Let the child be y.
..b) If y is not full, change x to point to y.
..c) If y is full, split it and change x to point to one of the two parts of y. If k is smaller than mid key in y, then set x as first part of y. Else second part of y. When we split y, we move a key from y to its parent x.
3) The loop in step 2 stops when x is leaf. x must have space for 1 extra key as we have been splitting all nodes in advance. So simply insert k to x

    ____________________________________________________________________________________________________________

Deletion


***************************************************************************************************************** */
//the code is taken from geeksforgeeks and is similar to coremen
#include <iostream>
using namespace std;

// A BTree node
class BTreeNode
{
    int *keys;     // An array of keys
    int t;         // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // An array of child pointers
    int n;         // Current number of keys
    bool leaf;     // Is true when node is leaf. Otherwise false

  public:
    BTreeNode(int _t, bool _leaf)
    {
        // Copy the given minimum degree and leaf property
        t = _t;
        leaf = _leaf;

        // Allocate memory for maximum number of possible keys and child pointers
        keys = new int[2 * t - 1];
        C = new BTreeNode *[2 * t];

        // Initialize the number of keys as 0
        n = 0;
    }

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse()
    {
        // There are n keys and n+1 children, traverse through n keys and first n children
        int i;
        for (i = 0; i < n; i++)
        {
            // If this is not leaf, then before printing key[i],traverse the subtree rooted with child C[i].
            if (leaf == false)
                C[i]->traverse();
            cout << " " << keys[i];
        }

        // Print the subtree rooted with last child
        if (leaf == false)
            C[i]->traverse();
    }

    // A function to search a key in the subtree rooted with this node.
    BTreeNode *search(int k)
    {
        // Find the first key greater than or equal to k
        int i = 0;
        while (i < n && k > keys[i])
            i++;

        // If the found key is equal to k, return this node
        if (keys[i] == k)
            return this;

        // If the key is not found here and this is a leaf node
        if (leaf == true)
            return NULL;

        // Go to the appropriate child
        return C[i]->search(k);
    }

    // A utility function to insert a new key. The node must be non-full when this function is called
    void insertNonFull(int k)
    {
        int i = n - 1; // Initialize index as index of rightmost element

        // If this is a leaf node
        if (leaf == true){

            // Find the location of new key to be inserted and Move all greater keys one place ahead
            while (i >= 0 && keys[i] > k){
                keys[i + 1] = keys[i];
                i--;
            }

            keys[i + 1] = k; // Insert the new key at found location
            n = n + 1;
        }
        else // If this node is not leaf
        {
            // Find the child which is going to have the new key
            while (i >= 0 && keys[i] > k)
                i--;

            // See if the found child is full
            if (C[i + 1]->n == 2 * t - 1)
            {
                splitChild(i + 1, C[i + 1]); // If the child is full, then split it

                // After split, the middle key of C[i] goes up and C[i] is splitted into two.  See which of the two is going to have the new key
                if (keys[i + 1] < k)
                    i++;
            }
            C[i + 1]->insertNonFull(k);
        }
    }

    // A utility function to split the child y of this node Note that y must be full when this function is called
    void splitChild(int i, BTreeNode *y)
    {
        BTreeNode *z = new BTreeNode(y->t, y->leaf); // Create a new node which is going to store (t-1) keys of y
        z->n = t - 1;

        // Copy the last (t-1) keys of y to z
        for (int j = 0; j < t - 1; j++)
            z->keys[j] = y->keys[j + t];

        // Copy the last t children of y to z
        if (y->leaf == false)
        {
            for (int j = 0; j < t; j++)
                z->C[j] = y->C[j + t];
        }

        y->n = t - 1; // Reduce the number of keys in y

        // Since this node is going to have a new child, create space of new child
        for (int j = n; j >= i + 1; j--)
            C[j + 1] = C[j];

        // Link the new child to this node
        C[i + 1] = z;

        // A key of y will move to this node.  Move all greater keys one space ahead
        for (int j = n - 1; j >= i; j--)
            keys[j + 1] = keys[j];

        keys[i] = y->keys[t - 1]; // Copy the middle key of y to this node
        n = n + 1;                // Increment count of keys in this node
    }

    // A function to borrow a key from C[idx-1] and insert it into C[idx]
    void borrowFromPrev(int idx)
    {

        BTreeNode *child = C[idx];
        BTreeNode *sibling = C[idx - 1];

        // The last key from C[idx-1] goes up to the parent and key[idx-1] from parent is inserted as the first key in C[idx]. Thus, the  loses sibling one key and child gains one key
        // Moving all key in C[idx] one step ahead
        for (int i = child->n - 1; i >= 0; --i)
            child->keys[i + 1] = child->keys[i];

        // If C[idx] is not a leaf, move all its child pointers one step ahead
        if (!child->leaf)
        {
            for (int i = child->n; i >= 0; --i)
                child->C[i + 1] = child->C[i];
        }

        // Setting child's first key equal to keys[idx-1] from the current node
        child->keys[0] = keys[idx - 1];

        // Moving sibling's last child as C[idx]'s first child
        if (!child->leaf)
            child->C[0] = sibling->C[sibling->n];

        // Moving the key from the sibling to the parent This reduces the number of keys in the sibling
        keys[idx - 1] = sibling->keys[sibling->n - 1];

        child->n += 1;
        sibling->n -= 1;
    }

    // A function to borrow a key from the C[idx+1] and place it in C[idx]
    void borrowFromNext(int idx)
    {

        BTreeNode *child = C[idx];
        BTreeNode *sibling = C[idx + 1];

        // keys[idx] is inserted as the last key in C[idx]
        child->keys[(child->n)] = keys[idx];

        // Sibling's first child is inserted as the last child into C[idx]
        if (!(child->leaf))
            child->C[(child->n) + 1] = sibling->C[0];

        //The first key from sibling is inserted into keys[idx]
        keys[idx] = sibling->keys[0];

        // Moving all keys in sibling one step behind
        for (int i = 1; i < sibling->n; ++i)
            sibling->keys[i - 1] = sibling->keys[i];

        // Moving the child pointers one step behind
        if (!sibling->leaf)
        {
            for (int i = 1; i <= sibling->n; ++i)
                sibling->C[i - 1] = sibling->C[i];
        }

        // Increasing and decreasing the key count of C[idx] and C[idx+1] respectively
        child->n += 1;
        sibling->n -= 1;
    }

    // A function to merge C[idx] with C[idx+1] C[idx+1] is freed after merging
    void merge(int idx)
    {
        BTreeNode *child = C[idx];
        BTreeNode *sibling = C[idx + 1];

        // Pulling a key from the current node and inserting it into (t-1)th position of C[idx]
        child->keys[t - 1] = keys[idx];

        // Copying the keys from C[idx+1] to C[idx] at the end
        for (int i = 0; i < sibling->n; ++i)
            child->keys[i + t] = sibling->keys[i];

        // Copying the child pointers from C[idx+1] to C[idx]
        if (!child->leaf)
        {
            for (int i = 0; i <= sibling->n; ++i)
                child->C[i + t] = sibling->C[i];
        }

        // Moving all keys after idx in the current node one step before to fill the gap created by moving keys[idx] to C[idx]
        for (int i = idx + 1; i < n; ++i)
            keys[i - 1] = keys[i];

        // Moving the child pointers after (idx+1) in the current node one step before
        for (int i = idx + 2; i <= n; ++i)
            C[i - 1] = C[i];

        // Updating the key count of child and the current node
        child->n += sibling->n + 1;
        n--;

        // Freeing the memory occupied by sibling
        delete (sibling);
    }

    int findKey(int k)
    {
        int idx = 0;
        while (idx < n && keys[idx] < k)
            ++idx;
        return idx;
    }

    // A function to remove the key k from the sub-tree rooted with this node
    void remove(int k)
    {
        int idx = findKey(k);

        // The key to be removed is present in this node
        if (idx < n && keys[idx] == k)
        {
            // If the node is a leaf node - removeFromLeaf is called Otherwise, removeFromNonLeaf function is called
            if (leaf)
                removeFromLeaf(idx);
            else
                removeFromNonLeaf(idx);
        }
        else
        {
            // If this node is a leaf node, then the key is not present in tree
            if (leaf)
            {
                cout << "The key " << k << " is does not exist in the tree\n";
                return;
            }

            // The key to be removed is present in the sub-tree rooted with this node The flag indicates whether the key is present in the sub-tree rooted with the last child of this node
            bool flag = ((idx == n) ? true : false);

            // If the child where the key is supposed to exist has less that t keys, we fill that child
            if (C[idx]->n < t)
                fill(idx);

            // If the last child has been merged, it must have merged with the previous child and so we recurse on the (idx-1)th child. Else, we recurse on the (idx)th child which now has atleast t keys
            if (flag && idx > n)
                C[idx - 1]->remove(k);
            else
                C[idx]->remove(k);
        }
    }

    // A function to remove the idx-th key from this node - which is a leaf node
    void removeFromLeaf(int idx)
    {
        // Move all the keys after the idx-th pos one place backward
        for (int i = idx + 1; i < n; ++i)
            keys[i - 1] = keys[i];

        // Reduce the count of keys
        n--;
    }

    // A function to remove the idx-th key from this node - which is a non-leaf node
    void removeFromNonLeaf(int idx)
    {
        int k = keys[idx];

        // If the child that precedes k (C[idx]) has atleast t keys, find the predecessor 'pred' of k in the subtree rooted at C[idx].Replace k by pred. Recursively delete pred in C[idx]
        if (C[idx]->n >= t)
        {
            int pred = getPred(idx);
            keys[idx] = pred;
            C[idx]->remove(pred);
        }

        // If the child C[idx] has less that t keys, examine C[idx+1].
        // If C[idx+1] has atleast t keys, find the successor 'succ' of k in the subtree rooted at C[idx+1]
        // Replace k by succ and Recursively delete succ in C[idx+1]
        else if (C[idx + 1]->n >= t)
        {
            int succ = getSucc(idx);
            keys[idx] = succ;
            C[idx + 1]->remove(succ);
        }

        // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1] into C[idx]
        // Now C[idx] contains 2t-1 keys
        // Free C[idx+1] and recursively delete k from C[idx]
        else
        {
            merge(idx);
            C[idx]->remove(k);
        }
    }

    // A function to get predecessor of keys[idx]
    int getPred(int idx)
    {
        // Keep moving to the right most node until we reach a leaf
        BTreeNode *cur = C[idx];
        while (!cur->leaf)
            cur = cur->C[cur->n];

        // Return the last key of the leaf
        return cur->keys[cur->n - 1];
    }

    int getSucc(int idx)
    {

        // Keep moving the left most node starting from C[idx+1] until we reach a leaf
        BTreeNode *cur = C[idx + 1];
        while (!cur->leaf)
            cur = cur->C[0];

        // Return the first key of the leaf
        return cur->keys[0];
    }

    // A function to fill child C[idx] which has less than t-1 keys
    void fill(int idx)
    {

        // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key from that child
        if (idx != 0 && C[idx - 1]->n >= t)
            borrowFromPrev(idx);

        // If the next child(C[idx+1]) has more than t-1 keys, borrow a key from that child
        else if (idx != n && C[idx + 1]->n >= t)
            borrowFromNext(idx);

        // Merge C[idx] with its sibling
        // If C[idx] is the last child, merge it with with its previous sibling
        // Otherwise merge it with its next sibling
        else
        {
            if (idx != n)
                merge(idx);
            else
                merge(idx - 1);
        }
        return;
    }

    friend class BTree; // Make the BTree friend of this so that we can access private members of this class in BTree functions
};

// A BTree
class BTree
{
    BTreeNode *root; // Pointer to root node
    int t;           // Minimum degree
  public:
    // Constructor (Initializes tree as empty)
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }

    // function to traverse the tree
    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

    // function to search a key in this tree
    BTreeNode *search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    // The main function that inserts a new key in this B-Tree
    void insert(int k)
    {
        // If tree is empty
        if (root == NULL){

            root = new BTreeNode(t, true);              // Allocate memory for root
            root->keys[0] = k;                          // Insert key
            root->n = 1;                                // Update number of keys in root
        }
        else{                                           // If tree is not empty
            if (root->n == 2 * t - 1){                  //Only  if root is full, then tree grows in height

                BTreeNode *s = new BTreeNode(t, false); // Allocate memory for new root
                s->C[0] = root;                         // Make old root as child of new root
                s->splitChild(0, root);                 // Split the old root and move 1 key to the new root

                // New root has two children now.  Decide which of the two children is going to have new key
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->C[i]->insertNonFull(k);

                root = s;                               // Change root
            }
            else                                        // If root is not full, call insertNonFull for root
                root->insertNonFull(k);
        }
    }

    void remove(int k)
    {
        if (!root)
        {
            cout << "The tree is empty\n";
            return;
        }

        root->remove(k); // Call the remove function for root

        // If the root node has 0 keys, make its first child as the new root if it has a child, otherwise set root as NULL
        if (root->n == 0)
        {
            BTreeNode *tmp = root;
            if (root->leaf)
                root = NULL;
            else
                root = root->C[0];

            delete tmp; // Free the old root
        }
        return;
    }
};

//*****************************************************************************************************************