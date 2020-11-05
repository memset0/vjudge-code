#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int T; cin >> T;
    for (int test = 1; test <= T; ++test) {
        string S; cin >> S;
        sort(S.begin(), S.end());
        int N; cin >> N;

        vector< pair<string, int> > A(N);
        int total_size = 0;
        for (int i = 0; i < N; ++i) {
            cin >> A[i].first;
            total_size += A[i].first.size();
            A[i].first += 'A';
            A[i].second = i;
        }

        sort(A.begin(), A.end());

        array<int, 10> count = {0};
        for (auto &c : S)
            count[c - '0']++;
        if (int(S.size()) < total_size)
            count[0] = total_size - S.size();

        bool good = true;
        vector<string> answer(N);
        vector<int> index(N, 0);
        for (int i = 0; i < N; ++i) {
            auto &x = A[i].first;
            int pos = A[i].second;
            auto &j = index[i];
            x.pop_back(); // the 'A'

            bool smaller = false;
            for (j = 0; j < int(x.size()); ++j) {
                if (j == int(x.size()) - 1 && answer[pos].empty())
                    break;
                char c = x[j];
                char will_use = 0;
                for (int k = 0; k <= c - '0'; ++k)
                    if (count[k] > 0) {
                        will_use = k + '0';
                        --count[k];
                        break;
                    }
                if (will_use == 0) {
                    good = false;
                    break;
                }

                if (will_use != '0')
                    answer[pos] += will_use;
                if (will_use < c) {
                    ++j;
                    smaller = true;
                    break;
                }
            }
            if (!good)
                break;
            if (answer[pos] == "") {
                // need something here 
                char will_use = 0;
                for (int k = 9; k > 0; --k)
                    if (count[k] > 0)
                        if (smaller || k + '0' <= x[j]) {
                            will_use = k + '0';
                            --count[k];
                            break;
                        }
                if (will_use == 0) {
                    good = false;
                    break;
                }

                ++j;
                answer[pos] += will_use;
            }
        }
        for (int i = 0; i < N && good; ++i) {
            auto &x = A[i].first;
            auto pos = A[i].second;
            auto &j = index[i];

            for (; j < int(x.size()) && good; ++j) {
                char will_use = 0;
                for (int k = 0; k < 10; ++k)
                    if (count[k] > 0) {
                        will_use = k + '0';
                        --count[k];
                        break;
                    }
                if (will_use != '0')
                    answer[pos] += will_use;
            }
        }

        if (!good || total_size < int(S.size())) {
            cout << "-1\n";
            continue;
        }
        for (auto &x : answer)
            cout << x << " ";
        cout << "\n";
    }
}