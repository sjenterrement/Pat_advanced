/*
�������ӽڵ��ϵ����ÿ��Ҷ�Ӹ���
����涨���ڵ�Ϊ01���ʲ��ô���node�ṹ��Ѱ�Ҹ��ڵ�
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> v[100];
int book[100], maxdepth = -1;
void dfs(int index, int depth) {
	if (v[index].size() == 0) {//���ڵ�ΪҶ�ӽ��ʱ�����˽ڵ�ȷ������
		book[depth]++;//ÿ��Ҷ�ӽڵ����
		maxdepth = max(maxdepth, depth);//�������
		return;
	}
	for (int i = 0; i < v[index].size(); i++)
		dfs(v[index][i], depth + 1);//������ȣ�����ÿ��·�������ӽڵ���ȣ�1
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
	dfs(1, 0);//����root�ڵ�Ϊ1
	printf("%d", book[0]);
	for (int i = 1; i <= maxdepth; i++)
		printf(" %d", book[i]);
	return 0;
}