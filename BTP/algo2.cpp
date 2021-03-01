#include <bits/stdc++.h>
using namespace std;
#define APPSCT 2600
#define ZONECT 10
#define BATCHCT 8
// #define MXAPPS 500
#define pr(x) cout << fixed << setprecision(x);

class Application {
public:
	int cpu, ram, disk, bw, id;
	Application() {
		cpu = 100;
		ram = 100;
		disk = 100;
		id = 1;
		bw = 100;
	}
};

class Zone {
public:
	int cpu, ram, disk, bw, id, apps;
	Zone() {
		cpu = 10000;
		ram = 10000;
		disk = 10000;
		bw = 10000;
		id = 1;
		apps = 0;
	}
};

struct minBatch {
	vector<Application> apps;
	float fm;
	vector<int> res;
	vector<Zone> zones;
};

vector<vector<int>> T, D;
float nf = ZONECT * ZONECT * 100 - ZONECT * 90;

float calctr(vector<int> &res, int i, int z) {
	float sum = 0;
	for (int k = 0; k < i; ++k) {
		sum += D[i][k] * T[z][res[k]];
	}
	return sum / nf;
}

float calcCV(int pos, int zapps, vector<Zone> &zones) {
	float zbar = (pos + 1.0) / ZONECT;
	float fac = sqrt(ZONECT) * zbar;
	float sum = 0;
	for (auto &zone : zones) {
		sum += (zone.apps - zbar) * (zone.apps - zbar);
	}
	sum = sum - (zapps - zbar) * (zapps - zbar) + (zapps + 1 - zbar) * (zapps + 1 - zbar);

	return sqrt(sum) / fac;
}

vector<int> scheduleOpt(vector<Application> apps, vector<Zone> &zones, int alpha, int beta) {
	vector<int> res(apps.size());
	for (int c = 0; c < apps.size(); ++c) {
		auto &app = apps[c];
		int pos = -1;
		float minfm = INT_MAX;
		for (int z = 0; z < zones.size(); ++z) {
			float tr = calctr(res, c, z);
			float CV = calcCV(c, zones[z].apps, zones);
			float fm = (alpha * tr + beta * CV) / (alpha + beta);
			if (fm < minfm) minfm = fm, pos = z;
		}
		if (pos != -1) {
			res[c] = pos;
			zones[pos].apps++;
		}
	}
	return res;
}

vector<int> scheduleOptBatch(vector<Application> apps, vector<Zone> &zones, int alpha, int beta) {
	vector<int> res(apps.size());
	for (int c = 0; c < apps.size(); c += BATCHCT) {
		// cerr << c << endl;
		int end = min(c + BATCHCT, (int)apps.size());
		minBatch mn;
		mn.apps = apps;
		mn.fm = FLT_MAX;
		mn.zones = zones;
		mn.res = res;
		float minfm;
		int ct = 0;

		do {
			// if (ct++ % 10000 == 0)
			// 	cerr << ct << endl;
			for (int r = c; r < end; ++r) {
				auto &app = apps[r];
				int pos = -1;
				minfm = INT_MAX;

				for (int z = 0; z < zones.size(); ++z) {
					float tr = calctr(res, r, z);
					float CV = calcCV(r, zones[z].apps, zones);
					float fm = (alpha * tr + beta * CV) / (alpha + beta);
					if (fm < minfm) minfm = fm, pos = z;
				}
				if (pos != -1) {
					// cerr << "Here" << endl;
					res[r] = pos;
					zones[pos].apps++;
				}
			}
			if (minfm < mn.fm) {
				for (int r = c; r < end; ++r) {
					mn.res[r] = res[r];
					mn.apps[r] = apps[r];
				}
				mn.fm = minfm, mn.zones = zones;
			}
			for (int r = c; r < end; ++r) {
				zones[res[r]].apps--;
				res[r] = 0;
			}

		} while (next_permutation(apps.begin() + c, apps.begin() + end, [](Application &a, Application &b) {
			return a.id < b.id;
		}));
		ct = 0;
		for (int r = c; r < end; ++r) {
			res[r] = mn.res[r];
			apps[r] = mn.apps[r];
			// zones[r] = mn.zones[r];
			// zones[res[r]]
		}
		zones = mn.zones;
	}
	// cerr << 0 << endl;
	return res;
}

