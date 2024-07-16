#include <bits/stdc++.h>

using LL = long long;

constexpr int CASE_NUM = 5;
constexpr int CASE_SIZE[CASE_NUM] = {
    (int)1e3, (int)1e4, (int)1e5, (int)5e5, (int)5e5
};
std::string CASE_INFO[CASE_NUM];

constexpr int MAXN = 5e5 + 10;
int a[MAXN], b[MAXN];

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

LL merge_sort(int *a, int l, int r) {
    if (l >= r) return 0;
    int mid = (l + r) >> 1;
    LL res = merge_sort(a, l, mid) + merge_sort(a, mid + 1, r);
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

void make_data(int _case, int n, int score) {
    std::ofstream out(std::format("{}.in", _case));
    out << n << '\n';
    for (int i = 0; i < n; ++i) {
        if (_case != CASE_NUM - 1) {
            a[i] = rnd() % static_cast<int>(1e9) + 1; // 随机
        } else {
            a[i] = n - i; // 逆序
        }

        out << a[i] << " \n"[i == n - 1];
    }
    out.close();

    LL res = merge_sort(a, 0, n - 1);
    std::ofstream ans(std::format("{}.out", _case));
    ans << res << '\n';
    ans.close();

    CASE_INFO[_case] = std::format("{} {} #n={}#", _case, score, n);
}

void wirte_info() {
    std::ofstream out("scores.txt");
    for (int i = 0; i < CASE_NUM; ++i) {
        out << CASE_INFO[i] << '\n';
    }
    out.close();
}

void createTask() {
    for (int i = 0; i < CASE_NUM; ++i) {
        make_data(i, CASE_SIZE[i], 1);
    }
    wirte_info();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    createTask();
}