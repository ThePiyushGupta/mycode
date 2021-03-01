#include <bits/stdc++.h>

#include "CircularQueue.cpp"
#include "utils.cpp"
using namespace std;

void rearrange2(vector<int> &shuffpos) {
	unordered_map<int, int> mymap;
	for (int c = 0; c < shuffpos.size(); ++c) mymap[shuffpos[c]] += 1;
	// dbgv(shuffpos);

	shuffpos.clear();

	vector<vector<int>> temp;
	for (auto &it : mymap) {
		temp.push_back({it.first, it.second});
	}

	sort(temp.begin(), temp.end(), [](vector<int> &a, vector<int> &b) {
		return a[1] > b[1];
	});

	int ct = 0;
	CircualarQueue q;
	int grpct = temp.size();

	while (ct < grpct && ct < ZONECT) {
		q.insert(ct++);
	}
	// cerr << "HERE2" << endl;

	while (ct != grpct) {
		Node *curr = q.curr;
		int k = curr->val;
		shuffpos.push_back(temp[k][0]);
		temp[k][1]--;
		if (temp[k][1] == 0) {
			curr->val = ct++;
		}
		q.advance();
	}
	int rem = grpct;
	// cerr << "HERE1" << endl;

	while (q.curr != NULL) {
		Node *curr = q.curr;
		int k = curr->val;
		// cerr << k << endl;
		shuffpos.push_back(temp[k][0]);

		temp[k][1]--;
		// cerr << "HERE3" << endl;

		if (temp[k][1] == 0) {
			rem--;
			q.remove();
		} else
			q.advance();
	}
	// cerr << "HERE2" << endl;
}

void rearrange(vector<int> &shuffpos) {
	vector<vector<int>> temp;

	for (int c = 0; c < begg.size(); ++c) {
		temp.push_back({begg[c], endg[c], c});
	}
	sort(temp.begin(), temp.end(), [](vector<int> &a, vector<int> &b) {
		return a[1] - a[0] > b[1] - b[0];
	});

	int ct = 0;
	CircualarQueue q;

	while (ct < GRPCT && ct < ZONECT) {
		q.insert(ct++);
	}

	while (ct != GRPCT) {
		Node *curr = q.curr;
		int k = curr->val;
		shuffpos.push_back(temp[k][2]);
		temp[k][0]++;
		if (temp[k][1] == temp[k][0]) {
			curr->val = ct++;
		}
		q.advance();
	}

	int rem = GRPCT;
	while (q.curr != NULL) {
		Node *curr = q.curr;
		int k = curr->val;
		shuffpos.push_back(temp[k][2]);

		temp[k][0]++;
		if (temp[k][1] == temp[k][0]) {
			rem--;
			q.remove();
		} else
			q.advance();
	}
	// dbgv(shuffpos);
}

void schedule(float alpha, float beta, vector<int> shuffpos) {
	// dbgv(shuffpos);
	reloadInputs();
	Alpha = alpha, Beta = beta;

	vector<int> res(APPSCT);

	// dbgv(shuffpos);

	for (int c = 0; c < APPSCT; ++c) {
		// cerr << c << ' ';
		res[begg[shuffpos[c]]] = schedule(begg[shuffpos[c]], res);
		begg[shuffpos[c]]++;
	}
	// cerr << endl;
	// dbgv(res);
	cerr << calcCV() << ' ' << calcNS(res) << endl;
}

void scheduleRR(float alpha, float beta) {
	reloadInputs();
	Alpha = alpha, Beta = beta;
	vector<int> shuffpos;

	vector<int> res(APPSCT);
	int zptr = 0;
	for (int c = 0; c < APPSCT; ++c) {
		res[begg[shuffpos[c]]] = zptr;
		begg[shuffpos[c]]++;
		zc[zptr]++;
		zptr = (zptr + 1) % ZONECT;
	}
	cerr << calcCV() << ' ' << calcNS(res) << endl;
}

void scheduleNew(float alpha, float beta) {
	reloadInputs();
	Alpha = alpha, Beta = beta;
	vector<int> shuffpos;

	// rearrange
	rearrange(shuffpos);

	vector<int> res(APPSCT);

	for (int c = 0; c < APPSCT; ++c) {
		// cerr << c << ' ';
		res[begg[shuffpos[c]]] = schedule(begg[shuffpos[c]], res);
		begg[shuffpos[c]]++;
	}
	// dbgv(res);
	cerr << calcCV() << ' ' << calcNS(res) << endl;
}

void scheduleNewOnline(float alpha, float beta, vector<int> shuffpos) {
	reloadInputs();
	Alpha = alpha, Beta = beta;
	vector<int> res(APPSCT);

	for (int c = 0; c < APPSCT; c += BATCHSZ) {
		vector<int> temp;
		for (int r = 0; r < BATCHSZ && r + c < APPSCT; ++r) {
			temp.push_back(shuffpos[c + r]);
		}

		rearrange2(temp);

		// cerr << "HERE" << endl;
		for (int r = 0; r < BATCHSZ && r + c < APPSCT; ++r) {
			res[begg[temp[r]]] = schedule(begg[temp[r]], res);
			begg[temp[r]]++;
		}
	}
	// cerr << "HERE" << endl;

	cerr << calcCV() << ' ' << calcNS(res) << endl;
}

int main() {
	// system("./TestDataGenerator");
	// cerr << fixed << setprecision(4);
	// cout << fixed << setprecision(4);

	vector<int> shuffpos;
	reloadInputs();

	for (int c = 0; c < begg.size(); ++c) {
		for (int r = begg[c]; r < endg[c]; ++r) shuffpos.push_back(c);
	}

	vector<int> alpha = {1};
	// vector<int> alpha = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 1000};
	for (auto &it : alpha) {
		cerr << "Paper's Algo: ";
		shuffle_array(shuffpos);
		schedule(it, 1.0, shuffpos);

		cerr << "Our Algo: ";
		scheduleNew(it, 1.0);

		cerr << "Onl Algo: ";
		scheduleNewOnline(it, 1.0, shuffpos);
		cerr << endl;
	}
	return 0;
}
