#include<bits/stdc++.h>

const int N=2010;
int t,k,n,m;

int main(){
	std::cin>>t>>k;
	for(int i=0;i<N;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%k;
	}
	for(int i=0;i<N;i++)
		for(int j=0;j<=i;j++){
			s[i][j]=c[i][j]%k==0;
			if(i)s[i][j]+=s[i-1][j];
			if(j)s[i][j]+=s[i][j-1];
			if(i&&j)s[i][j]-=s[i-1][j-1];
		}
	for(int i=0;i<t;i++){
		std::cin>>n>>m;
		std::cout<<s[n][m]<<std::endl;
	}
}