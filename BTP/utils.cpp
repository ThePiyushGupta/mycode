#include <bits/stdc++.h>

#include "constants.h"
#define APPSCT D.size()
#define dbgv(v)                           \
	for (auto &it : v) cerr << it << ' '; \
	cerr << endl;
using namespace std;

vector<vector<int>> D;	// Dependency matrix
vector<vector<int>> T;	// Transport Matrix
vector<int> begg, endg;
vector<int> zc;
float nf = ZONECT * ZONECT * 100 - ZONECT * 90;
float Alpha, Beta;

void genT() {
	zc.resize(ZONECT);
	T.resize(ZONECT, vector<int>(ZONECT, 100));
	for (int c = 0; c < ZONECT; ++c) T[c][c] = 10;
}

void shuffle_array(vector<int> &foo) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(foo.begin(), foo.end(), default_random_engine(seed));
}

float calcNS(vector<int> &res) {
	float s1 = 0, s2 = 0;
	for (int r = 0; r < APPSCT; ++r) {
		for (int c = 0; c < D[r].size(); ++c) {
			s1 += T[res[r]][res[D[r][c]]];
			s2 += T[r % ZONECT][D[r][c] % ZONECT];
		}
	}
	float ns = (s2 - s1) * 100.0 / s2;
	return ns;
}

void loadAppsData() {
	ifstream myfile;

	myfile.open("AppsData.txt");
	int grpct, len, temp;

	myfile >> grpct;
	endg = {0};

	for (int c = 0; c < grpct; ++c) {
		myfile >> len;
		begg.push_back(endg.back());
		endg.push_back(endg.back() + len);
	}
	endg.erase(endg.begin());

	myfile >> temp;
	D.resize(temp);

	for (int r = 0; r < D.size(); ++r) {
		int id, ct = 0;
		myfile >> id >> ct;
		for (int c = 0; c < ct; ++c) {
			myfile >> temp;
			D[id].push_back(temp);
		}
	}
}

void reloadInputs() {
	D.clear(), T.clear(), begg.clear(), endg.clear(), zc.clear();
	loadAppsData();
	genT();
}

float calcCV() {
	float zbar = (APPSCT + 1) / ZONECT;
	float fac = zbar;
	float sum = 0;
	for (auto &zone : zc) {
		sum += (zone - zbar) * (zone - zbar);
	}
	return sqrt(sum / ZONECT) / fac;
}

float calcCV(int pos, int z) {
	float zbar = (pos + 1.0) / ZONECT;
	float fac = sqrt(ZONECT) * zbar;
	float sum = 0;
	for (auto &zone : zc) {
		sum += (zone - zbar) * (zone - zbar);
	}
	sum = sum - (zc[z] - zbar) * (zc[z] - zbar) + (zc[z] + 1 - zbar) * (zc[z] + 1 - zbar);

	return sqrt(sum) / fac;
}

float calcTR(vector<int> &res, int i, int z) {
	float sum = 0;
	for (auto &it : D[i]) {
		sum += T[z][res[it]];
	}
	return sum / nf;
}

int schedule(int pos, vector<int> &res) {
	float minfm = FLT_MAX;
	int ret = -1;
	for (int z = 0; z < ZONECT; ++z) {
		if (zc[z] == MAXZONECT) continue;
		float tr = calcTR(res, pos, z);
		float cv = calcCV(pos, z);
		float fm = (Alpha * tr + Beta * cv) / (Alpha + Beta);
		if (fm < minfm) minfm = fm, ret = z;
	}
	zc[ret]++;
	return ret;
}