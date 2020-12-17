#include <bits/stdc++.h>
#include "find.h"

int find_pos(int n, int k) {
    int ans = 0;
    for (int l = 1, r = n, mid; l <= r; ) {
        mid = l + r >> 1;
        if (query(mid) <= k) {
            ans = mid; l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}