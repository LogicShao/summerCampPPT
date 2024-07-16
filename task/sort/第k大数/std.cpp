#include <bits/stdc++.h>

void quick_select(std::vector<int> &a, int l, int r, int k) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = a[rand() % (r - l + 1) + l];
    while (i < j) {
        do ++i; while (a[i] < x);
        do --j; while (a[j] > x);
        if (i < j) std::swap(a[i], a[j]);
    }
    if (j - l + 1 >= k) quick_select(a, l, j, k);
    else quick_select(a, j + 1, r, k - (j - l + 1));
}

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int &i : a) std::cin >> i;
    quick_select(a, 0, n - 1, k);
    std::cout << a[k - 1] << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();
}