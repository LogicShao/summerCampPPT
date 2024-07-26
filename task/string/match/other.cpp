#include<bits/stdc++.h>
using namespace std;
using LL = long long;
const int MAXN = 1e6+5;
const int mod = 1e9+7;
const int base = 131;
int n;
int stringsize,mubiaosize;
string wenben,muban;
int qianzhui[MAXN],weight[MAXN];
void init_weight()  //初始化权重
{
    weight[0] = 1;
    for(int i=1;i<stringsize;i++)
    {
        weight[i] = 1LL*weight[i-1]*base%mod;
    }
}
void init_qianzhui()    //初始化前缀和
{
    qianzhui[0] = 0;
    for(int i=1;i<=stringsize;i++)
    {
        qianzhui[i] = (1LL*qianzhui[i-1]*base%mod+wenben[i-1])%mod;
    }
}
int mubiao_hax()
{
    int ans=0;
    for(int i=1;i<=mubiaosize;i++)
    {
        ans = (1LL*ans*base%mod+muban[i-1])%mod;
    }
    return ans;
}
int get_hax(int l,int r)
{
    return (qianzhui[r]-1LL*qianzhui[l-1]*weight[r-l+1]%mod+mod)%mod;
}

int main()
{
    freopen("0.in","r",stdin);
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int num=0;
        vector<int> index;
        int mubiaohaxv;
        cin>>stringsize>>mubiaosize;
        getline(cin,wenben);
        init_weight();
        getline(cin,wenben);
        getline(cin,muban);
        init_qianzhui();
        mubiaohaxv = mubiao_hax();
        for(int j=1;j<=stringsize-mubiaosize+1;j++)
        {
            int tmp_hax = get_hax(j,j+mubiaosize-1);
            if(tmp_hax==mubiaohaxv)
            {
                num+=1;
                index.push_back(j);
            }
        }
        printf("%d\n",num);
        for(int i=0;i<num-1;i++)
        {
            printf("%d ",index[i]);
        }
        printf("%d\n",index[num-1]);
    }

    return 0;
}