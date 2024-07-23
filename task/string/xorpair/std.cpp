#include <bits/stdc++.h>

using LL = long long;

constexpr int N = 1e5 + 5, M = 35;
constexpr int NM = N * M;

struct trie {
    int son[NM][2], idx = 0;

    void insert(int x) {
        int p = 0;
        for (int i = 30; i >= 0; -- i) {
            int t = (x >> i) & 1;
            if (!son[p][t]) son[p][t] = ++ idx;
            p = son[p][t];
        }
    }

    int query(int x) {
        int p = 0, res = 0;
        for (int i = 30; i >= 0; -- i) {
            int t = (x >> i) & 1;
            if (son[p][t ^ 1]) {
                res |= 1 << i;
                p = son[p][t ^ 1];
            } else {
                p = son[p][t];
            }
        }
        return res;
    }
} tr;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int &x : a) std::cin >> x;

    int res = 0;
    for (int i = 0; i < n; ++ i) {
        tr.insert(a[i]);
        res = std::max(res, tr.query(a[i]));
    }

    std::cout << res << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T = 1;
    // std::cin >> T;

    while (T --) {
        solve();
    }
}