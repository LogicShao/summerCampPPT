#include <bits/stdc++.h>

using LL = long long;
using PII = std::pair<int, int>;

constexpr int N = 1e5 + 10;
constexpr int mod1 = 1e9 + 7, mod2 = 1e9 + 9;
constexpr int base1 = 131, base2 = 233;

int str_hash(const std::string &s, int base, int mod) {
    // 计算字符串哈希值
    int res = 0;
    for (char c : s) {
        res = (1LL * res * base % mod + c) % mod;
    }
    return res;
}

struct strHashImpl { // 单模数哈希
    // h: 正向哈希值(前缀和), rh: 反向哈希值(后缀和)
    // rh 用于判断回文串，如果 h[l, r] == rh[l, r]，则 [l, r] 是回文串
    // 如果不需要判断回文串，可以不用 rh
    int h[N], rh[N]; 
    int p[N]; // p[i] 表示 base 的 i 次方，也就是每一个字符的权值
    int base, mod; // base: 基数, mod: 模数
    int n; // 字符串长度

    strHashImpl(int base, int mod) : base(base), mod(mod) {
        // 初始化: 计算 base 的 i 次方
        p[0] = 1;
        for (int i = 1; i < N; ++ i) {
            p[i] = 1LL * p[i - 1] * base % mod;
        }
    }

    strHashImpl(PII arg) : strHashImpl(arg.first, arg.second) {} // 用于初始化多哈希

    void init(const std::string &s) { // 下标从 0 开始
        // 初始化: 计算正向哈希值
        n = s.size();
        h[1] = s[0];
        for (int i = 0; i < n; ++ i) {
            h[i] = (1LL * h[i - 1] * base % mod + s[i - 1]) % mod;
        }

        // 初始化: 计算反向哈希值
        rh[n + 1] = 0;
        for (int i = n; i; -- i) {
            rh[i] = (1LL * rh[i + 1] * base % mod + s[i - 1]) % mod;
        }
    }

    int get(int l, int r) { // 获取 [l, r] 的哈希值
        return (h[r] - 1LL * h[l - 1] * p[r - l + 1] % mod + mod) % mod;
    }

    int rget(int l, int r) { // 获取 [l, r] 的反向哈希值
        return (rh[l] - 1LL * rh[r + 1] * p[r - l + 1] % mod + mod) % mod;
    }

    bool palindromic(int l, int r) { // 判断 [l, r] 是否为回文串
        return get(l, r) == rget(l, r);
    }

    bool equal(int l1, int r1, int l2, int r2) { // 判断 [l1, r1] 和 [l2, r2] 是否相等
        return get(l1, r1) == get(l2, r2);
    }
};

// 实现一下泛型的 HashChecker
// 方便写多哈希(虽然最多只会用到两个哈希)
// 同时使用几个单哈希就是多哈希
// 一般最多只会用到双哈希
template <PII ...Args> // Args: {base, mod}
struct Checker {
    std::vector<strHashImpl> h;

    Checker() : h({Args...}) {}

    void init(const std::string &s) {
        for (auto &hi : h) {
            hi.init(s);
        }
    }

    bool palindromic(int l, int r) { // 检查 [l, r] 是否为回文串
        for (auto &hi : h) {
            if (!hi.palindromic(l, r)) {
                return false;
            }
        }
        return true;
    }

    bool equal(int l1, int r1, int l2, int r2) { // 检查 [l1, r1] 和 [l2, r2] 是否相等
        for (auto &hi : h) {
            if (hi.get(l1, r1) != hi.get(l2, r2)) {
                return false;
            }
        }
        return true;
    }
};

using ULL = unsigned long long;

struct strHashImpl2 { // 自然溢出哈希
    // 使用 ULL 即是对 2**64 取模
    ULL h[N], rh[N]; // 正向哈希值(前缀和), 反向哈希值(后缀和)
    ULL p[N]; // p[i] 表示 base 的 i 次方，也就是每一个字符的权值
    int base; // 基数
    int n; // 字符串长度

    strHashImpl2(int base) : base(base) {
        // 初始化: 计算 base 的 i 次方
        p[0] = 1;
        for (int i = 1; i < N; ++ i) {
            p[i] = p[i - 1] * base;
        }
    }

