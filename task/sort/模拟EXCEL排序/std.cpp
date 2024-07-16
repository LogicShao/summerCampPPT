#include <bits/stdc++.h>

struct record {
    std::string id, name;
    int score;
};

std::vector<std::function<bool(const record &a, const record &b)>> comps = {
    [](const record &a, const record &b) -> bool {
        return a.id < b.id;
    },

    [](const record &a, const record &b) -> bool {
        if (a.name != b.name) return a.name < b.name;
        return a.id < b.id;
    },

    [](const record &a, const record &b) -> bool {
        if (a.score != b.score) return a.score < b.score;
        return a.id < b.id;
    }
};

void solve() {
    int n, c;
    std::cin >> n >> c;
    std::vector<record> a(n);
    for (auto &[id, name, score] : a) {
        std::cin >> id >> name >> score;
    }
    std::sort(a.begin(), a.end(), comps[c - 1]);
    for (int i = 0; i < n; ++i) {
        std::cout << a[i].id << ' ' << a[i].name << ' ' << a[i].score;
        if (i < n - 1) std::cout << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();
}