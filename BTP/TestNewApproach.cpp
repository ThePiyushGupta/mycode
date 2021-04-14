#include <bits/stdc++.h>

#include "CircularQueue.cpp"
#include "utils.cpp"
using namespace std;

int BATCHSZ = 100;

void rearrange2(vector<int> &shuffpos) {
	unordered_map<int, vector<int>> mymap;

	for (int c = 0; c < shuffpos.size(); ++c) mymap[shuffpos[c] / 1000].push_back(shuffpos[c]);
	// dbgv(shuffpos);

	shuffpos.clear();

	vector<vector<int>> temp;
	for (auto &it : mymap) {
		temp.push_back({it.first, int(it.second.size())});
		reverse(it.second.begin(), it.second.end());
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

		shuffpos.push_back(temp[k][0]);
		temp[k][1]--;

		if (temp[k][1] == 0) {
			rem--;
			q.remove();
		} else
			q.advance();
	}

	for (int c = 0; c < shuffpos.size(); ++c) {
		int k = mymap[shuffpos[c]].back();
		mymap[shuffpos[c]].pop_back();
		shuffpos[c] = k;
	}
	// dbgv(shuffpos)
}
/*
Create an array G containing groups and sort based on decreasing group size
Create a circular queue C
Initialize order O
int ct = 0
while(ct<num(groups) && ct < num(zones)) 
	q.insert(ct)
	ct = ct + 1
while(ct != num(groups)) 
	insert a task from the task group at the front of the queue into O
	if no more tasks are left to be scheduled from the task group replace the task group with another task group
	advance head of C by 1
while(C is not empty)
	insert a task from the task group at the front of the queue into O
	if no more tasks are left to be scheduled from the task group remove the task group from C
	advance head of C by 1 
*/

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

void scheduleNewOnline(float alpha, float beta, vector<int> shuffpos, ofstream &myfile) {
	reloadInputs();
	Alpha = alpha, Beta = beta;
	vector<int> res(APPSCT);
	// cerr << BATCHSZ << endl;

	for (int c = 0; c < APPSCT; c += BATCHSZ) {
		vector<int> temp;
		for (int r = 0; r < BATCHSZ && r + c < APPSCT; ++r) {
			temp.push_back(shuffpos[c + r]);
		}

		rearrange2(temp);

		// cerr << "HERE" << endl;
		for (int r = 0; r < BATCHSZ && r + c < APPSCT; ++r) {
			// cerr << temp[r] << ' ';
			res[temp[r]] = schedule(temp[r], res);
			// begg[temp[r]]++;
		}
	}

	// for (int c = 0; c < shuffpos.size(); ++c) {
	// 	cerr << shuffpos[c] << ' ';
	// 	res[shuffpos[c]] = schedule(shuffpos[c], res);
	// }

	// cerr << "HERE" << endl;
	myfile << calcCV() << ' ' << calcNS(res) << endl;
}

int main(int argc, char *argv[]) {
	// system("./TestDataGenerator");
	// cerr << fixed << setprecision(4);
	// cout << fixed << setprecision(4);

	vector<int> shuffpos;
	reloadInputs();
	cerr << "INPUT RELOADED"
		 << "\n";

	// for (int c = 0; c < begg.size(); ++c) {
	// 	for (int r = begg[c]; r < endg[c]; ++r) shuffpos.push_back(c);
	// }

	vector<int> alpha = {1};
	shuffle_array(shuffpos);
	// cerr << "INPUT RELOADED" << endl;
	// dbgv(shuffpos);
	// cerr << endl;
	// dbgv(et);

	// schedule(1, 1.0, shuffpos);
	// schedule(1, 1.0, shuffpos);

	// vector<int> alpha = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};

	// for (int zc = 1; zc < 20; ++zc) {
	int zc = 10;
	// cerr << argc << endl;

	if (argc != 1) zc = stoi(argv[1]);
	ZONECT = zc;
	ofstream myfile;
	// cerr << "HERE" << endl;
	myfile.open("output" + to_string(zc) + ".txt");

	for (int c = 1; c <= 100; ++c) {
		BATCHSZ = c;
		// cerr << "Paper's Algo: ";
		// schedule(1, 1.0, shuffpos);

		// cerr << "Our Algo: ";
		// scheduleNew(1, 1.0);

		myfile << c << ' ';
		scheduleNewOnline(1, 1.0, shuffpos, myfile);

		// cerr << "Simple RR Algo: ";
		// scheduleRR(it, 1.0);
		// cerr << endl;
	}
	myfile.close();
	// }

	return 0;
}
