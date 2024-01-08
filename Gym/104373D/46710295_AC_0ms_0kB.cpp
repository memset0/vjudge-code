#include "bits/stdc++.h"
using namespace std;
int main()
{
    int n=82;
    int w=1e6;
    printf("%d 135\n",n);
    for(int i=1;i<n;i+=3)
    {
        printf("%d %d %d\n",i,i+1,w);
        printf("%d %d 1\n",i,i+2);
        printf("%d %d 1\n",i+2,i+1);
        printf("%d %d 1\n",i+1,i+3);
        printf("%d %d %d\n",i+2,i+3,max(w/2,1));
        w=max(1,(w/2-2));
    }
    return 0;
}