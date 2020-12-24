#include <bits/stdc++.h>
using namespace std;
#define ll long long

/*
    Function to calculate and return the short term
    energy of noise based on the assumption that the
    first 32000 samples are noise only.
*/
int calcThres(vector<int> &inp) {
	ll sum = 0, n = 0;
	for (int i = 0; i < 32000; ++i) {
		n = inp[i];
		sum += n * n;
	}
	return sum / 32000;
}

/*
    Reads input from input file "inp.txt" and stores in 
    an array.
    Subtracts the amplitude offset from each sample
*/
vector<int> readInput() {
	// declarations
	ifstream myFile;
	myFile.open("inp.txt");
	ll sum = 0, n;
	vector<int> ret;

	if (myFile.is_open()) {
		// extract sample from file and push to an array
		// calculate sum for offset calculation
		while (myFile >> n) {
			sum += n;
			ret.push_back(n);
		}
	} else
		cout << "Unable to open File\n";

	// calculate offset

	n = ret.size();
	sum /= n;

	// subtract offset from each sample
	for (auto &it : ret)
		it -= sum;

	return ret;
}

int main() {
	// read input into an arrray
	vector<int> inp = readInput();

	/*
        Declarations:
        sum = sum to calculate short term energy of blocks
        n = auxiliary variable to store aplitude of current sample
        prev = amplitude of previous sample
        zcc  = zero crossing count of current word
        nzcc = zero crossing count of current block
        zct = len ( number of samples ) of current word
        minSilEn = min short term enegy to start recognizing a word
    */

	ll sum = 0;
	int n, minSilEn = calcThres(inp) * 3, prev = 0, zcc = 0, nzcc = 0, zct = 0;

	//  for each sample after analyzing silence(32000 samples)
	for (int c = 32000; c < inp.size(); ++c) {
		n = inp[c];
		sum += n * n;

		// n*prev <0 => sample has crossed 0
		// => increae zero cross count of the block
		if (n * prev < 0)
			nzcc++;

		//  if a block gets completed then analyze it
		if (c % 320 == 0) {
			sum /= 320;

			// use short term energy to indicate word
			if (sum >= minSilEn) {
				// if word then change current word parameters
				zct += 320;
				zcc += nzcc;
			} else if (zct) {
				// check if the previous indicated word is actually a word
				// by checking if it is longer than 0.1 seconds
				if (zct > 1600) {
					double pr = zcc;
					pr /= zct;

					// check if the given word is YES or NO using zcr value
					if (pr > 0.14)
						cout << "YES" << endl;
					else
						cout << "NO" << endl;
				}
				// reset word variables  as current block is not a valid word
				zcc = zct = 0;
			}
			nzcc = sum = 0;
		}
		prev = n;
	}
}