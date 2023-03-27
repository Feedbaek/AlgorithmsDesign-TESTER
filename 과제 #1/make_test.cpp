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
#include <experimental/filesystem>
#define EASY 9
#define HARD 999

using namespace std;

int case_num;

struct DisjointSet {
	vector<int> parent, rank;

	DisjointSet(int n) {
		parent.resize(n);
		rank.resize(n);
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			rank[i] = 0;
		}
	}

	int find(int x) {
		if (parent[x] != x)
			parent[x] = find(parent[x]);
		return parent[x];
	}

	void merge(int x, int y) {
		int px = find(x), py = find(y);
		if (rank[px] > rank[py])
			parent[py] = px;
		else {
			parent[px] = py;
			if (rank[px] == rank[py])
				rank[py]++;
		}
	}
};

int main(int argc, char** argv) {
	int n, val;

	case_num = atoi(argv[1]);
	random_device rd;
	mt19937 rng(rd());

	for (int i=1; i<=case_num; ++i) {
		string txt = "./myinput/myinput" + to_string(i) + ".txt";
		FILE *fp = fopen(txt.c_str(), "w");

		if (i <= case_num / 3)
			n = rng() % EASY;
		else
			n = HARD;
		++n;

		fputs((to_string(n) + "\n").c_str(), fp);

		vector<pair<int, int> > edges;
		// 연결된 간선이 없는 상태에서 랜덤 그래프 생성
		for (int i = 1; i < n; i++) { // 1부터 시작
			for (int j = i+1; j <= n; j++) { // i보다 큰 번호의 정점과만 연결
				edges.push_back(make_pair(i, j)); // 첫 번째 정점이 더 작은 번호를 가지도록 함
			}
		}

		shuffle(edges.begin(), edges.end(), rng);

		DisjointSet dsu(n+1);
		for (auto e : edges) {
			int u = e.first, v = e.second;
			if (dsu.find(u) != dsu.find(v)) {
				// 랜덤 가중치 부여
				int weight = rng() % 100001 - 50000;
				string str = to_string(u) + " " + to_string(v) + " " + to_string(weight) + "\n";
				fputs(str.c_str(), fp);
				dsu.merge(u, v);
			}
		}
		fclose(fp);
	}
	return 0;
}
