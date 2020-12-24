#include <bits/stdc++.h>
using namespace std;

string transform(string &s) {
	string ret = "@";
	for (auto &it : s) ret += "#", ret += it;
	return ret += "#$";
}

void manachers(string o) {
	string s = transform(o);
	int c = 0, r = 0;
	vector<int> p(s.size());
	for (int i = 1; i < s.size() - 1; ++i) {
		int imirror = c - (i - c);
		if (r > i) p[i] = min(r - i, p[imirror]);

		while (s[i + p[i] + 1] == s[i - p[i] - 1]) p[i]++;

		if (i + p[i] > p[c]) {
			c = i;
			r = c + p[i];
		}
	}
	cout << s << endl;
	for (auto &it : p) cout << it;
	cout << endl;

	int maxPalindrome = 0;
	int centerIndex = 0;

	for (int i = 1; i < s.size() - 1; i++) {
		if (p[i] > maxPalindrome) {
			maxPalindrome = p[i];
			centerIndex = i;
		}
	}

	cout << maxPalindrome << "\n";
	cout << o.substr((centerIndex - 1 - maxPalindrome) / 2, maxPalindrome) << endl;
}

int main() {
	string s;
	cin >> s;
	manachers(s);
}