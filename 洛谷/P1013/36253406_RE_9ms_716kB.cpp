#include <iostream>
#include <cstdlib>

using namespace std;

string tmp , ord[10] , s[10][10]; 
int n , lep[10] , lea[10] , ans[200];

inline void Update(int d , int k){
    if(ans[d] == k || ans[d] == -1)
        ans[d] = k , lea[k] = d;
    else{
        cout << "ERROR!\n";
        exit(0);
    }
}

int main(){
    cin >> n >> tmp;
    for(int i = 1 ; i < n ; i++)
        cin >> ord[i] , lep[ord[i][0]] = i , ans[i] = -1;
    for(int i = 1 ; i < n ; i++){
        cin >> tmp;
        for(int j = 1 ; j < n ; j++){
            cin >> s[i][j];
            if(i == j && s[i][j] == ord[i])
                Update(i , 0);
            if(s[i][j].size() == 2)
                Update(lep[s[i][j][0]] , 1);
        }
    }
    for(int i = 1 ; i < n - 1 ; i++){
        int chs = lea[i] , res;
        for(int j = 1 ; j < n ; j++)
            if(ans[j] != -1){
                res = i + ans[j];
                if(res >= n - 1){
                    res -= n - 1;
                    Update(lep[s[chs][j][1]] , res);
                }else
                    Update(lep[s[chs][j][0]] , res);
            }
    }
    for(int i = 1 ; i < n ; i++)
        cout << ord[i] << "=" << ans[i] << " ";
    cout << "\n" << n - 1 << "\n";
    return 0;
}

// By Sooke.
// NOIP 提高 1998 进制位.