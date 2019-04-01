#include<cstdio>
#include<vector>
#include<stack>
#include<cstring>
using namespace std;
vector<int> pre, in, post, value;
void postOrder(int root, int start, int end) {
	if (start > end) return;
	int i = start;
	while (i < end&&in[i] != pre[root]) i++;
	postOrder(root + 1, start, i - 1);
	postOrder(root + 1 + i - start, i + 1, end);
	post.push_back(pre[root]);
}
int main() {
	int n;
	scanf("%d", &n);
	char str[5];
	stack<int> s;
	int key = 0;
	//while (~scanf("%s", str)) {
	for (int i = 0; i < 2 * n; i++) {
		scanf("%s", str);
		if (strlen(str) == 4) {
			int num;
			scanf("%d", &num);
			value.push_back(num);
			pre.push_back(key);
			s.push(key++);
		}
		else {
			in.push_back(s.top());
			s.pop();
		}
	}
//	}
	postOrder(0, 0, n - 1);
	printf("%d", value[post[0]]);
	for (int i = 1; i < n; i++) {
		printf(" %d", value[post[i]]);
	}
	return 0;
}