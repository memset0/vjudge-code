#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
int main()
{
    std::ios::sync_with_stdio(0);
    int task;
    std::cin>>task;
    while(task--)
    {
        int n,m;std::cin>>n>>m;
        std::cout<<n-m+1<<std::endl;
    }
    return 0;
}