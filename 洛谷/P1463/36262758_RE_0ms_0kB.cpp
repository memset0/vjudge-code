// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int read() {
	int x = 0; bool m = 0; char c = getchar();
	while (!isdigit(c) && c != '-') c = getchar();
	if (c == '-') m = 1, c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (m) return -x; else return x;
}

int n;
int p[500]={1,2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,27720,45360,50400,55440,83160,110880,166320,221760,277200,332640,498960,554400,665280,720720,1081080,1441440,2162160,2882880,3603600,4324320,6486480,7207200,8648640,10810800,14414400,17297280,21621600,32432400,36756720,43243200,61261200,73513440,110270160,122522400,147026880,183783600,245044800,294053760,367567200,551350800,698377680,735134400,1102701600,1396755360,2001000000};

int main() {

	n = read();
	for (int i = 1; true; i++)
		if (p[i] > n)
			printf("%d\n", p[i - 1]);
	
	return 0;
}