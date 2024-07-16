#include <bits/stdc++.h>

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (auto &i : a) std::cin >> i;
    std::sort(a.begin(), a.end(), std::greater<int>());
    int ans = 0, sum = 0;
    for (auto i : a) {
        sum += i;
        ++ans;
        if (sum >= k) break;
    }
    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();
}