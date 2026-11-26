// https://atcoder.jp/contests/abc485/tasks/abc485_f

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
struct node{
	int c,v;
}a[MAXN];
bool cmp(node x,node y)
{
	if(x.c == y.c) return x.v > y.v;
	return x.c < y.c;
}
int n,m,ans,cnt;
int dp[MAXN];
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i<=n;i++)
		cin >> a[i].c >> a[i].v;
	for(int T = 0;T<=m;T++)
	{
		cnt = ans = 0;
		sort(a+1,a+n+1,cmp);
		fill(dp,dp+m+2,0);
		for(int i = 1;i<=n;i++)
		{
			if(a[i].c == 0) { cnt += a[i].v; continue; }
			for(int j = m;j>=a[i].c;j--)
				dp[j] = max(dp[j],dp[j-a[i].c] + a[i].v);
		}
		cout << dp[m]+cnt << '\n';
		for(int i = 1;i<=n;i++)
			if(a[i].c > 0)
				a[i].c--;
	}
	return 0;
}
