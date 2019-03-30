#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct node {
	int v;
	node *left, *right;
};
node* build(node *root, int v) {
	if (root == NULL) {
		root = new node();
		root->v = v;
		root->left = root->right = NULL;
	}
	else if (v <= root->v)
		root->left = build(root->left, v);
	else
		root->right = build(root->right, v);
	return root;
}
vector<int> num(10000);
int maxDepth = -1;
void dfs(node *root, int depth) {
	if (root == NULL) {
		maxDepth = max(depth, maxDepth);
		return;
	}
	num[depth]++;
	dfs(root->left, depth + 1);
	dfs(root->right, depth + 1);
}
int main() {
	int n, t;
	scanf("%d", &n);
	node *root = NULL;
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		root = build(root, t);
	}
	dfs(root, 0);
	printf("%d+ %d = %d", num[maxDepth - 1], num[maxDepth - 2], num[maxDepth - 1] + num[maxDepth - 2]);
	return 0;
}