#include <bits/stdc++.h>

struct stu {
    int id;
    int chinese_score;
    int math_score;
    int english_score;

    int score() const {
        return chinese_score + math_score + english_score;
    }

    int score1() const {
        return chinese_score + math_score;
    }

    bool operator<(const stu &rhs) const {
        if (score() != rhs.score()) {
            return score() > rhs.score();
        }
        if (score1() != rhs.score1()) {
            return score1() > rhs.score1();
        }
        if (chinese_score != rhs.chinese_score) {
            return chinese_score > rhs.chinese_score;
        }
        return id < rhs.id;
    }
};

void solve() {
    int n;
    std::cin >> n;
    std::vector<stu> students(n);
    for (auto &[id, a, b, c] : students) {
        std::cin >> id >> a >> b >> c;
    }
    std::sort(students.begin(), students.end());
    for (auto &s : students) {
        std::cout << s.id << ' ' << s.score() << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();
}