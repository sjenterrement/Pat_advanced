#include<iostream>
#include<vector>
using namespace std;
int e[210][210];
int main() {
	int nv, ne, m, ta, tb, k;
	scanf("%d %d", &nv, &ne);
	for (int i = 0; i < nv; i++) {
		scanf("%d %d", &ta, &tb);
		e[ta][tb] = e[tb][ta] = 1;
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &k);
		vector<int> v(k);
		int hash[210] = { 0 }, isClique = 1, isMaximal = 1;
		for (int j = 0; j < k; j++) {
			scanf("%d", &v[j]);
			hash[v[j]] = 1;
		}
		for (int j = 0; j < k; j++) {
			if (isClique == 0)
				break;
			for (int l = 0; l < k; l++) {
				if (e[v[j]][v[l]] == 0) {
					isClique = 0;
					printf("Not a Clique");
					break;
				}
			}
		}
		if (isClique == 0)
			continue;
		for (int j = 1; j <= k; j++) {
			if (hash[j] == 0) {
				for (int l = 0; l < k; l++) {
					if (e[v[l]][v[j]] == 0)
						break;
					if (l == k - 1)
						isMaximal = 0;
				}
			}
			if (isMaximal == 0) {
				printf("Not Maximal\n");
				break;
			}
		}
		if (isMaximal == 1)
			printf("Yes\n");
	}
	return 0;
}