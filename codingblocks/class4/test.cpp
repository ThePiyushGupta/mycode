#include <bits/stdc++.h>
using namespace std;

int a[100005], n, t;
int sum = 0;
bool check(int k) {
	int sum = 0, j = 0;
	for (int i = 0; i < n; i++) {
		sum += a[i];
		if ( + 1 == k) {
			cerr << sum << ' ' << t << ' ' << k
				 << endl;
			if (sum <= t) return true;
			sum -= a[j];
			j++;
		}
	}
	cerr << endl;
	return false;
}

int main() {
	cin >> n;
	cin >> t;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	int l = 0;
	int h = n - 1;
	cout << ' ' << l << ' ' << h << endl;

	while (l <= h) {
		int mid = (l + h) / 2;
		if (check(mid)) {
			l = mid + 1;
		} else {
			h = mid - 1;
		}
		cout << mid << ' ' << l << ' ' << h << endl;
	}

	if (check(l)) {
		cout << l;
	} else {
		cout << l - 1;
	}
}