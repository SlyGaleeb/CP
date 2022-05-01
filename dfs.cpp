#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ld long double
const ll N = 2e5 + 5;

bool vis[N];
vector<ll>v[N];
vector<ll>ans;

void dfs(ll node) {
	if (vis[node]==1)
		return;
	ans.push_back(node);
	vis[node] = 1;
	for (auto u:v[node])
		dfs(u);
	return;
}

int main() 
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll n,m,a;
	cin >> n >> m;
	for (ll i = 1; i <= n; ++i)
		vis[i] = 0;
	for (ll i = 1; i <= m; ++i) {
		ll x,y;
		cin >> x >> y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	cin >> a;
	dfs(a);
	for (auto c:ans)
		cout << c << " ";
}