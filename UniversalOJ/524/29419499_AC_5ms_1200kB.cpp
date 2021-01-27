#include <bits/stdc++.h>
using namespace std;

namespace sol1 {
#define j 1000
int b[j];
int n;
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) { cin >> b[i]; }
	int result = 0;
	for (int i = 1; i <= n; ++i) {
		for (int h = i + 1; h <= n; ++h) {
			if (b[i] > b[h]) { result += (i ^ h); }
		}
	}
	cout << result << endl;
	return 0;
}
}  // namespace sol1

namespace sol2 {
int Aeiypt[30]={293309062,96701749,694916487,371591203,450903345,936470975,360036365,596019536,362870120,978299587,72615453,677215478,297218049,296795024,703206614,117310233,243106488,303113802,602459530,151925105,47183452,590812021,886995042,967943647,1040249104,802320701,554202194,839697519,607415572,770010993};
int yetzns(int Dos,int A){
        if (A==0) return 0;
        if (A&1) return yetzns(Dos+1,A>>1)^Aeiypt[Dos];
        return yetzns(Dos+1,A>>1);
}
int main() {
    int t;
    std::cin >> t;
    for (; t; t--) {
        int n;
        std::cin >> n;
        std::cout << yetzns(0, n) << std::endl;
    }
    return 0;
}  // namespace sol2
}

int main() {
#ifdef memset0
	freopen("small.in", "r", stdin);
// freopen("small.txt", "w", stdout);
#endif
	int t;
	std::cin >> t;
	if (t == 1) {
		return sol1::main();
	} else {
		return sol2::main();
	}
}