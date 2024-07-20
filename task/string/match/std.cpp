#include <bits/stdc++.h>

using LL = long long;

constexpr int N = 1e6 + 10;
constexpr int base = 131;
constexpr int mod[] = {
    (int)1e9 + 7, (int)1e9 + 9, (int)1e9 + 21
};

struct strhash {
    int b[N], h[N], mod;

    int momo(int x) {
        return (x % mod + mod) % mod;
    }

    strhash(int mod) : mod(mod) {
        b[0] = 1;
        for (int i = 1; i < N; ++ i)
            b[i] = (LL)b[i - 1] * base % mod;
    }

    void init(const std::string &s, int n) {
        h[0] = 0;
        for (int i = 1; i <= n; ++ i) {
            h[i] = (LL)h[i - 1] * base % mod;
            h[i] = ((LL)h[i] + s[i - 1]) % mod;
        }
    }

    int get(int l, int r) {
        return momo(h[r] - (LL)h[l - 1] * b[r - l + 1] % mod);
    }
} h0(mod[0]), h1(mod[1]), h2(mod[2]);

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::string S, T;
    std::cin >> S >> T;

    h0.init(S, n);
    h1.init(S, n);
    h2.init(S, n);

    std::vector<int> thash(3, 0);
    for (int i = 0; i < 3; ++ i) {
        for (int j = 0; j < m; ++ j) {
            thash[i] = (LL)thash[i] * base % mod[i];
            thash[i] = ((LL)thash[i] + T[j]) % mod[i];
        }
    }

    auto check = [&](int l, int r) -> bool {
        return h0.get(l, r) == thash[0] && h1.get(l, r) == thash[1] && h2.get(l, r) == thash[2];
    };

    std::vector<int> ans;
    for (int i = 0; i + m - 1 < n; ++ i)
        if (check(i + 1, i + m))
            ans.push_back(i + 1);

    std::cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++ i) {
        std::cout << ans[i] << " \n"[i == (int)ans.size() - 1];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T --) {
        solve();
    }
}