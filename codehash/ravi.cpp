#include <bits/stdc++.h>
#define ll long long int
#define f(n) for (ll i = 0; i < n; i++)
#define fn(n) for (ll j = 0; j < n; j++)
#define d(n) for (ll i = n; i >= 0; i--)
#define P 1000000007
#define PHI 1.618033988
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define IP                            \
	ios_base::sync_with_stdio(false); \
	cin.tie(NULL);
using namespace std;

ll getlib(int book, map<ll, vector<ll>> &bookinlib, map<ll, vector<ll>> &infolib, int libs) {
	ll libno = -1;
	ll scan = LONG_MAX;
	for (ll i = 0; i < libs; i++) {
		for (ll j = 0; j < bookinlib[i].size(); j++) {
			if (bookinlib[i][j] == book) {
				if (scan > infolib[i][1]) {
					libno = i;
				}
			}
		}
	}
	return libno;
}

int main() {
	ll book, libs, scan;
	cin >> book;
	cin >> libs;
	cin >> scan;

	ll count = 0;

	vector<pair<ll, ll>> scores(book);
	map<ll, ll> score;
	for (ll i = 0; i < book; i++) {
		ll x;
		cin >> x;
		score[i] = x;
		scores.push_back(make_pair(x, i));
	}
	reverse(scores.begin(), scores.end());

	vector<bool> bookchecked;
	for (ll i = 0; i < book; i++) {
		bookchecked.push_back(false);
	}
	vector<bool> libchecked;
	for (ll i = 0; i < libs; i++) {
		libchecked.push_back(false);
	}

	map<ll, vector<ll>> bookinlib;
	map<ll, vector<ll>> infolib;
	for (ll i = 0; i < libs; i++) {
		for (ll j = 0; j < 3; j++) {
			ll x;
			cin >> x;
			infolib[i].push_back(x);
		}
		vector<pair<ll, ll>> dummy;
		for (ll j = 0; j < infolib[i][0]; j++) {
			ll x;
			cin >> x;
			dummy.push_back(make_pair(score[x], x));
		}
		reverse(dummy.begin(), dummy.end());
		for (ll j = 0; j < infolib[i][0]; j++) {
			bookinlib[i].push_back(dummy[j].second);
		}
	}
	string s = "";

	for (ll i = 0; i < book; i++) {
		if (bookchecked[scores[i].second] == false) {
			ll libno = getlib(scores[i].second, bookinlib, infolib, libs);
			if (libno == -1) {
				break;
			} else {
				count++;
				s = s + to_string(libno) + " ";
				ll leftdays = scan - infolib[libno][1];
				ll totalbooks = leftdays * infolib[libno][2];
				totalbooks = min(totalbooks, infolib[libno][0]);
				s = s + to_string(totalbooks) + "\n";
				for (int j = 0; j < totalbooks; j++) {
					s = s + to_string(bookinlib[libno][j]) + " ";
					bookchecked[bookinlib[libno][j]] = true;
				}
				s = s + "\n";
			}
		}
	}
	cout << count << endl;
	cout << s << endl;
	return 0;
}