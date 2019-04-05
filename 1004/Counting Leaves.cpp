/*
给出父子节点关系，求每层叶子个数
此题规定根节点为01，故不用创建node结构和寻找根节点
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> v[100];
int book[100], maxdepth = -1;
void dfs(int index, int depth) {
	if (v[index].size() == 0) {//当节点为叶子结点时，给此节点确定层数
		book[depth]++;//每层叶子节点个数
		maxdepth = max(maxdepth, depth);//计算层数
		return;
	}
	for (int i = 0; i < v[index].size(); i++)
		dfs(v[index][i], depth + 1);//深度优先，遍历每条路径，孩子节点深度＋1
}
int main() {
	int n, m, k, node, c;
	scanf("%d %d", &n,&m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &node, &k);
		for (int j = 0; j < k; j++) {
			scanf("%d", &c);
			v[node].push_back(c);
		}
	}
	dfs(1, 0);//设置root节点为1
	printf("%d", book[0]);
	for (int i = 1; i <= maxdepth; i++)
		printf(" %d", book[i]);
	return 0;
}