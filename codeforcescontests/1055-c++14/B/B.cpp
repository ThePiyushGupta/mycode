#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
void findres(vector<int> &, int, int);
queue<pair<int, int>> l, r, ltemp, rtemp, emptyqueue;
vector<int> res;

int main() {
    // obtain input in a vector and sort it
    int n;
    vector<int> a;
    while (cin >> n) {
        a.push_back(n);
    }

    sort(a.begin(), a.end());
    n = a.size();

    // add initial elements to the queues
    int k = n, pos;
    pos = k / 2;
    res.push_back(a[pos]);

    if (pos > 0) l.push({0, pos});
    if (n > pos + 1) r.push({pos + 1, n});
    pair<int, int> t;

    while (!l.empty() || !r.empty()) {
        if (!l.empty()) {
            t = l.front();
            findres(a, t.first, t.second);
            l.pop();
        }

        else if (!r.empty()) {
            t = r.front();
            findres(a, t.first, t.second);
            r.pop();
        }

        if (r.empty() && l.empty()) {
            l = ltemp;
            ltemp = emptyqueue;
            r = rtemp;
            rtemp = emptyqueue;
        }
    }

    for (int i = 0; i < res.size(); i++) cout << res[i] << ' ';
}

void findres(vector<int> &a, int begin, int end) {
    int k = end - begin, pos;
    pos = begin + k / 2;
    res.push_back(a[pos]);

    if (pos > begin) ltemp.push({begin, pos});
    if (end > pos + 1) rtemp.push({pos + 1, end});
}
