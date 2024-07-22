#include <iostream>
#include <cstring>
#include <cstdio>

typedef long long LL;

const int N = 1000000 + 10;
const int base1 = 131;
const int base2 = 233;
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;
char s[N];

int momo(int x, int mod) {
    return (x % mod + mod) % mod;
}

void chkmax(int &a, const int &b) {
    if (a < b) a = b;
}

struct strhash {
    int b[N], h[N], mod, base;
    int rh[N];

    strhash(int mod, int base) : mod(mod), base(base) {
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
} h1(mod1, base1), h2(mod2, base2);

bool check_odd(int R, int n, int pos) {
    // 此时圆心刚好位于回文中心字符
    // pos 刚好表示字符位置
    int l = pos - R;
    int r = pos + R;
    if (0 < l && l <= r && r <= n) {
        return h1.check(l, r) && h2.check(l, r);
    }
    return false;
}

bool check_even(int R, int n, int pos) {
    // 此时圆心夹在中心字符之间
    // pos 表示圆心位于[pos,pos+1]字符之间
    int l = pos - R + 1;
    int r = pos + R;
    if (0 < l && l < r && r <= n) {
        return h1.check(l, r) && h2.check(l, r);
    }
    return false;
}

int solve() {
    int n;
    scanf("%d%s", &n, s + 1);

    h1.init(s, n);

    int res = 1;
    // 最长奇数回文串
    for (int i = 1; i <= n; ++ i) {
        // 二分回文半径
        // 此处的回文半径定义为回文串长度除以2下取整
        int l = 0, r = std::min(i - 1, n - i) + 1;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (check_odd(mid, n, i)) l = mid;
            else r = mid - 1;
        }
        chkmax(res, 2 * l + 1);
    }
    // 最长偶数回文串
    for (int i = 1; i < n; ++ i) {
        int l = 1, r = std::min(i - 1, n - i) + 1;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (check_even(mid, n, i)) l = mid;
            else r = mid - 1;
        }
        chkmax(res, 2 * l);
    }

    return res;
}

int main() {
    printf("%d\n", solve());
}