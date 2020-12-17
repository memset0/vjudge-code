#include<bits/stdc++.h>
int T;
double h,H,D,x;
int main() {
	scanf("%d",&T);
	while(T--){
		scanf("%lf%lf%lf",&H,&h,&D);
		x=sqrt(D*(H-h)),
		printf("%.3f\n",std::max((D*(1-h/H)<=x)&&(x<=D)?D+H-2*x:h,D*h/H));
	}
}