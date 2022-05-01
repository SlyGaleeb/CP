#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ld long double
const ll N = 2e5 + 5;
int n,m,par[N];
vector<pair<int,ll>>v[N];
bool vis[N];
ll dis[N];
priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>pq;
 
void dijkstra (int node) {
    pq.push({0,node});
    dis[node] = 0;
    while (!pq.empty()) {
        int curr = pq.top().second;
        pq.pop();
        if (vis[curr])
            continue;
        vis[curr] = 1;
        for (auto [c,w]:v[curr]) {
            if (dis[curr]+w<dis[c]) {
            	par[c] = curr;
                dis[c] = dis[curr]+w;
                pq.push({dis[c],c});
            }
        }
    }
}
