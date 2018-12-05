#include <bits/stdc++.h>
// //*****************************************************************************************************
using namespace std;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<string> vs;
// //*****************************************************************************************************
// vector<string> split(const string &s, char c) {
//     vector<string> v;
//     stringstream ss(s);
//     string x;
//     while (getline(ss, x, c))
//         v.emplace_back(x);
//     return move(v);
// }
// template <typename T, typename... Args> inline string arrStr(T arr, int n) {
//     stringstream s;
//     s << "[";
//     for (int i = 0; i < n - 1; i++)
//         s << arr[i] << ",";
//     s << arr[n - 1] << "]";
//     return s.str();
// }

// #define EVARS(args...)                                                         \
//     {                                                                          \
//         __evars_begin(__LINE__);                                               \
//         __evars(split(#args, ',').begin(), args);                              \
//     }

// inline void __evars_begin(int line) { cerr << "#" << line << ": "; }
// template <typename T> inline void __evars_out_var(vector<T> val) {
//     cerr << arrStr(val, val.size());
// }
// template <typename T> inline void __evars_out_var(T *val) {
//     cerr << arrStr(val, 10);
// }
// template <typename T> inline void __evars_out_var(T val) { cerr << val; }
// inline void __evars(vector<string>::iterator it) { cerr << endl; }

// template <typename T, typename... Args>
// inline void __evars(vector<string>::iterator it, T a, Args... args) {
//     cerr << it->substr((*it)[0] == ' ', it->length()) << "=";
//     __evars_out_var(a);
//     cerr << "; ";
//     __evars(++it, args...);
// }
// //*****************************************************************************************************
// #define debug(x)                                                               \
//     { cerr << #x << " = " << x << endl; }
// #define mod 1000000007
// #define MAX 20000000
// #define test()                                                                 \
//     long long o;                                                               \
//     cin >> o;                                                                  \
//     while (o--)
// #define input(vec) for (unsigned int c = 0; c<vec.size(); cin>> vec[c++])
// #define output(vec, x)                                                         \
//     {                                                                          \
//         for (unsigned int c = 0; c < vec.size(); x << vec[c++] << ' ')         \
//             ;                                                                  \
//         x << endl;                                                             \
//     }
// #define sz(k) k.size()
// #define ln(s) s.length()
// #define pb push_back
// #define mp make_pair
// #define all(x) x.begin(), x.end()
// #define finc(i, x, y) for (__typeof(x) i = x; i < y; i++)
// #define fdec(i, x, y) for (__typeof(x) i = x; i > y; i--)
// #define fincp(itr, x)                                                          \
//     for (__typeof(x.begin()) itr = x.begin(); itr != x.end(); itr++)
// #define fdecp(itr, x) for (auto itr = x.end() - 1; itr != x.begin() - 1; itr--)
// #define dragonforce()                                                          \
//     ios_base::sync_with_stdio(false);                                          \
//     cin.tie(NULL);                                                             \
//     cout.tie(NULL);                                                            \
//     cerr.tie(NULL);
// #define PI (acos(-1.0))
// #define E 2.71828182845904523536
// #define by(x) [](const auto &a, const auto &b) { return a.x < b.x; }
// #define grsort() [](const auto &a, const auto &b) { return a > b; }
// #define F first
// #define S second
// #define mem(a, x) memset(a, x, sizeof(a))
// #define mnv(v) *min_element(v.begin(), v.end())
// #define mxv(v) *max_element(v.begin(), v.end())
// #define pr(x) cout << fixed << setprecision(x);
// template <class t = int> t get() {
//     t a;
//     std::cin >> a;
//     return a;
// }
// //************************************************************************************************************

// int main() {
//     int n,a;
//     cin>>n;
//     vi b(n);
//     input(b);
//     cin>>a;
//     vi temp(b);
//     for(size_t i = 0; i < a; i++)
//     {
//         temp[i]=b[i];
//     }
//     make_heap(temp.begin(),temp.end());




    
// }

// A C++ program to demonstrate common Binary Heap Operations
#include <climits>
#include <iostream>
using namespace std;

// Prototype of a utility function to swap two integers
void swap(int* x, int* y);

// A class for Min Heap
class MinHeap {
    int* harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
public:
    // Constructor
    MinHeap(int capacity);

    // to heapify a subtree with the root at given index
    void MinHeapify(int);

    int parent(int i) { return (i - 1) / 2; }

    // to get index of left child of node at index i
    int left(int i) { return (2 * i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2 * i + 2); }

    // to extract the root which is the minimum element
    int extractMin();

    // Decreases key value of key at index i to new_val
    void decreaseKey(int i, int new_val);

    // Returns the minimum key (key at root) from min heap
    int getMin() { return harr[0]; }

    // Deletes a key stored at index i
    void deleteKey(int i);

    // Inserts a new key 'k'
    void insertKey(int k);
    void findpos(int k)
    {
        int i = 0;
        while (k != harr[i]) {
            if (k > harr[i])
        }
    }
};

// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}

// Inserts a new key 'k'
void MinHeap::insertKey(int k)
{
    if (heap_size == capacity) {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }

    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    // Fix the min heap property if it is violated
    while (i != 0 && harr[parent(i)] < harr[i]) {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// Decreases value of key at index 'i' to new_val. It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val)
{
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] < harr[i]) {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// Method to remove minimum element (or root) from min heap
int MinHeap::extractMin()
{
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1) {
        heap_size--;
        return harr[0];
    }

    // Store the minimum value, and remove it from heap
    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;
    MinHeapify(0);

    return root;
}

// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void MinHeap::deleteKey(int i)
{
    decreaseKey(i, INT_MAX);
    extractMin();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i) {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

// A utility function to swap two elements
void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Driver program to test above functions
int main()
{
    // 	MinHeap h(11);
    // 	h.insertKey(3);
    // 	h.insertKey(2);
    // 	h.deleteKey(1);
    // 	h.insertKey(15);
    // 	h.insertKey(5);
    // 	h.insertKey(4);
    // 	h.insertKey(45);
    // 	cout << h.extractMin() << " ";
    // 	cout << h.getMin() << " ";
    // 	h.decreaseKey(2, 1);
    // 	cout << h.getMin();

    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int b;
    cin >> b;
    MinHeap h(b);
    for (int i = 0; i < b - 1; i++) {
        h.insertKey(a[i]);
    }

    for (int i = b - 1; i < n; i++) {
        h.insertKey(a[i]);
        cout << h.extractMin();
    }
    return 0;
}
