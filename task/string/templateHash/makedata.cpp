#include <bits/stdc++.h>

using LL = long long;

constexpr int CASE_NUM = 10;
constexpr int CASE_SIZE[CASE_NUM] = {
    static_cast<int>(1e2), // 0
    static_cast<int>(1e2), // 1
    static_cast<int>(1e2), // 2
    static_cast<int>(1e3), // 3
    static_cast<int>(1e3), // 4
    static_cast<int>(1e3), // 5
    static_cast<int>(1e4), // 6
    static_cast<int>(1e4), // 7
    static_cast<int>(1e4), // 8
    static_cast<int>(1e4), // 9
};
std::string CASE_INFO[CASE_NUM];
constexpr std::string_view char_set = "abcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";

constexpr int MAX_SUM_SIZE = static_cast<int>(1e5); // sum of all string

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

constexpr int mod1 = 1e9 + 7;
constexpr int mod2 = 1e9 + 9;
constexpr int mod3 = 1e9 + 21;
constexpr int base = 131;

using three_ = std::tuple<int, int, int>;

int strHash(std::string &s, int mod) {
    int res = 0;
    for (char c : s) {
        res = (1LL * res * base + c) % mod;
    }
    return res;
}

three_ strHash(std::string &s) {
    return {strHash(s, mod1), strHash(s, mod2), strHash(s, mod3)};
}

int solve_(int n, std::vector<std::string> &s) {
    std::vector<three_> hash(n);
    for (int i = 0; i < n; ++i) {
        hash[i] = strHash(s[i]);
    }
    std::sort(hash.begin(), hash.end());
    return std::unique(hash.begin(), hash.end()) - hash.begin();
}

std::string makeRandString(int n) {
    std::string res;
    for (int i = 0; i < n; ++i) {
        res.push_back(char_set[rnd() % char_set.size()]);
    }
    return res;
}

void make_data(int _case, int n, int score) {
    // make data in vector s
    int diff = rnd() % n + 1;
    std::vector<std::string> s;
    int each_string_size = MAX_SUM_SIZE / n;
    for (int i = 0; i < diff; ++i) {
        s.push_back(std::move(makeRandString(each_string_size)));
    }
    for (int i = diff; i < n; ++i) {
        s.push_back(s[rnd() % diff]);
    }
    // output in file
    std::ofstream out(std::format("{}.in", _case));
    out << n << '\n';
    for (int i = 0; i < n; ++i) {
        out << s[i] << '\n';
    }

    // make answer
    int ans = solve_(n, s);
    // output in file
    out.close();
    out.open(std::format("{}.out", _case));
    out << ans << '\n';
    out.close();

    // make info
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