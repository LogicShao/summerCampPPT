#include <bits/stdc++.h>

using LL = long long;

constexpr int CASE_NUM = 5;
constexpr int CASE_SIZE[CASE_NUM] = {
    (int)1e3, (int)1e4, (int)1e5, (int)5e5, (int)5e5
};
std::string CASE_INFO[CASE_NUM];

constexpr int MAXN = 5e5 + 10;
constexpr int MAX_sum_height = 2e9 + 7;
int height[MAXN];

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

bool allpos(int n) {
    for (int i = 0; i < n; ++i) {
        if (height[i] < 0) {
            std::cerr << "failed!";
            return false;
        }
    }
    return true;
}

LL make_rand_height(int n) {
    // sum_height <= MAX_sum_height
    int average_height = MAX_sum_height / n;
    LL sum_height = 0;
    for (int i = 0; i < n; ++i) {
        // 正态分布
        height[i] = std::uniform_int_distribution<int>(average_height / 4, average_height * 3 / 4)(rnd);
        sum_height += height[i];
    }
    if (sum_height > MAX_sum_height) {
        int delta = sum_height - MAX_sum_height;
        for (int i = 0; i < n; ++i) {
            if (height[i] > delta) {
                height[i] -= delta;
                break;
            }
        }
    }
    if (!allpos(n)) {
        return make_rand_height(n);
    }
    return sum_height;
}

void make_data(int _case, int n, int score) {
    std::ofstream out(std::format("{}.in", _case));
    LL sum_height = make_rand_height(n);
    LL k = std::uniform_int_distribution<LL>(1, sum_height)(rnd);
    out << n << ' ' << k << '\n';
    for (int i = 0; i < n; ++i) {
        out << height[i] << "\n";
    }
    out.close();

    out.open(std::format("{}.out", _case));
    std::sort(height, height + n, std::greater<int>());
    LL sum = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        sum += height[i];
        ++ans;
        if (sum >= k) break;
    }
    out << ans << '\n';
    out.close();

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