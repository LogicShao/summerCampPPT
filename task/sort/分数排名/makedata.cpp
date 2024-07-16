#include <bits/stdc++.h>

constexpr int CASE_NUM = 5;
constexpr int CASE_SIZE[CASE_NUM] = {
    (int)5e5, (int)5e5, (int)5e5, (int)5e5, (int)5e5
};
std::string CASE_INFO[CASE_NUM];

constexpr int MAXN = 1e7 + 10;
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
} students[MAXN];

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

void make_data(int _case, int n, int score) {
    std::ofstream out(std::format("{}.in", _case));
    
    std::vector<int> ids(n);
    std::iota(ids.begin(), ids.end(), 1);
    std::shuffle(ids.begin(), ids.end(), rnd);

    out << n << '\n';
    for (int i = 1; i <= n; ++i) {
        students[i].id = ids[i - 1];
        students[i].chinese_score = rnd() % 151;
        students[i].math_score = rnd() % 151;
        students[i].english_score = rnd() % 151;

        out << std::format("{} {} {} {}\n",
                students[i].id,
                students[i].chinese_score,
                students[i].math_score,
                students[i].english_score);
    }
    out.close();

    std::sort(students + 1, students + n + 1);

    out.open(std::format("{}.out", _case));
    for (int i = 1; i <= n; ++i) {
        out << std::format("{} {}\n", students[i].id, students[i].score());
    }
    out.close();

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