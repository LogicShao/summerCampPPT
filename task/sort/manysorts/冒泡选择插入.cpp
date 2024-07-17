#include <bits/stdc++.h>

void bubble_sort(int *a, int n) {
    for (int i = 1; i < n; ++ i) {
        bool flag = false;
        for (int j = 1; j < n; ++ j) { // 从前往后冒泡 大数上浮
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
                flag = true;
            }
        }
        if (!flag) break; // 如果没有交换说明已经有序
    }
}

void select_sort(int *a, int n) {
    for (int i = 1; i < n; ++ i) {
        int p = i; // 选出最小的数
        for (int j = i + 1; j <= n; ++ j) {
            if (a[j] < a[p]) p = j;
        }
        std::swap(a[i], a[p]);
    }
}

void insert_sort(int *a, int n) {
    for (int i = 2; i <= n; ++ i) {
        int x = a[i], j = i - 1;
        for (; j && a[j] > x; -- j) a[j + 1] = a[j];
        a[j + 1] = x;
    }
}

int main() {

}