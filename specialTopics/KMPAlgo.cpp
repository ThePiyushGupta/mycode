#include <bits/stdc++.h>
using namespace std;

// based on longest common prefix that is also a suffix

class kmppat {
public:
	int n;
	vector<int> pi;

	kmppat(string s) {
		n = s.size();
		pi = prefix_function(s);
		cout << s << endl;
		for (auto it : pi) cout << it;
		cout << endl;
	}

	vector<int> prefix_function(string s) {
		vector<int> pi(n);
		for (int c = 1; c < n; ++c) {
			int k = pi[c - 1];
			while (k && s[c] != s[k])
				k = pi[k - 1];
			if (s[c] == s[k]) k++;
			pi[c] = k;
		}
		return pi;
	}

	vector<int> toMatch(string s) {
		int k = 1;
		vector<int> res;
		for (int c = 0; c < s.size(); ++c) {
			while (k && s[c] != s[k - 1]) {
				k = pi[k - 1];
			}
			if (k == n) {
				res.push_back(c);
				k = pi[k - 1];
			}
			k++;
		}
		for (auto &it : res) cout << it << ' ';
		cout << endl;
		return res;
	}
};

int main() {
	string s, t;
	cin >> s;
	t = s;
	reverse(t.begin(), t.end());
	kmppat idk(s + "#" + t);
}