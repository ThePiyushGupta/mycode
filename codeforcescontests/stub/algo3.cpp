#include <bits/stdc++.h>
using namespace std;
#define APPSCT 10
#define ZONECT 2
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
		cpu = 1000;
		ram = 1000;
		disk = 1000;
		bw = 1000;
		id = 1;
		apps = 0;
	}
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
	float zbar = (1.0 + pos) / ZONECT;
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
			cout << fm << ' ';
		}
		cout << pos << ' ' << endl;
		if (pos != -1) {
			res[c] = pos;
			zones[pos].apps++;
		}
	}
	return res;
}
float calcCVsimp(vector<Zone> &zones) {
	float zbar = (APPSCT) / ZONECT;
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
	pr(2);

	D[3][0] = 1;
	D[2][1] = 1;
	D[4][3] = 1;
	D[5][4] = 1;
	D[6][5] = 1;
	D[7][6] = 1;
	D[8][7] = 1;
	D[9][8] = 1;

	// D[10][9] = 1;
	// D[11][10] = 1;

	// for (int c = 0; c < APPSCT; ++c) {
	// 	int t = rand();
	// 	t %= (6 * c) / 10 + 1 + c / 2;
	// 	if (t < c) D[c][t] = 1;
	// }

	// now Try scheduling
	// vector<int> beta = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 1000};
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
		// pr(2);
		float ns = (sum - optsum) * 100.0 / sum;
		cout << cv << ',' << ns << endl;
	}
	cout << endl;
	for (auto &zone : zones) zone.apps = 0;
	vector<int> res = scheduleOpt(apps, zones, 1, 3);

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
	cout << sum << ' ' << optsum << endl;
	float ns = (sum - optsum) * 100.0 / sum;
	cout << cv << ',' << ns << endl;
}