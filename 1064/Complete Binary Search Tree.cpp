#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
vector<int> in, level;
void levelOrder(int start, int end, int index) {
	if (start > end) return;
	int n = end - start + 1;
	int l = log(n + 1) / log(2);//除了最后一层的层数
	int level = n - (pow(2, l) - 1);//最后一层叶子节点数
	int root = start + (pow(2, l - 1) - 1) + min((int)pow(2, l - 1), level);
	level[index] = in[root];
	levelOrder(start, root - 1, 2 * index + 1);
	levelOrder(root + 1, end, 2 * index + 2);
}
int main() {
	int n;
	scanf("%d", &n);
	in.resize(n);
	level.resize(n);
	for (int i = 0; i < n; i++)
		scanf("%d", &in[i]);
	sort(in.begin(), in.end());
	levelOrder(0, n - 1, 0);
	printf("%d", level[0]);
	for (int i = 1; i < n; i++)
		printf(" %d", level[i]);
	return 0;
}