#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int inf = 999999999;
int cmax, n, sp, m;
int minNeed = inf, minBack = inf;
int e[510][510], dis[510], weight[510];
bool visit[510];
vector<int> pre[510];
vector<int> path, temppath;
void dfs(int v) {
	temppath.push_back(v);
	if (v == 0) {
		int need = 0, back = 0;
		for (int i = temppath.size() - 1; i >= 0; i--) {
			int id = temppath[i];
			if (weight[id] = 0) {
				back += weight[id];
			}
			else {
				if (back > (0 - weight[id])) {
					back += weight[id];
				}
				else {
					need += ((0 - weight[id]) - back);
					back = 0;
				}
			}
		}
	}
}