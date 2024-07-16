#include <bits/stdc++.h>

// 下标从1开始
void adjustHeap(std::vector<int> &a, int i, int n) {
    int t = a[i];
    for (int j = i * 2; j <= n; j *= 2) {
        if (j < n && a[j] < a[j + 1]) ++j;
        if (t >= a[j]) break;
        a[i] = a[j];
        i = j;
    }
    a[i] = t;
}

void heap_sort(std::vector<int> &a) {
    int n = a.size() - 1;
    for (int i = n / 2; i >= 1; --i) adjustHeap(a, i, n); // 建堆
    for (int i = n; i > 1; --i) {
        std::swap(a[1], a[i]);
        adjustHeap(a, 1, i - 1);
    }
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    heap_sort(a);
    for (int i = 1; i <= n; ++i) std::cout << a[i] << " \n"[i == n];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();
}