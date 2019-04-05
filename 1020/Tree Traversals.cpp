/*
后续中序转层序，利用后序中序转前序:只需在转前序时加入参数index，和post[root一起保存在level
*/
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct node {
	int index, value;
};
bool cmp(node a, node b) {
	return a.index < b.index;
}
vector<int> post, in;
vector<node> level;
void pre_level(int root, int start, int end, int index) {
	if (start > end) return;
	int i = start;
	while (i < end&&in[i] != post[root]) i++;
	level.push_back({ index,post[root] });
	pre_level(root - (end - i + 1), start, i - 1, 2 * index + 1);//root - (end - i + 1):即为当前根结点-右子树的个数
	pre_level(root - 1, i + 1, end, 2 * index + 2);//root-1:后序右子树根节点
}
int main() {
	int n;
	scanf("%d", &n);
	post.resize(n);
	in.resize(n);
	for (int i = 0; i < n; i++) scanf("%d", &post[i]);
	for (int i = 0; i < n; i++) scanf("%d", &in[i]);
	pre_level(n - 1, 0, n - 1, 0);
	sort(level.begin(), level.end(), cmp);
	for (int i = 0; i < level.size(); i++) {
		if (i != 0) cout << " ";
		cout << level[i].value;
	}
	return 0;
}
