#include <bits/stdc++.h>

using LL = long long;

LL merge_sort(std::vector<int> &a, int l, int r) {
    if (l >= r) return 0;
    int mid = (l + r) >> 1;
    LL res = merge_sort(a, l, mid) + merge_sort(a, mid + 1, r);
    std::vector<int> b(r - l + 1);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (a[i] > a[j]) {
            res += mid - i + 1;
            b[k++] = a[j++];
        } else {
            b[k++] = a[i++];
        }
    }
    while (i <= mid) b[k++] = a[i++];
    while (j <= r) b[k++] = a[j++];
    for (int i = l; i <= r; ++i) a[i] = b[i - l];
    return res;
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int &i : a) std::cin >> i;
    std::cout << merge_sort(a, 0, n - 1) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();
}