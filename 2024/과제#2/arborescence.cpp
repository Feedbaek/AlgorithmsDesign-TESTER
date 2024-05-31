#include <iostream>
#include <vector>
#include <stack>

#define WHITE 0
#define GREY 1
#define BLACK 2

using namespace std;

int visited[10001];  // visited[i] = i번 노드를 방문했는지 여부
int tree_num[10001];  // tree_num[i] = i번 노드를 루트로 하는 서브트리의 노드 개수
vector<int> edges[10002];  // edges[i] = i번 노드와 연결된 노드들

int node_number = 1;
int scc_number = 1;
int color[10002];
int low[10002];
int discover_time[10002];
int scc[10002];
int arborescence_root;
stack<int> discover_stack;

int strongComponent(int u) {
	color[u] = GREY;
	discover_time[u] = node_number++;
	low[u] = discover_time[u];
	discover_stack.push(u);

	for (int v : edges[u]) {
		if (color[v] == WHITE) {
			int ret = strongComponent(v);
			low[u] = min(low[u], ret);
		}
		else if (scc[v] == 0) {
			low[u] = min(low[u], discover_time[v]);
		}
	}

	if (low[u] == discover_time[u]) {
		int y = 0;
		do {
			y = discover_stack.top();
			discover_stack.pop();
			scc[y] = scc_number;
		} while (y != u);
		++scc_number;
	}
	color[u] = BLACK;

	return low[u];
}

void dfs(int node, int n) {
	visited[node] = GREY;
	tree_num[node] = 1;

	for (int i=0; i<edges[node].size(); ++i) {
		int next = edges[node][i];
		if (visited[next] == WHITE) {
			dfs(next, n);
			tree_num[node] += tree_num[next];
		} else if (visited[next] == BLACK) {
			tree_num[node] += tree_num[next];
		}
	}
	if (tree_num[node] == n) {
		arborescence_root = node;
	}
	visited[node] = BLACK;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		edges[a].push_back(b);
	}

	for (int i=1; i<=n; ++i) {  // 강한 연결 요소 찾기
		if (color[i] == WHITE) {
			strongComponent(i);
		}
	}

	for (int i=1; i<=n; ++i) {  // dfs로 가장 아보레센스 루트 하나 찾기
		if (visited[i] == WHITE) {
			dfs(i, n);
		}
	}

	int answer = 0;
	for (int i=1; i<=n; ++i) {  // 아보레센스 루트의 연결 성분들 찾기
		if (scc[i] == scc[arborescence_root]) {
			++answer;
		}
	}

	cout << answer << '\n';  // 정답 출력

	return 0;
}

