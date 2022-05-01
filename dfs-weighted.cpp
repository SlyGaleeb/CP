#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ld long double
const ll N = 2e5 + 5;

bool vis[N];
vector<ll>v[N];
vector<ll>ans;
ll dis[N];

ll mx = 0;

void dfs (int node, int dist) {
	if (vis[node]==1)
		return;
	vis[node] = 1;
	dis[node] = dist;
	mx = max(mx,dist);
	for (auto [x,w]:v[node])
		dfs(x,dist+w);
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
		cin >> x >> y >> w;
		v[x].push_back({y,w});
		v[y].push_back({x,w});
	}
	cin >> a;
	dfs(a);
	for (auto c:ans)
		cout << c << " ";
}