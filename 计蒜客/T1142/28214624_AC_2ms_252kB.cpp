#include<iostream>
using namespace std;
int a[50][50];
int main(){
	int n;
	cin>>n;
	int m=2*n-1;
	int x=0,y=m/2;
	for(int i=1;i<=m*m;i++){
		a[x][y]=i;
		if(x>0&&y<m&&a[x-1][y+1]!=0){
			x++;continue;
		}
		if(y==m-1&&x==0){
			x++;continue;
		}
		if(x==0){
			x=m-1;
			y++;
			continue;
		}
		if(y==m-1&&x){
			y=0;x--;
			continue;
		}
		if(x>0&&y<m&&a[x-1][y+1]==0){
			x--;y++;
			continue;
		}
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}