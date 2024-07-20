#include <iostream>
#include <cstring>
#include <cstdio>

typedef long long LL;

const int N = 1000000 + 10;
const int base = 131;
const int mod1 = 1e9 + 7; // 双模数
const int mod2 = 1e9 + 9;
char s[N];
int R[N]; // R[i] 表示以 i 结尾的回文串的最大长度

inline int momo(int x, int mod) {
    return (x % mod + mod) % mod;
}

inline void chkmax(int &a, const int &b) {
    if (a < b) a = b;
}

struct strhash {
    int b[N], h[N], mod;
    int rh[N];

    strhash(int mod) : mod(mod) {
        b[0] = 1;
        for (int i = 1; i < N; ++ i)
            b[i] = (LL)b[i - 1] * base % mod;
    }

    void init(char *s, int n) {
        h[0] = 0; // 正向哈希
        for (int i = 1; i <= n; ++ i) {
            h[i] = (LL)h[i - 1] * base % mod;
            h[i] = ((LL)h[i] + s[i]) % mod;
        }
        rh[n + 1] = 0; // 反向哈希
        for (int i = n; i; -- i) {
            rh[i] = (LL)rh[i + 1] * base % mod;
            rh[i] = ((LL)rh[i] + s[i]) % mod;
        }
    }

    int get(int l, int r) {
        return momo(h[r] - (LL)h[l - 1] * b[r - l + 1] % mod, mod);
    }

    int rget(int l, int r) {
        return momo(rh[l] - (LL)rh[r + 1] * b[r - l + 1] % mod, mod);
    }

    bool check(int l, int r) {
        // 判断是否为回文
        return get(l, r) == rget(l, r);
    }
} h1(mod1), h2(mod2);

int solve() {
    int n;
    scanf("%d", &n);
    scanf("%s", s + 1);

    h1.init(s, n);
    h2.init(s, n);

    R[1] = 1;
    R[2] = s[1] == s[2] ? 2 : 1;
    for (int i = 3; i <= n; ++ i) {
        R[i] = 1;
        for (int j = std::min(R[i - 1] + 2, i); j; -- j) {
            int l = i - j + 1;
            int r = i;
            if (h1.check(l, r) && h2.check(l, r)) {
                R[i] = j;
                break;
            }
        }
    }

    int res = 1;
    for (int i = 1; i <= n; ++ i) {
        chkmax(res, R[i]);
    }

    return res;
}

int main() {
    printf("%d\n", solve());
}