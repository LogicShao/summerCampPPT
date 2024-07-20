#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("1.in", "r", stdin);
    freopen("./output/1.ans", "w", stdout);
    int n;
    cin >> n;
    map<string , int> mp;
    while(n --)
    {
        string s;
        cin >> s;
        mp[s] = 1;
    }
    int m;
    cin >> m;
    while(m --){
        string s;
        cin >> s;
        if(!mp.count(s)){
            cout << "WRONG\n";
            continue;
        }
        if(mp[s] == 1){
            cout << "OK\n";
            mp[s] = 2;
        }else if(mp[s] == 2){
            cout << "REPEAT\n";
        }

    }
    return 0;
}