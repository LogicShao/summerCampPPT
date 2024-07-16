#include <bits/stdc++.h>

constexpr int CASE_NUM = 5;
constexpr int CASE_SIZE[CASE_NUM] = {
    (int)1e3, (int)1e4, (int)1e5, (int)1e6, (int)1e7
};
std::string CASE_INFO[CASE_NUM];

constexpr int MAXN = 1e7 + 10;
int a[MAXN];

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

void make_data(int _case, int n, int score) {
    std::ofstream out(std::format("{}.in", _case));
    int k = rnd() % n + 1;
    out << n << ' ' << k << '\n';
    for (int i = 1; i <= n; ++i) {
        a[i] = rnd() % (int)1e5;
        out << a[i] << " \n"[i == n];
    }
    out.close();
    
    std::ofstream ans(std::format("{}.out", _case));
    std::nth_element(a + 1, a + k, a + n + 1, std::greater<int>());
    ans << a[k] << '\n';
    ans.close();

    CASE_INFO[_case] = std::format("{} {} #n={},k={}#", _case, score, n, k);
}

void wirte_info() {
    std::ofstream out("scores.txt");
    for (int i = 0; i < CASE_NUM; ++i) {
        out << CASE_INFO[i] << '\n';
    }
    out.close();
}

void test() {
    make_data(5, 3, 1);
    wirte_info();
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

    test();

    // createTask();
}