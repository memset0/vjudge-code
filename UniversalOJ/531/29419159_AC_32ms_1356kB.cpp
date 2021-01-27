#include"lcs.h"
#include<bits/stdc++.h>
using namespace std;
const int N=207;
int p[N],w[N],s[N][N];
inline bool cmp(int a,int b){
	w[0]=a,w[1]=b;
	if(!s[a][b]) s[a][b]=get_lcs(2,w); s[b][a]=3^s[a][b];
	if(s[a][b]==2) return 1; return 0;
}
void find_permutation(int n, int res[]){
	for(int i=0;i<n;i++) p[i]=i+1;
	sort(p,p+n,cmp);
	for(int i=0;i<n;i++) res[i]=p[i];
}