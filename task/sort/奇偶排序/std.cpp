#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &i : a) std::cin >> i;
    std::sort(a.begin(), a.end(), [](int x, int y) { 
        if (x % 2 == y % 2) return x < y;
        return x % 2 > y % 2;
    });
    for (int i = 0; i < n; ++i) {
        std::cout << a[i];
        if (i < n - 1) std::cout << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();
}