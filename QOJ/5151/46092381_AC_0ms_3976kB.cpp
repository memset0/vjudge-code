#include<bits/stdc++.h>
using namespace std;
double h,r,da,dw;
int main(){
	scanf("%lf%lf%lf%lf",&h,&r,&da,&dw);
	printf("%.10lf",h*sqrt(da)/(sqrt(da)+sqrt(dw)));
	return 0;
}