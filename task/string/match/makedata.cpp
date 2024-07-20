#include <bits/stdc++.h>

using LL = long long;
using PII = std::pair<int, int>;

// case info
constexpr int CASE_NUM = 10;
constexpr int SUM_CASE_SIZE = (int)1e6;
constexpr int CASE_SIZE[] = {
    (int)10, (int)20, (int)50,
    (int)100, (int)200, (int)1e4,
    (int)1e5, (int)1e5, (int)1e6,
    (int)1e6
};
std::string CASE_INFO[CASE_NUM];

// other info
constexpr std::string_view char_set = "abcdefghijklmnopqrstuvwxyz";
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

std::string makeRandString(int n, int range = 26) {
    std::string res;
    for (int i = 0; i < n; ++i) {
        res.push_back(char_set[rnd() % range]);
    }
    return res;
}

std::string make_case(int n) {
    int m = std::uniform_int_distribution<int>(1, n)(rnd);
    int range = std::uniform_int_distribution<int>(1, 26)(rnd);
    std::string S = makeRandString(n, range);
    std::string T = makeRandString(m, range);
    return std::format("{} {}\n{}\n{}\n", n, m, S, T);
}

std::string ensure_case(int n) {
    int m = std::uniform_int_distribution<int>(1, n)(rnd);
    int range = std::uniform_int_distribution<int>(1, 5)(rnd);
    // 尝试构造 S 使得 T 在 S 中出现 cnt 次
    // m 为 range 的倍数
    std::string period = makeRandString(range, range);
    m = m / range * range;
    std::string T = period;
    for (int i = 1; i < m / range; ++i) {
        T += period;
    }
    n = n / range * range;
    std::string S = period;
    for (int i = 1; i < n / range; ++i) {
        S += period;
    }
    return std::format("{} {}\n{}\n{}\n", n, m, S, T);
};

// 随机数据 没有特殊处理
void make_small_data(int _case, int size, int score) {
    // make data
    int T = SUM_CASE_SIZE / size;
    int n = size;
    // write data
    std::ofstream out(std::format("{}.in", _case));
    out << T << '\n';
    for (int i = 0; i < T; ++i) {
        if (rand() & 1) {
            out << make_case(n);
        } else {
            out << ensure_case(n);
        }
    }
    out.close();
    std::cerr << std::format("case {} finish make data\n", _case);
    // write ans
    system(std::format("std < {}.in > {}.out", _case, _case).c_str());
    std::cerr << std::format("case {} finish write ans\n", _case);
    // make info
    CASE_INFO[_case] = std::format("{} {} #T={},n={},random case#", _case, score, T, n);
    std::cerr << std::format("case {} finish\n", _case);
}

// 大数据保证出现次数不能过少
void make_ensure_data(int _case, int size, int score) {
    // make data
    int T = SUM_CASE_SIZE / size;
    int n = size;
    // write data
    std::ofstream out(std::format("{}.in", _case));
    out << T << '\n';
    for (int i = 0; i < T; ++i) {
        out << ensure_case(n);
    }
    out.close();
    std::cerr << std::format("case {} finish make data\n", _case);
    // write ans
    system(std::format("std < {}.in > {}.out", _case, _case).c_str());
    std::cerr << std::format("case {} finish write ans\n", _case);
    // make info
    CASE_INFO[_case] = std::format("{} {} #T={},n={},big case#", _case, score, T, n);
    std::cerr << std::format("case {} finish\n", _case);
}

void wirte_info() {
    std::ofstream out("scores.txt");
    for (int i = 0; i < CASE_NUM; ++i) {
        out << CASE_INFO[i] << '\n';
    }
    out.close();
}

void createTask() {
    int each_score = 2;
    for (int i = 0; i < CASE_NUM; ++i) {
        std::cerr << std::format("make case {}/{}\n", i, CASE_NUM);
        if (i < 5) {
            make_small_data(i, CASE_SIZE[i], each_score);
        } else {
            make_ensure_data(i, CASE_SIZE[i], each_score);
        }
    }
    wirte_info();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    system("g++ -o std std.cpp -O2 -std=c++2a");
    createTask();
}