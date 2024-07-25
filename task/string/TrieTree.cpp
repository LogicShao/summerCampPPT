#include <bits/stdc++.h>

constexpr int N = 5e5 + 10; // 字典树节点数 (字符串总长度)
constexpr int M = 30; // 字符集大小
// 对于小写字母，字符集大小为 26
// 对于二进制整数，字符集大小为 2
// 字符集的定义是比较广泛的，不要局限于传统意义上的字符

struct TrieTree {
    // son[p][u] 表示节点 p 的第 u 个儿子
    // 对应的字符是字符集中的第 u 个字符
    // son[p][u] = 0 表示节点 p 的第 u 个儿子不存在
    // 也就是说，此时是字符串的末尾
    // cnt[p] 表示以节点 p 结尾的字符串的数量
    // idx 表示节点编号
    // 我们使用 0 号节点作为根节点
    int son[N][M], cnt[N], idx;

    void clear(int size) { // 初始化字典树
        // 如果有多组测试数据，需要清空字典树
        // 但是不能每次全部清空，否则会超时
        // size 是字典树的节点数
        memset(son, 0, size * sizeof(son[0]));
        memset(cnt, 0, size * sizeof(cnt[0]));
        idx = 0;
    }

    void insert(char str[]) { // 插入字符串
        int p = 0;
        for (int i = 0; str[i]; i++) {
            int u = str[i] - 'a';
            if (!son[p][u]) son[p][u] = ++ idx; // 如果儿子不存在，创建新节点
            p = son[p][u]; // 移动到下一个节点
        }
        cnt[p] ++; // 以节点 p 结尾的字符串数量加一
    }

    int query(char str[]) { // 查询字符串出现次数
        int p = 0;
        for (int i = 0; str[i]; i++) {
            int u = str[i] - 'a';
            if (!son[p][u]) return 0; // 如果没有完整匹配，说明字符串不存在
            p = son[p][u];
        }
        return cnt[p]; // 返回以节点 p 结尾的字符串数量
    }
};