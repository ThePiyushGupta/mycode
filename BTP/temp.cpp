#include <bits/stdc++.h>
using namespace std;
#define APPSCT 100
#define CONTSCT 6

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

class Container {
public:
	int cpu, ram, disk, bw, id;
	Container() {
		cpu = 1000;
		ram = 1000;
		disk = 1000;
		bw = 1000;
		id = 1;
	}
};

vector<int> scheduleOpt(vector<Application> apps, vector<Container> conts) {
	vector<int> res(apps.size(), -1);
	sort(apps.begin(), apps.end(), [](auto &a, auto &b) { return a.bw < b.bw; });
	multiset<Container, decltype([](auto &a, auto &b) { return a.bw < b.bw; })> contord;

	for (auto &cont : conts) {
		contord.insert(cont);
	}
	for (auto &app : apps) {
		Container temp;
		temp.bw = app.bw;
		auto pos = contord.lower_bound(temp);
		if (pos == contord.end()) {
			return res;
		}
		while (pos != contord.end()) {
			if ((*pos).cpu >= app.cpu && (*pos).ram >= app.ram && (*pos).disk >= app.disk) {
				res[app.id] = (*pos).id;
				break;
			}
			pos = next(pos);
		}
		if (pos != contord.end()) {
			temp = *pos;
			contord.erase(pos);
			temp.bw -= app.bw;
			contord.insert(temp);
		}
	}
	return res;
}

vector<int> roundRobin(vector<Application> &apps, vector<Container> &conts) {
	vector<int> res(apps.size());

	int ct = 0;
	for (int c = 0; c < apps.size(); ++c) {
		res[c] = ct++;
		ct %= conts.size();
	}
	return res;
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

	vector<Container> conts(CONTSCT);
	for (int c = 0; c < CONTSCT; ++c) {
		conts[c].id = c;
	}
	cout << "CONTAINERS GENERATED" << endl;

	vector<int> res = scheduleOpt(apps, conts);
	cout << "OPTIMIZED PATTERN GENERATED" << endl;
	for (auto &it : res) cout << it << ' ';
	cout << endl;

	vector<int> res2 = roundRobin(apps, conts);
	cout << "NON-OPTIMIZED PATTERN GENERATED" << endl;

	for (auto &it : res2) cout << it << ' ';
	cout << endl;

	vector<int> oct(CONTSCT), ct(CONTSCT);

	for (auto &app : apps) {
		oct[res[app.id]] += app.bw;
	}
	for (auto &app : apps) {
		ct[res2[app.id]] += app.bw;
	}

	for (int c = 0; c < CONTSCT; ++c) {
		cout << oct[c] << ' ';
	}

	cout << endl;

	for (int c = 0; c < CONTSCT; ++c) {
		cout << ct[c] << ' ';
	}
	cout << endl;
}