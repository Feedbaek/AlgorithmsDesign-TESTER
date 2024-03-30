#include <iostream>

using namespace std;

int visited[100001];

int main() {
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, u, v;
	cin >> n;


	for (int i=0; i<n-1; ++i) {
		cin >> u >> v;
		if (u > v) {
			int temp = u;
			u = v;
			v = temp;
		}

	}
	return 0;
}
