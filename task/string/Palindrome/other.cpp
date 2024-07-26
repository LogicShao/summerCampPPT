#pragma GCC optimize(1, 2, 3, "Ofast", "inline")
#include <bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
using namespace std;
const int N = 1e6 + 5;
int _ = 1, n, m, k, x, y, z, ans, l, r, t;
bool p, vis[N];
string s;
const int P1 = 1e9 + 7;
const int P2 = 1e9 + 9;
const int b1 = 33331;
const int b2 = 32141;
struct Hash {
    ll x, y;
    Hash() : x(0), y(0) {}
    Hash(ll x) : x(x), y(x) {}
    Hash(ll t1, ll t2) : x(t1), y(t2) {}
    inline bool operator==(const Hash &aa) const {
        if (x == aa.x && y == aa.y) return 1;
        return 0;
    }
    inline bool operator!=(const Hash &aa) const { return !(*this == aa); }
    inline void js() {
        x = (x % P1 + P1) % P1;
        y = (y % P2 + P2) % P2;
    }
    inline bool operator<(const Hash &aa) const {
        if (x != aa.x) return x < aa.x;
        return y < aa.y;
    }
    inline Hash operator+(const Hash &aa) const { return (Hash){x + aa.x, y + aa.y}; }
    inline Hash operator-(const Hash &aa) const { return (Hash){x - aa.x, y - aa.y}; }
    inline Hash operator*(const Hash &aa) const { return (Hash){x * aa.x, y * aa.y}; }
    inline Hash operator*(const ll &aa) const { return (Hash){x * aa, y * aa}; }
    inline Hash operator%(const Hash &aa) const {
        return (Hash){(x % aa.x + aa.x) % aa.x, (y % aa.y + aa.y) % aa.y};
    }
    inline void print() {
        cout << x << ' ';
        cout << y << endl;
    }
};
struct my_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    // 针对 std::pair<int, int> 作为主键类型的哈希函数
    size_t operator()(Hash x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x.x + FIXED_RANDOM) ^ (splitmix64(x.y + FIXED_RANDOM) >> 1);
    }
};
const Hash P = {P1, P2};
const Hash B = {b1, b2};
unordered_map<Hash, int, my_hash> mp;
struct TT {
    Hash sum[N], power[N];
    void pre(string s1, int N) {
        power[0] = Hash(1);
        for (int i = 1; i <= N; i++) {
            sum[i] = (sum[i - 1] * B + Hash(s1[i])) % P;
            power[i] = power[i - 1] * B % P;
        }
    }
    Hash query(int l, int r) {
        Hash ans = sum[r] - sum[l - 1] * power[r - l + 1] % P;
        ans.js();
        return ans;
    }
} TT[2];
bool check(int len) {
    for (int i = 1; i <= n; ++i) {
        int x = i - len / 2;
        int y = i + (len - len / 2 - 1);
        if (x < 1 || y > n) continue;
        if (TT[0].query(x, y) == TT[1].query(n - y + 1, n - x + 1)) return 1;
    }
    return 0;
}
void solve() {
    cin >> n >> s;
    s = ' ' + s;
    TT[0].pre(s, n);
    reverse(s.begin(), s.end());
    s = ' ' + s;
    TT[1].pre(s, n);
    l = 0, r = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid * 2)) {
            l = mid + 1;
            ans = max(ans, mid * 2);
        }
        else r = mid - 1;
    }
    l = 0, r = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid * 2 + 1)) {
            l = mid + 1;
            ans = max(ans, mid * 2 + 1);
        }
        else r = mid - 1;
    }
    cout << ans + 1 << endl;
}
signed main() {
    ios::sync_with_stdio(false);
    freopen("task/9.in", "r", stdin);
    //cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}