float calcCVsimp(vector<Zone> &zones) {
	float zbar = (APPSCT + 1) / ZONECT;
	float fac = zbar;
	float sum = 0;
	for (auto &zone : zones) {
		sum += (zone.apps - zbar) * (zone.apps - zbar);
	}
	return sqrt(sum / ZONECT) / fac;
}
int main() {
	srand(time(0));

	vector<Application> apps(APPSCT);
	for (int c = 0; c < APPSCT; ++c) {
		apps[c].id = c;
		apps[c].disk = 10 + rand() % 90;
		apps[c].ram = 10 + rand() % 90;
		apps[c].bw = 10 + rand() % 90;
		apps[c].cpu = 10 + rand() % 90;
	}
	cout << "APPS GENERATED" << endl;

	vector<Zone> zones(ZONECT);
	for (int c = 0; c < ZONECT; ++c) {
		zones[c].id = c;
	}
	cout << "CONTAINERS GENERATED" << endl;

	// generating traffic matrix
	T.resize(ZONECT, vector<int>(ZONECT, 100));
	for (int c = 0; c < ZONECT; ++c) T[c][c] = 10;

	D.resize(APPSCT, vector<int>(APPSCT, 0));

	// D[3][0] = 1;
	// D[2][1] = 1;
	// D[4][3] = 1;
	// D[5][4] = 1;
	// D[6][5] = 1;
	// D[7][6] = 1;

	for (int c = 0; c < APPSCT; ++c) {
		int t = rand();
		// t %= (6 * c) / 10 + 1 + c / 2;
		t %= max(c, 1);
		if (t < c) D[c][t] = 1;
	}

	// now Try scheduling
	// vector<int> beta = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	vector<int> beta = {1};
	for (int c = 0; c < beta.size(); ++c) {
		for (auto &zone : zones) zone.apps = 0;
		vector<int> res = scheduleOpt(apps, zones, beta[c], 1);

		float cv = calcCVsimp(zones);
		float optsum = 0, sum = 0;
		for (int i = 0; i < APPSCT; ++i) {
			for (int j = 0; j < APPSCT; ++j) {
				if (D[i][j]) {
					optsum += T[res[i]][res[j]];
					sum += T[i % ZONECT][j % ZONECT];
				}
			}
		}
		pr(2);
		float ns = (sum - optsum) * 100.0 / sum;
		cout << cv << ',' << ns << endl;
	}

	// cout << "TESTING NEW ONE" << endl;

	// for (int c = 0; c < beta.size(); ++c) {
	// 	for (auto &zone : zones) zone.apps = 0;
	// 	vector<int> res = scheduleOptBatch(apps, zones, beta[c], 1);
	// 	// cerr << 1 << endl;

	// 	float cv = calcCVsimp(zones);
	// 	// cerr << cv << endl;

	// 	float optsum = 0, sum = 0;
	// 	for (int i = 0; i < APPSCT; ++i) {
	// 		for (int j = 0; j < APPSCT; ++j) {
	// 			// cerr << apps[i].id << ' ' << apps[j].id << endl;

	// 			if (D[apps[i].id][apps[j].id]) {
	// 				// cerr << res[i] << ' ' << res[j] << endl;
	// 				optsum += T[res[i]][res[j]];
	// 				sum += T[i % ZONECT][j % ZONECT];
	// 			}
	// 		}
	// 	}

	// 	pr(2);
	// 	// cerr << 1 << endl;
	// 	float ns = (sum - optsum) * 100.0 / sum;
	// 	cout << cv << ',' << ns << endl;
	// }

	// for (auto &zone : zones) zone.apps = 0;
	// vector<int> res = scheduleOpt(apps, zones, 1, 0);

	// float cv = calcCVsimp(zones);
	// float optsum = 0, sum = 0;
	// for (int i = 0; i < APPSCT; ++i) {
	// 	for (int j = 0; j < APPSCT; ++j) {
	// 		if (D[i][j]) {
	// 			optsum += T[res[i]][res[j]];
	// 			sum += T[i % ZONECT][j % ZONECT];
	// 		}
	// 	}
	// }
	// pr(2);
	// float ns = (sum - optsum) * 100.0 / sum;
	// cout << cv << ',' << ns << endl;
}