#include <bits/stdc++.h>

using LL = long long;
using PII = std::pair<int, int>;

namespace solver {
    struct trie {
        std::vector<std::vector<int>> son;
        std::vector<int> cnt;
        int idx = 0;

        trie() : son(1, std::vector<int>(26, 0)), cnt(1, 0) {}

        void insert(const std::string& str) {
            int p = 0;
            for (char c : str) {
                int u = c - 'a';
                if (son[p][u] == 0) {
                    son[p][u] = ++idx;
                    son.emplace_back(26, 0);
                    cnt.push_back(0);
                }
                p = son[p][u];
            }
            cnt[p]++;
        }

        int query(const std::string& str) {
            int p = 0;
            for (char c : str) {
                int u = c - 'a';
                if (son[p][u] == 0) {
                    return 0;
                }
                p = son[p][u];
            }
            int res = cnt[p];
            cnt[p] = -1;
            return res;
        }
    };

    void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n;
        trie t;
        for (int i = 0; i < n; ++i) {
            std::string str;
            in >> str;
            t.insert(str);
        }
        in >> m;
        for (int i = 0; i < m; ++i) {
            std::string str;
            in >> str;
            int res = t.query(str);
            if (res > 0) {
                out << "OK\n";
            } else if (res == 0) {
                out << "WRONG\n";
            } else {
                out << "REPEAT\n";
            }
        }
    }
}; // namespace solver

// case info
constexpr int CASE_NUM = 10;
std::string CASE_INFO[CASE_NUM];
constexpr int case_size_n1 = static_cast<int>(1e3);
constexpr int case_size_n2 = static_cast<int>(1e4);
constexpr int case_size_n3 = static_cast<int>(1e4);
constexpr int case_size_m1 = static_cast<int>(2e3);
constexpr int case_size_m2 = static_cast<int>(2e4);
constexpr int case_size_m3 = static_cast<int>(2e5);
const std::vector<PII> CASE_SIZE = {
    {case_size_n1, case_size_m1},
    {case_size_n1, case_size_m1},
    {case_size_n1, case_size_m1},
    {case_size_n1, case_size_m1},
    {case_size_n2, case_size_m2},
    {case_size_n2, case_size_m2},
    {case_size_n2, case_size_m2},
    {case_size_n3, case_size_m3},
    {case_size_n3, case_size_m3},
    {case_size_n3, case_size_m3}
};

// other info
constexpr int MAX_string_size = 50;
constexpr std::string_view char_set = "abcdefghijklmnopqrstuvwxyz";
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

std::string makeRandString(int n) {
    std::string res;
    for (int i = 0; i < n; ++i) {
        res.push_back(char_set[rnd() % char_set.size()]);
    }
    return res;
}

void make_data(int _case, PII c_size, int score) {
    int n = c_size.first, m = c_size.second;
    // make data
    std::vector<std::string> data;
    // 生成 n 个不同的字符串
    for (int i = 0; i < n; ++i) {
        std::string str = makeRandString(rnd() % MAX_string_size + 1);
        data.push_back(std::move(str));
    }
    std::sort(data.begin(), data.end());
    data.erase(std::unique(data.begin(), data.end()), data.end());
    n = data.size();
    // 生成 m 个字符串
    std::vector<std::string> query;
    int none_cnt = std::uniform_int_distribution<int>(0, m / 2)(rnd);
    for (int i = 0; i < none_cnt; ++i) {
        std::string str = makeRandString(rnd() % MAX_string_size + 1);
        query.push_back(std::move(str));
    }
    for (int i = none_cnt; i < m; ++i) {
        query.push_back(data[rnd() % n]);
    }
    std::random_shuffle(query.begin(), query.end());
    std::cerr << std::format("case {} finish make data\n", _case);
    // write data
    std::ofstream out(std::format("{}.in", _case));
    out << n << '\n';
    for (const auto& str : data) {
        out << str << '\n';
    }
    out << m << '\n';
    for (const auto& str : query) {
        out << str << '\n';
    }
    out.close();
    std::cerr << std::format("case {} finish write data\n", _case);
    // write ans
    out.open(std::format("{}.out", _case));
    std::ifstream in(std::format("{}.in", _case));
    solver::solve(in, out);
    in.close();
    out.close();
    std::cerr << std::format("case {} finish write ans\n", _case);
    // make info
    CASE_INFO[_case] = std::format("{} {} #n={},m={}#", _case, score, n, m);
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
    for (int i = 0; i < CASE_NUM; ++i) {
        std::cerr << std::format("make test {}/{}\n", i, CASE_NUM);
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