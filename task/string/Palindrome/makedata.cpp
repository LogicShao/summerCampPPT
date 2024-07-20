#include <bits/stdc++.h>

using LL = long long;

constexpr int CASE_NUM = 10;
constexpr int CASE_SIZE[CASE_NUM] = {
    static_cast<int>(1e4), // 0
    static_cast<int>(1e4), // 1
    static_cast<int>(1e4), // 2
    static_cast<int>(1e5), // 3
    static_cast<int>(1e5), // 4
    static_cast<int>(1e5), // 5
    static_cast<int>(1e6), // 6
    static_cast<int>(1e6), // 7
    static_cast<int>(1e6), // 8
    static_cast<int>(1e6), // 9
};
std::string CASE_INFO[CASE_NUM];
constexpr std::string_view char_set = "abcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

constexpr int mod1 = 1e9 + 7;
constexpr int mod2 = 1e9 + 9;
constexpr int mod3 = 1e9 + 21;
constexpr int base = 131;
constexpr int N = static_cast<int>(1e6) + 10;

struct strHashImpl {
    int b[N], h[N], mod;
    int rh[N];

    strHashImpl(int mod) : mod(mod) {
        b[0] = 1;
        for (int i = 1; i < N; ++i) {
            b[i] = 1LL * b[i - 1] * base % mod;
        }
    }

    int momo(int x) {
        return (x % mod + mod) % mod;
    }

    void init(std::string &s, int n) { // 1-indexed
        h[0] = 0;
        for (int i = 1; i <= n; ++i) {
            h[i] = 1LL * h[i - 1] * base % mod;
            h[i] = (1LL * h[i] + s[i]) % mod;
        }
        rh[n + 1] = 0;
        for (int i = n; i; --i) {
            rh[i] = 1LL * rh[i + 1] * base % mod;
            rh[i] = (1LL * rh[i] + s[i]) % mod;
        }
    }

    int get(int l, int r) { // 1-indexed
        return momo(h[r] - 1LL * h[l - 1] * b[r - l + 1] % mod);
    }

    int rget(int l, int r) { // 1-indexed
        return momo(rh[l] - 1LL * rh[r + 1] * b[r - l + 1] % mod);
    }
} h1(mod1), h2(mod2), h3(mod3);

bool check_palindrome(std::string &s, int l, int r) { // 1-indexed
    return h1.get(l, r) == h1.rget(l, r) && h2.get(l, r) == h2.rget(l, r) && h3.get(l, r) == h3.rget(l, r);
}

int solve(std::string &s, int n) {
    h1.init(s, n);
    h2.init(s, n);
    h3.init(s, n);
    std::vector<int> R(n + 1);
    R[1] = 1;
    R[2] = s[1] == s[2] ? 2 : 1;
    for (int i = 3; i <= n; ++i) {
        R[i] = 1;
        for (int j = std::min(R[i - 1] + 2, i); j; --j) {
            if (check_palindrome(s, i - j + 1, i)) {
                R[i] = j;
                break;
            }
        }
    }
    return *std::max_element(R.begin() + 1, R.end());
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
    return res;
}

void make_data(int _case, int n, int score) {
    // make data
    std::string s = makeRandString(n);

    // write data
    std::ofstream out(std::format("{}.in", _case));
    out << n << '\n' << s << '\n';
    out.close();

    // write answer
    out.open(std::format("{}.out", _case));
    out << solve(s, n) << '\n';
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