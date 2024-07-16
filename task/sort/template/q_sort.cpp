#include <iostream>
#include <cstdio>

using namespace std;

const int M = 1e6 + 10;
int n, q[M];

void q_sort(int l,int r) {
    if (l >= r) return;
    int x = q[(l + r) / 2], i = l - 1, j = r + 1;
    while (i < j) {
        do i++; while(q[i] < x);
        do j--; while(q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    q_sort(l, j);
    q_sort(j + 1, r);
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &q[i]);
    q_sort(1, n);
    for(int i = 1; i <= n; i++) printf("%d%c", q[i], " \n"[i == n]);
}