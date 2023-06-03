#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
#include <utility>

using namespace std;

int case_num;

void TEST(int n, int m, FILE *fp, mt19937 &rng) {
	vector<vector<int>> edges;
	string line;
	int u, v;

	edges.resize(n+1);
	line = to_string(n) + " ";
	line += to_string(m) + "\n";

	fputs(line.c_str(), fp);

	for (int j=0; j<m; ++j) {
		do {
			u = (rng() % n) + 1;
			v = (rng() % n) + 1;
		} while (u == v || find(edges[u].begin(), edges[u].end(), v) != edges[u].end());
		edges[u].push_back(v);
		line = to_string(u) + " ";
		line += to_string(v) + "\n";
		fputs(line.c_str(), fp);
	}
}

int main(int argc, char** argv) {
	int n, m;
	string line;

	case_num = atoi(argv[1]);
	random_device rd;
	mt19937 rng(rd());

	for (int i=1; i<=case_num; ++i) {
		string txt = "./myInput/myInput" + to_string(i) + ".txt";
		FILE *fp = fopen(txt.c_str(), "w");

		if (i <= case_num / 4) {
			n = 5; m = 7;
			TEST(n, m, fp, rng);
		}
		else {
			n = 10000; m = 100000;
			TEST(n, m, fp, rng);
		}
		fclose(fp);
	}
	return 0;
}
