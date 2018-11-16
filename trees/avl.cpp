// C program to insert a node in AVL tree
#include <bits/stdc++.h>
using namespace std;

// An AVL tree node
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
    Node(int k) {
        left = right = NULL;
        key = k;
        height = 1;
    }
};

class avlTree {
   private:
    Node *top;

   public:
    avlTree() { top = NULL; }

    void printpreorder() { preOrder(top); }

    void preOrder(Node *root) {
        // Node *root = top;
        if (root != NULL) {
            printf("%d ", root->key);
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    Node *insert(Node *node, int key) {
        /* 1. Perform the normal BST insertion */
        if (node == NULL) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else  // Equal keys are not allowed in BST
            return node;

        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->left), height(node->right));

        /* 3. Get the balance factor of this ancestor node to check whether this * node became unbalanced */
        int balance = getBalance(node);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->key) return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key) return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    // Get Balance factor of node N
    int getBalance(struct Node *N) {
        if (N == NULL) return 0;
        return height(N->left) - height(N->right);
    }

    // A utility function to get the height of the tree
    int height(struct Node *N) {
        if (N == NULL) return 0;
        return N->height;
    }

    // A utility function to right rotate subtree rooted with y. See the diagram given above.
    Node *rightRotate(struct Node *y) {
        struct Node *x = y->left;
        struct Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        // Return new root
        return x;
    }

    // A utility function to left rotate subtree rooted with x. See the diagram given above.
    Node *leftRotate(struct Node *x) {
        struct Node *y = x->right;
        struct Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        // Return new root
        return y;
    }

    // Recursive function to delete a node with given key from subtree with given root. It returns root of the modified subtree.
    Node *deleteNode(struct Node *root, int key) {
        // STEP 1: PERFORM STANDARD BST DELETE
        if (root == NULL) return root;

        // If the key to be deleted is smaller than the root's key, then it lies
        // in left subtree
        if (key < root->key) root->left = deleteNode(root->left, key);

        // If the key to be deleted is greater than the root's key, then it lies
        // in right subtree
        else if (key > root->key)
            root->right = deleteNode(root->right, key);

        // if key is same as root's key, then This is the node to be deleted
        else {
            // node with only one child or no child
            if ((root->left == NULL) || (root->right == NULL)) {
                struct Node *temp = root->left ? root->left : root->right;

                // No child case
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                } else  // One child case Copy the contents of the non-empty child
                    *root = *temp;
                delete temp;
            } else {
                // node with two children: Get the inorder successor (smallest in the right subtree)
                struct Node *temp = minValueNode(root->right);

                // Copy the inorder successor's data to this node
                root->key = temp->key;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->key);
            }
        }

        // If the tree had only one node then return
        if (root == NULL) return root;

        // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
        root->height = 1 + max(height(root->left), height(root->right));

        // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
        int balance = getBalance(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    /* Given a non-empty binary search tree, return the node with minimum key value found in that tree. Note that the entire tree does not need to be searched. */
    struct Node *minValueNode(struct Node *node) {
        struct Node *current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != NULL) current = current->left;
        return current;
    }
};

/* Driver program to test above function*/
int main() {}