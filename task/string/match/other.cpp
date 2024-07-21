#include <bits/stdc++.h>

void solve(std::ifstream &cin, std::ofstream &cout)
{
    int n, m;
    cin >> n >> m;
    std::string s, t;
    cin >> s >> t;
    s = " " + s, t = " " + t;
    std::vector<int> nxt(m + 1, 0);
    for (int i = 2, j = 0; i <= m; i++)
    {
        while (j && t[j + 1] != t[i])
            j = nxt[j];
        if (t[j + 1] == t[i])
            j++;
        nxt[i] = j;
    }
    std::vector<int> ans;
    for (int i = 1, j = 0; i <= n; i++)
    {
        while (j && t[j + 1] != s[i])
            j = nxt[j];
        if (t[j + 1] == s[i])
            j++;
        if (j == m)
        {
            ans.push_back(i - m + 1);
            j = nxt[j];
        }
    }
    cout << ans.size() << "\n";
    if (ans.size() == 0)
        return;
    for (auto t : ans)
        cout << t << " ";
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::ifstream cin("3.in");
    std::ofstream cout("./output/0.test");

    int _;
    cin >> _;

    while (_--)
    {
        solve(cin, cout);
    }

    return 0;
}