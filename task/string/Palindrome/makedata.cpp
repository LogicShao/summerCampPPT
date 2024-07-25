#include <bits/stdc++.h>

using LL = long long;

constexpr int CASE_NUM = 10;
constexpr int CASE_SIZE[CASE_NUM] = {
    (int)1e4, (int)1e4, (int)1e4,
    (int)1e4, (int)1e4, (int)1e5,
    (int)1e5, (int)1e5, (int)1e5,
    (int)1e5
};
std::string CASE_INFO[CASE_NUM];
constexpr std::string_view char_set = "abcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

int solve(std::string &s, int n) {
    // manacher
    std::vector<int> p(n * 2 + 1); // p[i] = max length of palindrome centered at i
    std::string t(n * 2 + 1, '#'); // t[i] = s[(i - 1) / 2]
    for (int i = 0; i < n; ++i) {
        t[i * 2 + 1] = s[i];
    }
    int mx = 0, id = 0, res = 0;
    for (int i = 0; i < n * 2 + 1; ++i) {
        p[i] = mx > i ? std::min(p[2 * id - i], mx - i) : 1;
        while (i + p[i] < n * 2 + 1 && i - p[i] >= 0 && t[i + p[i]] == t[i - p[i]]) {
            ++p[i];
        }
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
        res = std::max(res, p[i] - 1);
    }
    return res;
}

std::string makeRandString(int n) { // 1-indexed
    std::string res;
    for (int i = 0; i <= n; ++i) {
        res.push_back(char_set[rnd() % char_set.size()]);
    }
    int palin_len = std::uniform_int_distribution<int>(1, n)(rnd);
    int l = std::uniform_int_distribution<int>(1, n - palin_len + 1)(rnd);
    int r = l + palin_len - 1;
    for (int i = l; i <= (l + r) / 2; ++i) {
        res[i] = res[r - i + l];
    }
    return res.substr(1);
}

std::string make_same_string(int n) {
    std::string res;
    char c = char_set[rnd() % char_set.size()];
    for (int i = 0; i <= n; ++i) {
        res.push_back(c);
    }
    int runin_cnt = std::uniform_int_distribution<int>(0, 3)(rnd);
    for (int i = 0; i < runin_cnt; ++i) {
        int idx = std::uniform_int_distribution<int>(1, n)(rnd);
        res[idx] = char_set[rnd() % char_set.size()];
    }
    return res.substr(1);
}

void hack_bf(int _case, int n, int score) {
    // make data
    std::string s = make_same_string(n);

    // write data
    std::ofstream out(std::format("./task/{}.in", _case));
    out << n << '\n' << s << '\n';
    out.close();

    // write answer
    out.open(std::format("./task/{}.out", _case));
    out << solve(s, n) << '\n';
    out.close();

    // make info
    CASE_INFO[_case] = std::format("{} {} #n={}#", _case, score, n);
}

void make_data(int _case, int n, int score) {
    // make data
    std::string s = makeRandString(n);

    // write data
    std::ofstream out(std::format("./task/{}.in", _case));
    out << n << '\n' << s << '\n';
    out.close();

    // write answer
    out.open(std::format("./task/{}.out", _case));
    out << solve(s, n) << '\n';
    out.close();

    // make info
    CASE_INFO[_case] = std::format("{} {} #n={}#", _case, score, n);
}

void wirte_info() {
    std::ofstream out("./task/scores.txt");
    for (int i = 0; i < CASE_NUM; ++i) {
        out << CASE_INFO[i] << '\n';
    }
    out.close();
}

void createTask() {
    for (int i = 0; i < CASE_NUM; ++i) {
        std::cerr << "Making test " << i << "...\n";
        if (i & 1) {
            hack_bf(i, CASE_SIZE[i], 1);
        } else {
            make_data(i, CASE_SIZE[i], 1);
        }
    }
    wirte_info();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    createTask();
}