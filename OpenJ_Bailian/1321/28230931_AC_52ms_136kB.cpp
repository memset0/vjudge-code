#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
#include <string>
#include <set>
#include <functional>
#include <numeric>
#include <sstream>
#include <stack>
#include <map>
#include <queue>
#include<iomanip>
using namespace std;
string s[10];
int line[10];  //记录第i个棋子放在第几列
int ans = 0;
int n,k;
int cnt = 0;
void dfs(int row)
{
    if (cnt == k)
    {
        ans ++;
        return;
    }
    if (row >= n)
    {
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (s[row][i] == '#')   //判断放棋子的可能
        {
            int ok = 1;
            for (int j = 0; j < cnt; j++)  //注意这里 < cnt
            {
                if (line[j] == i)
                {
                    ok = 0;
                    break;
                }
            }
            if (ok)
            {
                line[cnt++] = i; //第cnt个棋子放在第i列
                dfs(row + 1);
                cnt--;
            }
        }
    }
    dfs(row + 1);  //不放棋子
}
int main()
{
    while(cin >> n >> k)
    {
        memset(line,-1,sizeof(line));
        ans = 0,cnt = 0;
        if (n == -1 && k == -1) break;
        for (int i = 0; i < n; i++) cin >> s[i];
        dfs(0);
        cout << ans << endl;
    }
    return 0;
}
// dafjsdjfajsdhfasjdhfjadsfygaksd yfaikdys tbfgyadsgiuyfgasdyufgayhusidgfikuygayreugft uiyoad yuivadfsihugajhdsgfhjads