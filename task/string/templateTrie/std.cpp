#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int M = 5e5 + 10;
int son[M][30], cnt[M], idx;
char str[55];

void insert(char str[])
{
    int p = 0;
    for (int i = 0; str[i]; i++)
    {
        int u = str[i] - 'a';
        if (!son[p][u]) son[p][u] = ++ idx;
        p = son[p][u];  
    }
    cnt[p] ++;
}

int query(char str[])
{
    int p = 0;
    for (int i = 0; str[i]; i++)
    {
        int u = str[i] - 'a';
        if (!son[p][u]) return 0;
        p = son[p][u];
    }
    int res = cnt[p];
    cnt[p] = -1;
    return res;
}

int main()
{
    // freopen("P2580_2.in", "r", stdin);
    // freopen("my_ans.out", "w", stdout);

    int n, m;
    scanf("%d", &n);
    while (n --) {
        scanf("%s", str);
        insert(str);
    }
    scanf("%d", &m);
    while (m --) {
        scanf("%s", str);
        int res = query(str);
        if (res > 0) printf("OK\n");
        if (res == 0) printf("WRONG\n");
        if (res == -1) printf("REPEAT\n");
    }
}