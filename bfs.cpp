#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ld long double
const ll N = 1e5 + 5;
vector<int>v[N];
bool vis[N];
int dis[N];
queue<int>q;
 
void bfs (int node) {
    q.push(node);
    dis[node] = 0;
    vis[node] = 1;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (auto c:v[curr]) {
            if (!vis[c]) {
                dis[c] = dis[curr] + 1;
                q.push(c);
                vis[c] = 1;
            }
        }
    }
}
 
 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n,m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		vis[i] = 0;
	for (int i = 0; i < m; ++i) {
		int a,b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	bfs(1);
}