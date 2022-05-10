#include <bits/stdc++.h>
#define MAXN 100001
using namespace std;
int n, m, a[MAXN];
struct P {
	int left, right, mid, lazy, value;
} p[MAXN * 4]; //定义
void build(int root, int left, int right) {
	p[root].left = left;
	p[root].right = right;
	p[root].value = 0;
	if (left == right) return ;
	int mid = p[root].mid = (left + right) >> 1;
	build(root << 1, left, mid);
	build((root << 1) + 1, mid + 1, right);
} //建树
void pushdown(int root, int value) {
	//由于是整条线段所以没有必要传递左指针和右指针
	p[root].lazy += value; //注意不是=（等于）
	p[root].value += value * (p[root].right - p[root].left + 1);
}
void add(int root, int left, int right, int value) {
	if (p[root].left == left && p[root].right == right) {
		//整条线段都需要覆盖
		pushdown(root, value); //去打lazy tag
		return ;
	}
	p[root].value += value * (right - left + 1);
	if (right <= p[root].mid) add(root * 2, left, right, value);
	else if (left > p[root].mid) add(root * 2 + 1, left, right, value);
	else {
		add(root * 2, left, p[root].mid, value);
		add(root * 2 + 1, p[root].mid + 1, right, value);
	}
} //修改
int find(int root, int left, int right) {
	if (p[root].lazy) {
		//发现lazy tag
		pushdown(root * 2, p[root].lazy); //给左孩子打上
		pushdown(root * 2 + 1, p[root].lazy); //给右孩子打上
		p[root].lazy = 0; //清除lazy tag
	}
	if (left == p[root].left && right == p[root].right) return p[root].value;
	if (right <= p[root].mid) return find(root * 2, left, right);
	else if (left > p[root].mid) return find(root * 2 + 1, left, right);
	else return find(root * 2, left, p[root].mid) + find(root * 2 + 1, p[root].mid + 1, right);
} //查询
int main() {
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		add(1, i, i, a[i]);
	} //建树
	int k, x, y, z;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &k);
		if (k == 1) {
			scanf("%d%d%d", &x, &y, &z);
			add(1, x, y, z);
		} else {
			scanf("%d%d", &x, &y);
			printf("%d\n", find(1, x, y));
		}
	}
	return 0;
}