    void init(const std::string &s) { // 下标从 0 开始
        // 初始化: 计算正向哈希值
        n = s.size();
        h[1] = s[0];
        for (int i = 0; i < n; ++ i) {
            h[i] = h[i - 1] * base + s[i - 1];
        }

        // 初始化: 计算反向哈希值
        rh[n + 1] = 0;
        for (int i = n; i; -- i) {
            rh[i] = rh[i + 1] * base + s[i - 1];
        }
    }

    ULL get(int l, int r) { // 获取 [l, r] 的哈希值
        return h[r] - p[r - l + 1] * h[l - 1];
    }

    ULL rget(int l, int r) { // 获取 [l, r] 的反向哈希值
        return rh[l] - p[r - l + 1] * rh[r + 1];
    }

    bool palindromic(int l, int r) { // 判断 [l, r] 是否为回文串
        return get(l, r) == rget(l, r);
    }

    bool equal(int l1, int r1, int l2, int r2) { // 判断 [l1, r1] 和 [l2, r2] 是否相等
        return get(l1, r1) == get(l2, r2);
    }
};

using i128 = __int128; // 当然如果模数够大的话，可以直接单模数哈希

LL fpow(LL a, LL b, LL mod) { // 快速幂 a^b % mod
    LL res = 1;
    while (b) {
        if (b & 1) res = (i128)res * a % mod;
        a = (i128)a * a % mod;
        b >>= 1;
    }
    return res;
}

bool Miller_Rabin(LL x) { // Miller-Rabin 素数测试
    // 时间复杂度 O(klogx)
    // 有 2^(-k) 的概率判断错误
    // 想学习的可以看：
    // 1: https://oi-wiki.org/math/number-theory/prime/#millerrabin-%E7%B4%A0%E6%80%A7%E6%B5%8B%E8%AF%95
    // 2: https://www.bilibili.com/video/BV14K411e7aT/
    if (x == 2) return true;
    if (x < 2 || !(x & 1)) return false;
    LL u = x - 1, t = 0;
    while (!(u & 1)) u >>= 1, ++ t;
    for (auto a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        LL v = fpow(a, u, x);
        if (v == 1 || v == x - 1) continue;
        for (int i = 1; i < t; ++ i) {
            v = (i128)v * v % x;
            if (v == x - 1) break;
            if (v == 1) return false;
        }
        if (v != x - 1) return false;
    }
    return true;
}

std::vector<LL> find_prime(LL x, int num = 1) { // 找到大于等于 x 的 num 个素数
    std::vector<LL> res;
    for (LL i = x; res.size() < num; ++ i) {
        if (Miller_Rabin(i)) res.push_back(i);
    }
    return res;
}

const LL mod_ = find_prime(1e18, 1)[0]; // 找到一个大于等于 1e18 的素数作为模数
const LL base_ = 131;

/**
 * 打表可得>1e18的前10个素数为:
 *  1000000000000000003,
 *  1000000000000000009,
 *  1000000000000000031,
 *  1000000000000000079,
 *  1000000000000000177,
 *  1000000000000000183,
 *  1000000000000000201,
 *  1000000000000000283,
 *  1000000000000000381,
 *  1000000000000000387
 */

struct strHashImpl3 { // 单模数哈希
    LL h[N]; // 实现和上面一样，只是用了更大的模数
    LL p[N];
    LL base, mod;
    int n;

    strHashImpl3(LL base, LL mod) : base(base), mod(mod) {
        p[0] = 1;
        for (int i = 1; i < N; ++ i) {
            p[i] = (i128)p[i - 1] * base % mod;
        }
    }

    strHashImpl3() : strHashImpl3(base_, mod_) {}

    void init(const std::string &s) {
        n = s.size();
        h[1] = s[0];
        for (int i = 0; i < n; ++ i) {
            h[i] = (i128)h[i - 1] * base % mod;
            h[i] = ((i128)h[i] + s[i - 1]) % mod;
        }
    }

    LL get(int l, int r) { // 获取 [l, r] 的哈希值
        return (h[r] - (i128)h[l - 1] * p[r - l + 1] % mod + mod) % mod;
    }

    bool equal(int l1, int r1, int l2, int r2) { // 判断 [l1, r1] 和 [l2, r2] 是否相等
        return get(l1, r1) == get(l2, r2);
    }
};