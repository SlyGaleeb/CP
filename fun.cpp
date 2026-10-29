//count of numbers in range l,r (inclusive) divisble by x

ll fun(ll l, ll r, ll x) {
    return r/x-(l-1)/x;
}
// code end

ll mod_exp(ll base, ll exp, ll mod) {
    base %= mod;
    ll res = 1;
    while (exp> 0) {
        if (exp%2==1) 
            res = res*base%mod;
        base = base*base%mod;
        exp/=2;
    }
    return res;
}

ll nCr (ll n, ll r) {
    if (n<r)
        return 0ll;
    return (fact[n]*mod_exp(fact[r]*fact[n-r]%MOD,MOD-2,MOD))%MOD;
}

ll nCr_large(ll n, ll r) {
    if (n < r || r < 0) return 0;
    ll res = 1;
    for (ll i = 0; i < r; i++) {
        res = res * ((n - i) % MOD) % MOD;
    }
    res = res * inv_fact[r] % MOD;
    return res;
}

ll modInv (ll a, ll MOD) {
    return mod_exp(a, MOD - 2, MOD);
}

string convert_base(ll n, int base) {
    if (n == 0)
        return "0";
    const string DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ll power = 1;
    while (power <= n / base) {
        power *= base;
    }
    string result;
    while (power > 0) {
        ll k = n / power;
        result += DIGITS[k];
        n -= power * k;
        power /= base;
    }
    return result;
}

fact[0] = 1;
for (int i = 1; i <= N; i++) 
    fact[i] = fact[i-1]*i%MOD;
void add_edge() {
    int a,b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
}

void dfs (ll node) {
    vis[node] = 1;
    for (auto c:adj[node]) {
        if (vis[c])
            continue;
        dfs(c);
    }
}

// this only works for trees
void dfs(ll child, ll par) {
    for (auto &c : adj[child]) {
        if (c == par)
            continue;
        dfs(c, child);
    }
}

// longest path dp
void dfs (ll node) {
    vis[node] = 1;
    for (auto c:adj[node]) {
        if (!vis[c])
            dfs(c);
        dp[node] = max(dp[node],dp[c]+1);
    }
} 

void flood(ll r, ll c) {
    if (r<0 || r>=n || c<0 || c>=m || vis[r][c])
        return;
    vis[r][c] = 1;
    flood(r,c+1);
    flood(r,c-1);
    flood(r+1,c);
    flood(r-1,c);
}

vector<int> dis(N, -1);
queue<int> q;
void bfs (ll x) {
    dis[x] = 0;
    q.push(x);
    while (!q.empty()) {
        ll s = q.front(); 
        q.pop();
        for (auto u : adj[s]) {
            if (dis[u]==-1) {
                dis[u] = dis[s]+1;
                q.push(u);
            }
        }
    }
}

vector<int> factor(ll n) {
    vector<int> ret;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            ret.push_back(i);
            n /= i;
        }
    }
    if (n > 1) { ret.push_back(n); }
    return ret;
}

void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i;
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

void sieve_of_eratosthenes(int n)
{
    bool is_prime[n + 1];
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    for (ll p = 2; p * p <= n; p++) {
        if (is_prime[p]) {
            for (ll i = p * p; i <= n; i += p) {
                is_prime[i] = false;
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
}

ll power(ll a, ll n)
{
    ll ans = 1;
    while (n > 0) {
        ll last_bit = (n & 1ll);
        if (last_bit) {
            ans*=a;
        }
        a*=a;
        n>>=1ll;;
    }
    return ans;
}

// DSU start

vector<int> par, height;

void init (int n) {
    height.assign(n, 0);
    par.resize(n);
    for (int i = 0; i < n; ++i)
        par[i] = i;
}

int find (int node) {
    if (par[node] != node) {
        par[node] = find(par[node]);
    }
    return par[node];
}

void unite (int A, int B) {
    if (A == B)
        return;
    int rootA = find(A);
    int rootB = find(B);
    if (height[rootA] <= height[rootB])
        swap(rootA, rootB);
    par[rootB] = rootA;
    if (height[rootA] == height[rootB])
        height[rootA]++; 
}

// DSU end

// Hopcroft Karp

struct HopcroftKarp {
  int n;
  vector<int> l, r, d;
  vector<vector<int>> g;
  HopcroftKarp(int _n, int _m) {
    n = _n;
    int p = _n + _m + 1;
    g.resize(p);
    l.resize(p, 0);
    r.resize(p, 0);
    d.resize(p, 0);
  }
  void add_edge(int u, int v) {
    g[u].push_back(v + n); //right id is increased by n, so is l[u]
  }
  bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n; u++) {
      if (!l[u]) d[u] = 0, q.push(u);
      else d[u] = inf;
    }
    d[0] = inf;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto v : g[u]) {
        if (d[r[v]] == inf) {
          d[r[v]] = d[u] + 1;
          q.push(r[v]);
        }
      }
    }
    return d[0] != inf;
  }
  bool dfs(int u) {
    if (!u) return true;
    for (auto v : g[u]) {
      if(d[r[v]] == d[u] + 1 && dfs(r[v])) {
        l[u] = v;
        r[v] = u;
        return true;
      }
    }
    d[u] = inf;
    return false;
  }
  int maximum_matching() {
    int ans = 0;
    while (bfs()) {
      for(int u = 1; u <= n; u++) if (!l[u] && dfs(u)) ans++;
    }
    return ans;
  }
};

// end

using T = pair<ll, int>;
priority_queue<T, vector<T>, greater<T>> pq;
vector<ll> dis(N, inf);
void dijkstra (ll node) {
    dis[node] = 0;
    pq.emplace(0, node);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dis[u]) 
            continue;
        for (auto &[nd, x] : adj[u]) {
            if (dis[u] + nd < dis[x]) {
                dis[x] = dis[u] + nd;
                pq.emplace(dis[x], x);
            }
        }
    }
}

// Floyd_warshall Start

ll adj[N][N], dis[N][N];

for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
        if (i==j)
            dis[i][j] = 0;
        else if (adj[i][j])
            dis[i][j] = adj[i][j];
        else
            dis[i][j] = 1e18;
    }
}
for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);
        }
    }
}

// Floyd_warshall End

// path from node a to node b in a tree

void dfs(ll v, ll p, ll d) {
  depth[v] = d;
  par[v] = p;
  for(ll c: adj[v])
    if(c != p) dfs(c, v, d + 1);
}
vector<ll> getpath(ll a, ll b) {
  vector<ll> ans, path1, path2;
  path1.push_back(a);
  path2.push_back(b);
  while(a != b) {
    if(depth[a] < depth[b]) path2.push_back(b = par[b]);
    else if(depth[a] > depth[b]) path1.push_back(a = par[a]);
    else if(depth[a] == depth[b]) path1.push_back(a = par[a]), path2.push_back(b = par[b]);
  }
  reverse(path2.begin(), path2.end());
  path2.erase(path2.begin());
  path1.insert(path1.end(), path2.begin(), path2.end());
  return ans = path1;
}

// end

// code to find minimum steps to visit all nodes from a source and go back to that source in an undirected tree

ll dfs(ll node, ll par) {
    ll cost = 0;
    for (auto c:adj[node]) {
        if (c==par)
            continue;
        ll temp = dfs(c,node);
        cost += 2+temp;
    }
    return cost;
}

//end

//count of inversions in an array

ll countAndMerge(vector<ll>& arr, ll l, ll m, ll r) {
    ll n1 = m - l + 1, n2 = r - m;
    vector<ll> left(n1), right(n2);
    for (ll i = 0; i < n1; i++)
        left[i] = arr[i + l];
    for (ll j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];
    ll res = 0;
    ll i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) 
            arr[k++] = left[i++];
        else {
            arr[k++] = right[j++];
            res += (n1 - i);
        }
    }
    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];
 
    return res;
}
ll countInv(vector<ll>& arr, ll l, ll r){
    ll res = 0;
    if (l < r) {
        ll m = (r + l) / 2;
        res += countInv(arr, l, m);
        res += countInv(arr, m + 1, r);
        res += countAndMerge(arr, l, m, r);
    }
    return res;
}

ll inversionCount(vector<ll>&v) {
    ll n = v.size();
    return countInv(v, 0, n - 1);
}

// end


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef tree<pair<ll, ll>, null_type, less<pair<ll, ll>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Centroid Decomposition start

set<ll>adj[N];
vector<ll>dad(N),sub(N),del(N);

ll dfs_size(ll u, ll p) {
    sub[u] = 1;
    for (auto v:adj[u]) {
        if (v==p || del[v])
            continue;
        sub[u] += dfs_size(v,u);
    }
    return sub[u];
}

ll dfs_centroid(ll u, ll p, ll n) {
    for (auto v:adj[u]) {
        if (v!=p && sub[v]>n/2 && !del[v])
            return dfs_centroid(v,u,n);
    }
    return u;
}

void build_centroid (ll u, ll p) {
    ll n = dfs_size(u,p);
    ll centroid = dfs_centroid(u,p,n);
    del[centroid] = 1;
    dad[centroid] = p;
    vector<ll>neighbors(all(adj[centroid]));
    for (auto v:neighbors) {
        if (del[v])
            continue;
        build_centroid(v,centroid);
    }
}

void init_centroid_decomposition () {
    del.assign(n+1,0);
    dad.assign(n+1,-1);
    sub.assign(n+1,-1);
    build_centroid(1,-1);
}

// Centroid Decomposition end

// LCA start

//Important!!!
//Call dfs(1, -1)

const int N = 3e5 + 9, LG = 18;

vector<int> g[N];
int par[N][LG + 1], dep[N], sz[N];

void dfs(int u, int p = 0) {
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    sz[u] = 1;

    for (int i = 1; i <= LG; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];

    for (auto v : g[u])
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
}

int lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);

    for (int k = LG; k >= 0; k--)
        if (dep[par[u][k]] >= dep[v])
            u = par[u][k];

    if (u == v)
        return u;

    for (int k = LG; k >= 0; k--)
        if (par[u][k] != par[v][k]) {
            u = par[u][k];
            v = par[v][k];
        }

    return par[u][0];
}

int kth(int u, int k) {
    assert(k >= 0);

    for (int i = 0; i <= LG; i++)
        if (k & (1 << i))
            u = par[u][i];

    return u;
}

int dist(int u, int v) {
    int l = lca(u, v);
    return dep[u] + dep[v] - (dep[l] << 1);
}

// kth node from u to v, 0th node is u
int go(int u, int v, int k) {
    int l = lca(u, v);
    int d = dep[u] + dep[v] - (dep[l] << 1);

    assert(k <= d);

    if (dep[l] + k <= dep[u])
        return kth(u, k);

    k -= dep[u] - dep[l];
    return kth(v, dep[v] - dep[l] - k);
}

// LCA end

int n; // number of vertices
vector<vector<int>> adj; // adjacency list of graph
vector<bool> visited;
vector<int> ans;

void dfs(int v) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs(u);
        }
    }
    ans.push_back(v);
}

void topological_sort() {
    visited.assign(n, false);
    ans.clear();
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    reverse(ans.begin(), ans.end());
}


//Bridge Finding

vector<bool> visited(N,0);
vector<ll> tin(N,-1), low(N,-1);
ll timer;

void dfs(ll v, ll p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    bool parent_skipped = false;
    for (ll to : adj[v]) {
        if (to == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                // The edge (v,to) is a bridge
        }
    }
}

// Bridge finding end

//tree diameter

ll dia = 0, nxt;
 
void tdfs(int child, int parent, int dis=0) {
    if (dis>dia)
        dia = dis, nxt = child;
    for (auto c:adj[child]) {
        if (c==parent)
            continue;
        tdfs(c,child,dis+1);
    }
}

//

//Miller-Rabin, Pollard Rho Prime Factorization

using u128 = __uint128_t;
ll modmul(ll a, ll b, ll m) {
    return (u128)a * b % m;
}
ll modpow(ll a, ll e, ll m) {
    ll r = 1;
    while (e) {
        if (e & 1) r = modmul(r, a, m);
        a = modmul(a, a, m);
        e >>= 1;
    }
    return r;
}
bool isPrime(ll n) {
    if (n < 2) return false;
    for (ll p : {2,3,5,7,11,13,17,19,23,29,31,37})
        if (n % p == 0) return n == p;

    ll d = n - 1, s = 0;
    while ((d & 1) == 0) d >>= 1, ++s;

    auto check = [&](ll a) {
        if (a % n == 0) return true;
        ll x = modpow(a, d, n);
        if (x == 1 || x == n - 1) return true;
        for (ll r = 1; r < s; r++) {
            x = modmul(x, x, n);
            if (x == n - 1) return true;
        }
        return false;
    };

    for (ll a : {2LL,325LL,9375LL,28178LL,450775LL,9780504LL,1795265022LL})
        if (!check(a)) return false;
    return true;
}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll f(ll x, ll c, ll mod) {
    return (modmul(x, x, mod) + c) % mod;
}
ll pollard(ll n) {
    if (n % 2 == 0) return 2;
    uniform_int_distribution<ll> dist(2, n - 2);
    while (true) {
        ll x = dist(rng), y = x, c = dist(rng), d = 1;
        while (d == 1) {
            x = f(x, c, n);
            y = f(f(y, c, n), c, n);
            d = __gcd(abs(x - y), n);
        }
        if (d != n) return d;
    }
}
void factor(ll n, vector<ll> &res) {
    if (n == 1) return;
    if (isPrime(n)) {
        res.push_back(n);
        return;
    }
    ll d = pollard(n);
    factor(d, res);
    factor(n / d, res);
}

//usage (in main write this)

ll x;
cin >> x;
vector<ll>fact;
factor(x,fact);
sort(all(fact));

// the prime factors of x are now stored in the vector fact.

//Pollard Rho end

// Code for solving system of 2 linear equations

pair<double,double> fun(const tuple<double,double,double>&p, const tuple<double,double,double>&q) {
    auto &[a1,b1,c1] = p;
    auto &[a2,b2,c2] = q;
    double det = a1*b2-a2*b1;
    if (det==0)
        return {inf,inf};
    double dx = c1*b2-c2*b1, dy = c2*a1-c1*a2;
    return {dx/det,dy/det};
}

// code end

//Range query point update with BIT

struct BIT {
    vector<ll> sums;
    int n;

    void init(int n) {
        sums.assign(n + 1, 0);
        this->n = n;
    }

    void build(const vector<ll> &v) {
        for (int i = 1; i <= n; ++i) {
            sums[i] += v[i - 1];
            int par = i + (i & -i);
            if (par <= n)
                sums[par] += sums[i];
        }
    }

    void update(int idx, ll x) {
        for (int i = idx; i <= n; i += (i & -i)) 
            sums[i] += x;
    }

    ll query(int r) {
        ll res = 0;
        for (int i = r; i > 0; i -= (i & -i))
            res += sums[i];
        return res;
    }

    ll query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

// Simple segment tree. Supports range query and point update.

struct segtree {
    ll NEUTRAL_ELEMENT = 0;
    ll size;
    vector<ll> sums;

    ll single (ll val) {
        return val;
    }

    ll merge (ll a, ll b) {
        return a+b;
    }

    void init (ll n) {
        size = 1;
        while (size<n)
            size *= 2;
        sums.assign(2*size,NEUTRAL_ELEMENT);
    }

    void build (vector<ll>&v, ll x, ll lx, ll rx) {
        if (rx-lx==1) {
            if (lx<(ll)v.size())
                sums[x] = single(v[lx]);
            return;
        }
        ll mid  = (lx+rx)/2;
        build(v,2*x+1,lx,mid);
        build(v,2*x+2,mid,rx);
        sums[x] = merge(sums[2*x+1],sums[2*x+2]);
    }

    void build (vector<ll>&v) {
        build(v,0,0,size);
    }

    void set (ll i, ll val, ll x, ll lx, ll rx) {
        if (rx-lx==1) {
            sums[x] = single(val);
            return;
        }
        ll mid = (lx+rx)/2;
        if (i<mid) 
            set(i,val,2*x+1,lx,mid);
        else
            set(i,val,2*x+2,mid,rx);
        sums[x] = merge(sums[2*x+1],sums[2*x+2]);
    }

    void set(ll i, ll val) {
        set(i,val,0,0,size);
    }

    ll query(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx>=r || rx<=l)
            return NEUTRAL_ELEMENT;
        if (lx>=l && rx<=r)
            return sums[x];
        ll mid = (lx+rx)/2;
        ll s1 = query(l,r,2*x+1,lx,mid);
        ll s2 = query(l,r,2*x+2,mid,rx);
        return merge(s1,s2);
    }

    ll query(ll l, ll r) {
        return query(l,r,0,0,size);
    }
};

//code end

// Segment Tree with Lazy Propagation

struct segtree {
    ll size;
    vector<ll>operations,sums;
    ll NO_OP = inf;
 
    ll op (ll a, ll b) {
        return a + b;
    }
 
    void apply_op (ll &a, ll b) {
        a = op(a,b);
    }
 
    void init (ll n) {
        size = 1;
        while (size<n)
            size *= 2;
        operations.assign(2*size,NO_OP);
        sums.assign(2*size,0);
    }
 
    void build (vector<ll>&v, ll x, ll lx, ll rx) {
        if (rx-lx==1) {
            if (lx<(ll)v.size())
                sums[x] = v[lx];
            return;
        }
        ll mid  = (lx+rx)/2;
        build(v,2*x+1,lx,mid);
        build(v,2*x+2,mid,rx);
        sums[x] = (sums[2*x+1]+sums[2*x+2]);
    }
 
    void build (vector<ll>&v) {
        build(v,0,0,size);
    }
 
    void propagate (ll x, ll lx, ll rx) {
        if (rx-lx==1 || operations[x]==NO_OP)
            return;
        ll mid = (lx+rx)/2ll;
        apply_op(operations[2*x+1],operations[x]);
        apply_op(operations[2*x+2],operations[x]);
        apply_op(sums[2*x+1],operations[x]*(mid-lx));
        apply_op(sums[2*x+2],operations[x]*(rx-mid));
        operations[x] = NO_OP;
    }
 
    void modify(ll l, ll r, ll val, ll x, ll lx, ll rx) {
        propagate(x,lx,rx);
        if (lx>=r || rx<=l)
            return;
        if (lx>=l && rx<=r) {
            apply_op(operations[x],val);
            apply_op(sums[x],val*(rx-lx));
            return;
        }
        ll mid = (lx+rx)/2;
        modify(l,r,val,2*x+1,lx,mid);
        modify(l,r,val,2*x+2,mid,rx);
        sums[x] = sums[2*x+1]+sums[2*x+2];
    }
 
    void modify(ll l, ll r, ll val) {
        modify(l,r,val,0,0,size);
    }
 
    ll get (ll l, ll r, ll x, ll lx, ll rx) {
        propagate(x,lx,rx);
        if (lx>=r || rx<=l) 
            return 0;
        if (lx>=l && rx<=r)
            return sums[x];
        ll mid = (lx+rx)/2ll;
        return get(l,r,2*x+1,lx,mid)+get(l,r,2*x+2,mid,rx);
    }
 
    ll get(ll l, ll r) {
        return get(l,r,0,0,size);
    }
};

// Code end

// String Hashing 

vector<pair<ll,ll>> compute_hash(const string &s) {
    const ll p1 = 127;
    const ll p2 = 131;
    const ll m1 = 1e9 + 7;
    const ll m2 = 1e9 + 9;
    ll p_pow1 = 1;
    ll p_pow2 = 1;
    ll n = s.size();
    vector<pair<ll,ll>>res(n+1,{0,0});
    ll x = 0, y = 0;
    for (ll i = 0; i < n; ++i) {
        (x += ((s[i]+1)*p_pow1%m1)) %= m1;
        (y += ((s[i]+1)*p_pow2%m2)) %= m2;
        res[i+1] = {x,y};
        (p_pow1*=p1) %= m1;
        (p_pow2*=p2) %= m2;
    }
    return res;
}

// Code to find hash value of substring 

vector<ll>p1(N+5),p2(N+5),inv_p1(N+5),inv_p2(N+5);
p1[0] = 1, p2[0] = 1;

for (ll i = 1; i <= N; ++i) 
    p1[i] = p1[i-1]*127ll%MOD;
for (ll i = 1; i <= N; ++i) 
    p2[i] = p2[i-1]*131ll%MOD2;

inv_p1[N] = mod_exp(p1[N],MOD-2,MOD);
inv_p2[N] = mod_exp(p2[N],MOD2-2,MOD2);

for (ll i = N-1; i >= 0; --i)
    inv_p1[i] = inv_p1[i+1]*127ll%MOD;   
for (ll i = N-1; i >= 0; --i)
    inv_p2[i] = inv_p2[i+1]*131ll%MOD2;  

pair<ll,ll>sub_hash (ll l, ll r, ll n, vector<pair<ll,ll>>&H, vector<ll>&inv_p1, vector<ll>&inv_p2) {
    return {(H[r+1].F-H[l].F+MOD)%MOD*inv_p1[l]%MOD,(H[r+1].S-H[l].S+MOD2)%MOD2*inv_p2[l]%MOD2};
}

pair<ll,ll> repeat_hash(pair<ll,ll> Hs, ll n, ll k) {
    ll pn1 = mod_exp(p1[n], k, MOD);
    ll pn2 = mod_exp(p2[n], k, MOD2);

    ll inv1 = mod_exp((p1[n] - 1 + MOD) % MOD, MOD - 2, MOD);
    ll inv2 = mod_exp((p2[n] - 1 + MOD2) % MOD2, MOD2 - 2, MOD2);

    ll sum1 = (pn1 - 1 + MOD) % MOD * inv1 % MOD;
    ll sum2 = (pn2 - 1 + MOD2) % MOD2 * inv2 % MOD2;

    ll h1 = Hs.first  * sum1 % MOD;
    ll h2 = Hs.second * sum2 % MOD2;

    return {h1, h2};
}

pair<ll,ll> pop_last_char_hash(const pair<ll,ll>& hs, char last_char,ll n) {
    ll c = last_char - 'a' + 1;

    ll val1 = c * p1[n-1] % MOD;
    ll val2 = c * p2[n-1] % MOD2;

    ll h1 = (hs.first - val1 + MOD) % MOD;
    ll h2 = (hs.second - val2 + MOD2) % MOD2;

    return {h1, h2};
}

// Code end

// Bipartite matching
vector<int>team(N,-1);
void dfs (int node, int col) {
    vis[node] = 1;
    team[node] = col;
    for (auto c:adj[node]) {
        if (!vis[c])
            dfs(c,col^1);
    }
}

// Code end

struct segtree {
    ll size;
    vector<ll>operations;
 
    ll single (ll val) {
        return val;
    }
 
    ll merge (ll a, ll b) {
        return a+b;
    }
 
    void init (ll n) {
        size = 1;
        while (size<n)
            size *= 2;
        operations.assign(2*size,0ll);
    }

    void build(vector<ll>&v) {
        for (ll i = 0; i < (ll)v.size(); i++) {
            operations[size-1+i] = v[i];
        }
    }
 
    ll get (ll i, ll x, ll lx, ll rx) {
        if (rx-lx==1) {
            return operations[x];
        }
        ll mid = (lx+rx)/2;
        ll res;
        if (i<mid) 
            res = get(i,2*x+1,lx,mid);
        else
            res = get(i,2*x+2,mid,rx);
        return res+operations[x];
    }
 
    ll get(ll i) {
        return get(i,0,0,size);
    }
 
    void add(ll l, ll r, ll val, ll x, ll lx, ll rx) {
        if (lx>=r || rx<=l)
            return;
        if (lx>=l && rx<=r) {
            operations[x] += val;
            return;
        }
        ll mid = (lx+rx)/2;
        add(l,r,val,2*x+1,lx,mid);
        add(l,r,val,2*x+2,mid,rx);
    }
 
    void add(ll l, ll r, ll val) {
        add(l,r,val,0,0,size);
    }
};

vector<ll>adj[N],subtree(N,1);
 
void dfs(ll child, ll par) {
    for (auto c:adj[child]) {
        if (c==par)
            continue;
        dfs(c,child);
        subtree[child] += subtree[c];
    }
}

// Mobius calculation code

ll mob[N];
void mobius() {
    mob[1] = 1;
    for (int i = 2; i < N; ++i) {
        mob[i]--;
        for (int j = i + i; j < N; j += i) 
            mob[j] -= mob[i];
    }
}


// code end

// Sparse Table

struct sparseTable {
    int n, lg;
    vector<vector<int>> t;

    void init(int n) {
        this->n = n;
        this->lg = 31 - __builtin_clz(n) + 1;
        t.assign(n, vector<int>(lg, 0));
    }

    void build(const vector<int> &v) {
        for(int i = 0; i < n; ++i) {
            t[i][0] = v[i];
        }
        for(int k = 1; k < lg; ++k) {
            for(int i = 0; i + (1 << k) - 1 < n; ++i) {
                t[i][k] = min(t[i][k - 1], t[i + (1 << (k - 1))][k - 1]);
            }
        }
    }

    int query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return min(t[l][k], t[r - (1 << k) + 1][k]);
    }
};

// end

// Cycle in directed graph

int n;
vector<vector<int>> adj;
vector<char> color;
vector<int> parent;
int cycle_start, cycle_end;

bool dfs(int v) {
    color[v] = 1;
    for (int u : adj[v]) {
        if (color[u] == 0) {
            parent[u] = v;
            if (dfs(u))
                return true;
        } else if (color[u] == 1) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
    }
    color[v] = 2;
    return false;
}

void find_cycle() {
    color.assign(n, 0);
    parent.assign(n, -1);
    cycle_start = -1;

    for (int v = 0; v < n; v++) {
        if (color[v] == 0 && dfs(v))
            break;
    }

    if (cycle_start == -1) {
        cout << "Acyclic" << endl;
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycle_start);
        reverse(cycle.begin(), cycle.end());

        cout << "Cycle found: ";
        for (int v : cycle)
            cout << v << " ";
        cout << endl;
    }
}

// cycle in undirected graph

int n;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> parent;
int cycle_start, cycle_end;

bool dfs(int v, int par) { // passing vertex and its parent vertex
    visited[v] = true;
    for (int u : adj[v]) {
        if(u == par) continue; // skipping edge to parent vertex
        if (visited[u]) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
        parent[u] = v;
        if (dfs(u, parent[u]))
            return true;
    }
    return false;
}

void find_cycle() {
    visited.assign(n, false);
    parent.assign(n, -1);
    cycle_start = -1;

    for (int v = 0; v < n; v++) {
        if (!visited[v] && dfs(v, parent[v]))
            break;
    }

    if (cycle_start == -1) {
        cout << "Acyclic" << endl;
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycle_start);

        cout << "Cycle found: ";
        for (int v : cycle)
            cout << v << " ";
        cout << endl;
    }
}

// Graph bipartite check
int n;
vector<vector<int>> adj;

vector<int> side(n, -1);
bool is_bipartite = true;
queue<int> q;
for (int st = 0; st < n; ++st) {
    if (side[st] == -1) {
        q.push(st);
        side[st] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : adj[v]) {
                if (side[u] == -1) {
                    side[u] = side[v] ^ 1;
                    q.push(u);
                } else {
                    is_bipartite &= side[u] != side[v];
                }
            }
        }
    }
}

cout << (is_bipartite ? "YES" : "NO") << endl;

// MST Kruskal

vector<int> parent, rank;

void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int n;
vector<Edge> edges;

int cost = 0;
vector<Edge> result;
parent.resize(n);
rank.resize(n);
for (int i = 0; i < n; i++)
    make_set(i);

sort(edges.begin(), edges.end());

for (Edge e : edges) {
    if (find_set(e.u) != find_set(e.v)) {
        cost += e.weight;
        result.push_back(e);
        union_sets(e.u, e.v);
    }
}

//lca binary lifting

int n, l;
vector<vector<int>> adj;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}
// end

// LCA in O(1)

template <class T>
struct RMQ { // 0-based
  vector<vector<T>> rmq;
  T kInf = numeric_limits<T>::max();
  void build(const vector<T>& V) {
    int n = V.size(), on = 1, dep = 1;
    while (on < n) on *= 2, ++dep;
    rmq.assign(dep, V);
 
    for (int i = 0; i < dep - 1; ++i)
      for (int j = 0; j < n; ++j) {
        rmq[i + 1][j] = min(rmq[i][j], rmq[i][min(n - 1, j + (1 << i))]);
      }
  }
  T query(int a, int b) { // [a, b)
    if (b <= a) return kInf;
    int dep = 31 - __builtin_clz(b - a); // log(b - a)
    return min(rmq[dep][a], rmq[dep][b - (1 << dep)]);
  }
};

struct LCA { // 0-based
  vector<int> enter, depth, exxit;
  vector<vector<int>> G;
  vector<pair<int, int>> linear;
  RMQ<pair<int, int>> rmq;
  int timer = 0;
  LCA() {} 
  LCA(int n) : enter(n, -1), exxit(n, -1), depth(n), G(n), linear(2 * n) {}
  void dfs(int node, int dep) {
    linear[timer] = {dep, node};
    enter[node] = timer++;
    depth[node] = dep;
    for (auto vec : G[node])
    if (enter[vec] == -1) {
      dfs(vec, dep + 1);
      linear[timer++] = {dep, node};
    }
    exxit[node] = timer;
  }
  void add_edge(int a, int b) {
    G[a].push_back(b);
    G[b].push_back(a);
  }
  void build(int root) {
    dfs(root, 0);
    rmq.build(linear);
  }
  int query(int a, int b) {
    a = enter[a], b = enter[b];
    return rmq.query(min(a, b), max(a, b) + 1).second;
  }
  int dist(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[query(a, b)];
  }
};
 
LCA lca;

// end

// LIS

int lis(vector<int> const& a) {
    int n = a.size();
    const int INF = 1e9;
    vector<int> d(n+1, INF);
    d[0] = -INF;
    for (int i = 0; i < n; i++) {
        int l = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[l-1] < a[i] && a[i] < d[l])
            d[l] = a[i];
    }
    int ans = 0;
    for (int l = 0; l <= n; l++) {
        if (d[l] < INF)
            ans = l;
    }
    return ans;
}

// Template for queries on trees

// Reminder: Make everything 0-indexed !!!!

vector<ll> adj[N], subtree(N, 1), pos(N), val, v(N);

void dfs(ll child, ll par) {
    val.pb(v[child]);
    pos[child] = (ll)val.size() - 1;
    for (auto &c : adj[child]) {
        if (c == par)
            continue;
        dfs(c, child);
        subtree[child] += subtree[c];
    }
}

// end


// Strongly Connected Components
// Kosaraju's Algorithm
// Reminder: This code is 0-indexed!!!!

constexpr ll inf = 1e18;
const ll N = 5e5 + 5;
const ll M = 505;
const ll MOD = 998244353; // 998244353 // 1000000007

vector<bool> vis;

void dfs (int node, vector<int> adj[], vector<int> &order) {
    vis[node] = 1;
    for (auto &c : adj[node]) {
        if (!vis[c])
            dfs(c, adj, order);
    }
    order.pb(node);
}

void pre() {

}

void init (ll n) {

}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> adj[n], adj_rev[n];
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj_rev[v].pb(u);
    }
    vis.assign(n, false);
    vector<int> order;
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            dfs(i, adj, order);
        }
    }
    reverse(all(order));
    vis.assign(n, false);
    vector<vector<int>> SCCs;
    for (auto &c : order) {
        if (!vis[c]) {
            vector<int> component;
            dfs(c, adj_rev, component);
            SCCs.pb(component);
        }
    }
    cout << SCCs.size() << "\n";
    for (auto &c : SCCs) {
        cout << c.size() << " ";
        for (auto &d : c) 
            cout << d << " ";
        cout << "\n";
    }
} 

//Binary Trie

struct Trie {
    static const int B = 31;
    
    // nxt[id][0] and nxt[id][1] store the indices of the children
    vector<array<int, 2>> nxt;
    vector<int> sz;
    
    // Stores detached node indices so we can recycle them during erase()
    vector<int> free_list;
    int root;

    Trie() {
        // Reserve memory upfront to prevent slow reallocations during insertion.
        // 1.5e7 is roughly 500k inserts * 31 bits. 
        nxt.reserve(N);
        sz.reserve(N);
        
        // Index 0 is strictly reserved to act as our "NULL" pointer.
        nxt.push_back({0, 0});
        sz.push_back(0);
        
        // Root is initialized at index 1
        root = new_node();
    }

    void init() {
        // .clear() on vectors of primitive types is an O(1) operation conceptually.
        // It sets the size to 0 but KEEPS the reserved capacity in RAM.
        nxt.clear();
        sz.clear();
        free_list.clear();
        
        // Restore index 0 as our strict "NULL" equivalent
        nxt.push_back({0, 0});
        sz.push_back(0);
        
        // Re-assign the root node for the new test case
        root = new_node();
    }

    int new_node() {
        // Recycle memory if erase() has freed up nodes
        if (!free_list.empty()) {
            int id = free_list.back();
            free_list.pop_back();
            nxt[id][0] = nxt[id][1] = 0;
            sz[id] = 0;
            return id;
        }
        // Otherwise, allocate a new index
        nxt.push_back({0, 0});
        sz.push_back(0);
        return nxt.size() - 1;
    }

    void insert(int val) {
        int cur = root;
        sz[cur]++;
        for (int i = B - 1; i >= 0; i--) {
            int b = (val >> i) & 1;
            
            // if (cur->nxt[b] == NULL) -> if (nxt[cur][b] == 0)
            if (nxt[cur][b] == 0) {
                nxt[cur][b] = new_node();
            }
            cur = nxt[cur][b];
            sz[cur]++;
        }
    }

    int query(int x, int k) { 
        int cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            if (cur == 0) break; // Replaces `if (cur == NULL)`
            
            int b1 = (x >> i) & 1;
            int b2 = (k >> i) & 1;
            
            if (b2 == 1) {
                if (nxt[cur][b1] != 0) ans += sz[nxt[cur][b1]];
                cur = nxt[cur][!b1];
            } else {
                cur = nxt[cur][b1];
            }
        }
        return ans;
    }

    int get_max(int x) { 
        int cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            int k = (x >> i) & 1;
            if (nxt[cur][!k] != 0) {
                cur = nxt[cur][!k];
                ans = (ans << 1) | 1;
            } else {
                cur = nxt[cur][k];
                ans <<= 1;
            }
        }
        return ans;
    }

    int get_min(int x) { 
        int cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            int k = (x >> i) & 1;
            if (nxt[cur][k] != 0) {
                cur = nxt[cur][k];
                ans <<= 1;
            } else {
                cur = nxt[cur][!k];
                ans = (ans << 1) | 1;
            }
        }
        return ans;
    }

    int get_kth(int x, int k) { 
        int cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            if (cur == 0) break;
            
            int b = (x >> i) & 1;
            int cnt_0_path = 0;
            if (nxt[cur][b] != 0) cnt_0_path = sz[nxt[cur][b]];
            
            if (k <= cnt_0_path) {
                cur = nxt[cur][b];
                ans <<= 1; 
            } else {
                k -= cnt_0_path; 
                cur = nxt[cur][!b];
                ans = (ans << 1) | 1;
            }
        }
        return ans;
    }

    // Helper to recursively harvest detached node indices
    void del(int cur) {
        if (cur == 0) return;
        if (nxt[cur][0] != 0) del(nxt[cur][0]);
        if (nxt[cur][1] != 0) del(nxt[cur][1]);
        free_list.push_back(cur);
    }

    void erase(int val) {
        int cur = root;
        sz[cur]--; 
        for (int i = B - 1; i >= 0; i--) {
            int b = (val >> i) & 1;
            sz[nxt[cur][b]]--; 
            
            // If child size drops to 0, harvest the memory and detach it
            if (sz[nxt[cur][b]] == 0) {
                del(nxt[cur][b]);  
                nxt[cur][b] = 0; // Pointer is strictly zeroed out
                return; 
            }
            cur = nxt[cur][b];
        }
    }
};

// end

//Topological Sort

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> indeg(n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        indeg[v]++;
    }
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (indeg[i] == 0) 
            q.push(i);
    }
    vector<int> topsorted;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topsorted.push_back(node);
        for (auto &c : adj[node]) {
            indeg[c]--;
            if (indeg[c] == 0)
                q.push(c);
        }
    }
    if (topsorted.size() != n) {
        cout << "[ ]";
        return 0;
    }
    for (auto &c : topsorted)
        cout << c << " ";
}

// end

// #pragma GCC optimize("Ofast")
// #pragma GCC optimization ("O3")
// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
typedef long long ll;
#define ld long double
#define ull unsigned long long
#define F first
#define S second
#define gcd __gcd
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound
using namespace std;
using namespace __gnu_pbds;
 
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
//typedef tree<pair<ll, ll>, null_type, less<pair<ll, ll>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
 
constexpr ll inf = 1e18;
const ll N = 2e5 + 5;
const ll M = 505;
const ll MOD = 998244353; // 998244353 // 1000000007
 
void pre() {
 
}
 
void init (ll n) {
 
}
 
void solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    int len = (int)sqrt(n + 0.0) + 1;
    vector<ll> b(len, 0);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            l--, r--;
            int bl = l / len, br = r / len;
            if (bl == br) {
                for (int i = l; i <= r; ++i)
                    v[i] += x;
            }
            else {
                for (int i = l; i < (bl + 1) * len; ++i)
                    v[i] += x;
                for (int i = bl + 1; i < br; ++i)
                    b[i] += x;
                for (int i = br * len; i <= r; ++i)
                    v[i] += x;
            }
        }
        else {
            int idx;
            cin >> idx;
            idx--;
            ll ans = v[idx] + b[idx / len];
            cout << ans << "\n"; 
        }
    }
}   
 
void brute() {
 
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    //init();
    //pre();
 
    int tc = 1, C = 1;
    //cin >> tc;
    cout << fixed << setprecision(10);
    while (tc--) {
        //cout << "Case #" << C++ << ": ";
 
        solve();
        //brute();
    }
}

//euler tour
struct segtree {
    ll NEUTRAL_ELEMENT = 0;
    ll size;
    vector<ll>sums;
 
    ll single (ll val) {
        return val;
    }
 
    ll merge (ll a, ll b) {
        return a+b;
    }
 
    void init (ll n) {
        size = 1;
        while (size<n)
            size *= 2;
        sums.assign(2*size,NEUTRAL_ELEMENT);
    }
 
    void build (vector<ll>&v, ll x, ll lx, ll rx) {
        if (rx-lx==1) {
            if (lx<(ll)v.size())
                sums[x] = single(v[lx]);
            return;
        }
        ll mid  = (lx+rx)/2;
        build(v,2*x+1,lx,mid);
        build(v,2*x+2,mid,rx);
        sums[x] = merge(sums[2*x+1],sums[2*x+2]);
    }
 
    void build (vector<ll>&v) {
        build(v,0,0,size);
    }
 
    void set (ll i, ll val, ll x, ll lx, ll rx) {
        if (rx-lx==1) {
            sums[x] = single(val);
            return;
        }
        ll mid = (lx+rx)/2;
        if (i<mid) 
            set(i,val,2*x+1,lx,mid);
        else
            set(i,val,2*x+2,mid,rx);
        sums[x] = merge(sums[2*x+1],sums[2*x+2]);
    }
 
    void set(ll i, ll val) {
        set(i,val,0,0,size);
    }
 
    ll query(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx>=r || rx<=l)
            return NEUTRAL_ELEMENT;
        if (lx>=l && rx<=r)
            return sums[x];
        ll mid = (lx+rx)/2;
        ll s1 = query(l,r,2*x+1,lx,mid);
        ll s2 = query(l,r,2*x+2,mid,rx);
        return merge(s1,s2);
    }
 
    ll query(ll l, ll r) {
        return query(l,r,0,0,size);
    }
};
 
vector<ll> adj[N], subtree(N, 1), pos(N), val, v(N);
 
void dfs(ll child, ll par) {
    val.pb(v[child]);
    pos[child] = (ll)val.size() - 1;
    for (auto &c : adj[child]) {
        if (c == par)
            continue;
        dfs(c, child);
        subtree[child] += subtree[c];
    }
}
 
void pre() {
 
}
 
void init (ll n) {
 
}
 
void solve() {
    ll n, q;
    cin >> n >> q;
    for (ll i = 0; i < n; ++i)
        cin >> v[i];
    for (ll i = 0; i < n-1; ++i) {
        ll a, b;
        cin >> a >>  b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dfs(0, -1);
    segtree st;
    st.init(n);
    st.build(val);
    while (q--) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll s, x;
            cin >> s >> x;
            s--;
            st.set(pos[s], x);
        }
        else {
            ll s;
            cin >> s;
            s--;
            cout << st.query(pos[s], pos[s] + subtree[s]) << "\n";
        }
    }
}

// 2-SAT
struct twosat {
    int n;  // total size combining +, -. must be even.
    vector<vector<int>> g, gt;
    vector<bool> vis, res;
    vector<int> comp;
    stack<int> ts;

    twosat(int vars = 0) {
        n = vars << 1;
        g.resize(n);
        gt.resize(n);
    }

    // zero indexed, be careful
    // if you want to force variable a to be true in OR or XOR combination
    // add addOR (a,1,a,1);
    // if you want to force variable a to be false in OR or XOR combination
    // add addOR (a,0,a,0);

    // (x_a or (not x_b))-> af=1,bf=0
    void addOR(int a, bool af, int b, bool bf) {
        a += a + (af ^ 1);
        b += b + (bf ^ 1);
        g[a ^ 1].push_back(b);  // !a => b
        g[b ^ 1].push_back(a);  // !b => a
        gt[b].push_back(a ^ 1);
        gt[a].push_back(b ^ 1);
    }

    // (!x_a xor !x_b)-> af=0, bf=0
    void addXOR(int a, bool af, int b, bool bf) {
        addOR(a, af, b, bf);
        addOR(a, !af, b, !bf);
    }

    void _add(int a, bool af, int b, bool bf) {
        a += a + (af ^ 1);
        b += b + (bf ^ 1);
        g[a].push_back(b);
        gt[b].push_back(a);
    }

    // add this type of condition ->
    // add(a,af,b,bf) means if a is af then b must need to be bf
    void add(int a, bool af, int b, bool bf) {
        _add(a, af, b, bf);
        _add(b, !bf, a, !af);
    }

    void dfs1(int u) {
        vis[u] = true;
        for (int v : g[u]) {
            if (!vis[v]) dfs1(v);
        }
        ts.push(u);
    }

    void dfs2(int u, int c) {
        comp[u] = c;
        for (int v : gt[u]) {
            if (comp[v] == -1) dfs2(v, c);
        }
    }

    bool ok() {
        vis.assign(n, false);
        for (int i = 0; i < n; ++i) {
            if (!vis[i]) dfs1(i);
        }

        int scc = 0;
        comp.assign(n, -1);

        while (!ts.empty()) {
            int u = ts.top();
            ts.pop();
            if (comp[u] == -1) dfs2(u, scc++);
        }

        res.assign(n / 2, false);
        for (int i = 0; i < n; i += 2) {
            if (comp[i] == comp[i + 1]) return false;
            res[i / 2] = (comp[i] > comp[i + 1]);
        }
        return true;
    }
};

//end


// Prim's Algorithm (MST)

using T = pair<ll, int>;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<T>> adj(n + 1);
    while (m--) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        adj[a].eb(w, b);
        adj[b].eb(w, a);
    }
    vector<bool> selected(n + 1, 0);
    priority_queue<T, vector<T>, greater<T>> pq;
    ll minWeight = 0;
    pq.emplace(0, 1);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (selected[u])
            continue;
        selected[u] = 1;
        minWeight += d;
        for (auto &[nd, v] : adj[u]) {
            if (!selected[v])
                pq.emplace(nd, v);
        }
    }
    if (count(all(selected), 0) != 1)
        cout << "IMPOSSIBLE";
    else
        cout << minWeight;
}

// KMP

void kmp(string &s) {
    for (int i = 1; i < s.size(); ++i) {
        int j = pi[i - 1];
        while (s[i] != s[j] && j > 0)
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
}

// string hashing

int power(long long n, long long k, const int mod) {
  int ans = 1 % mod;
  n %= mod;
  if (n < 0) n += mod;
  while (k) {
    if (k & 1) ans = (long long) ans * n % mod;
    n = (long long) n * n % mod;
    k >>= 1;
  }
  return ans;
}

const int MOD1 = 127657753, MOD2 = 987654319;
const int p1 = 137, p2 = 277;
int ip1, ip2;
pair<int, int> pw[N], ipw[N];
void prec() {
  pw[0] =  {1, 1};
  for (int i = 1; i < N; i++) {
    pw[i].first = 1LL * pw[i - 1].first * p1 % MOD1;
    pw[i].second = 1LL * pw[i - 1].second * p2 % MOD2;
  }
  ip1 = power(p1, MOD1 - 2, MOD1);
  ip2 = power(p2, MOD2 - 2, MOD2);
  ipw[0] =  {1, 1};
  for (int i = 1; i < N; i++) {
    ipw[i].first = 1LL * ipw[i - 1].first * ip1 % MOD1;
    ipw[i].second = 1LL * ipw[i - 1].second * ip2 % MOD2;
  }

}
struct Hashing {
  int n;
  string s; // 0 - indexed
  vector<pair<int, int>> hs; // 1 - indexed
  Hashing() {}
  Hashing(string _s) {
    n = _s.size();
    s = _s;
    hs.emplace_back(0, 0);
    for (int i = 0; i < n; i++) {
      pair<int, int> p;
      p.first = (hs[i].first + 1LL * pw[i].first * s[i] % MOD1) % MOD1;
      p.second = (hs[i].second + 1LL * pw[i].second * s[i] % MOD2) % MOD2;
      hs.push_back(p);
    }
  }
  pair<int, int> get_hash(int l, int r) { // 1 - indexed
    assert(1 <= l && l <= r && r <= n);
    pair<int, int> ans;
    ans.first = (hs[r].first - hs[l - 1].first + MOD1) * 1LL * ipw[l - 1].first % MOD1;
    ans.second = (hs[r].second - hs[l - 1].second + MOD2) * 1LL * ipw[l - 1].second % MOD2;
    return ans;
  }
  pair<int, int> get_hash() {
    return get_hash(1, n);
  }
};

//Geometry

#include<bits/stdc++.h>
using namespace std;

// https://victorlecomte.com/cp-geo.pdf
const int N = 3e5 + 9;

const double inf = 1e100;
const double eps = 1e-9;
const double PI = acos((double)-1.0);
int sign(double x) { return (x > eps) - (x < -eps); }
struct PT {
    double x, y;
    PT() { x = 0, y = 0; }
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y)    {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator * (const double a) const { return PT(x * a, y * a); }
    friend PT operator * (const double &a, const PT &b) { return PT(a * b.x, a * b.y); }
    PT operator / (const double a) const { return PT(x / a, y / a); }
    bool operator == (PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator != (PT a) const { return !(*this == a); }
    bool operator < (PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator > (PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
    double norm() { return sqrt(x * x + y * y); }
    double norm2() { return x * x + y * y; }
    PT perp() { return PT(-y, x); }
    double arg() { return atan2(y, x); }
    PT truncate(double r) { // returns a vector with norm r and having same direction
        double k = norm();
        if (!sign(k)) return *this;
        r /= k;
        return PT(x * r, y * r);
    }
};
istream &operator >> (istream &in, PT &p) { return in >> p.x >> p.y; }
ostream &operator << (ostream &out, PT &p) { return out << "(" << p.x << "," << p.y << ")"; }
inline double dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
inline double dist2(PT a, PT b) { return dot(a - b, a - b); }
inline double dist(PT a, PT b) { return sqrt(dot(a - b, a - b)); }
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
inline double cross2(PT a, PT b, PT c) { return cross(b - a, c - a); }
inline int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }
PT perp(PT a) { return PT(-a.y, a.x); }
PT rotateccw90(PT a) { return PT(-a.y, a.x); }
PT rotatecw90(PT a) { return PT(a.y, -a.x); }
PT rotateccw(PT a, double t) { return PT(a.x * cos(t) - a.y * sin(t), a.x * sin(t) + a.y * cos(t)); }
PT rotatecw(PT a, double t) { return PT(a.x * cos(t) + a.y * sin(t), -a.x * sin(t) + a.y * cos(t)); }
double SQ(double x) { return x * x; }
double rad_to_deg(double r) { return (r * 180.0 / PI); }
double deg_to_rad(double d) { return (d * PI / 180.0); }
double get_angle(PT a, PT b) {
    double costheta = dot(a, b) / a.norm() / b.norm();
    return acos(max((double)-1.0, min((double)1.0, costheta)));
}
bool is_point_in_angle(PT b, PT a, PT c, PT p) { // does point p lie in angle <bac
    assert(orientation(a, b, c) != 0);
    if (orientation(a, c, b) < 0) swap(b, c);
    return orientation(a, c, p) >= 0 && orientation(a, b, p) <= 0;
}
bool half(PT p) {
    return p.y > 0.0 || (p.y == 0.0 && p.x < 0.0);
}
void polar_sort(vector<PT> &v) { // sort points in counterclockwise
    sort(v.begin(), v.end(), [](PT a,PT b) {
        return make_tuple(half(a), 0.0, a.norm2()) < make_tuple(half(b), cross(a, b), b.norm2());
    });
}
void polar_sort(vector<PT> &v, PT o) { // sort points in counterclockwise with respect to point o
    sort(v.begin(), v.end(), [&](PT a,PT b) {
        return make_tuple(half(a - o), 0.0, (a - o).norm2()) < make_tuple(half(b - o), cross(a - o, b - o), (b - o).norm2());
    });
}
struct line {
    PT a, b; // goes through points a and b
    PT v; double c;  //line form: direction vec [cross] (x, y) = c 
    line() {}
    //direction vector v and offset c
    line(PT v, double c) : v(v), c(c) {
        auto p = get_points();
        a = p.first; b = p.second;
    }
    // equation ax + by + c = 0
    line(double _a, double _b, double _c) : v({_b, -_a}), c(-_c) {
        auto p = get_points();
        a = p.first; b = p.second;
    }
    // goes through points p and q
    line(PT p, PT q) : v(q - p), c(cross(v, p)), a(p), b(q) {}
        pair<PT, PT> get_points() { //extract any two points from this line
        PT p, q; double a = -v.y, b = v.x; // ax + by = c
        if (sign(a) == 0) {
            p = PT(0, c / b);
            q = PT(1, c / b);
        }
        else if (sign(b) == 0) {
            p = PT(c / a, 0);
            q = PT(c / a, 1);
        }
        else {
            p = PT(0, c / b);
            q = PT(1, (c - a) / b);
        }
        return {p, q};
        }
    // ax + by + c = 0
    array<double, 3> get_abc() {
        double a = -v.y, b = v.x;
        return {a, b, -c};
    }
    // 1 if on the left, -1 if on the right, 0 if on the line
    int side(PT p) { return sign(cross(v, p) - c); }
    // line that is perpendicular to this and goes through point p
    line perpendicular_through(PT p) { return {p, p + perp(v)}; }
    // translate the line by vector t i.e. shifting it by vector t
    line translate(PT t) { return {v, c + cross(v, t)}; }
    // compare two points by their orthogonal projection on this line
    // a projection point comes before another if it comes first according to vector v
    bool cmp_by_projection(PT p, PT q) { return dot(v, p) < dot(v, q); }
    line shift_left(double d) {
        PT z = v.perp().truncate(d);
        return line(a + z, b + z);
    }
    double dist(PT p) { 
        return fabs(cross(v, p) - c) / v.norm(); 
    }
};
// find a point from a through b with distance d
PT point_along_line(PT a, PT b, double d) {
    assert(a != b);
    return a + (((b - a) / (b - a).norm()) * d);
}
// projection point c onto line through a and b  assuming a != b
PT project_from_point_to_line(PT a, PT b, PT c) {
    return a + (b - a) * dot(c - a, b - a) / (b - a).norm2();
}
// reflection point c onto line through a and b  assuming a != b
PT reflection_from_point_to_line(PT a, PT b, PT c) {
    PT p = project_from_point_to_line(a,b,c);
    return p + p - c;
}
// minimum distance from point c to line through a and b
double dist_from_point_to_line(PT a, PT b, PT c) {
    return fabs(cross(b - a, c - a) / (b - a).norm());
}
// returns true if  point p is on line segment ab
bool is_point_on_seg(PT a, PT b, PT p) {
    if (fabs(cross(p - b, a - b)) < eps) {
        if (p.x < min(a.x, b.x) - eps || p.x > max(a.x, b.x) + eps) return false;
        if (p.y < min(a.y, b.y) - eps || p.y > max(a.y, b.y) + eps) return false;
        return true;
    }
    return false;
}
// minimum distance point from point c to segment ab that lies on segment ab
PT project_from_point_to_seg(PT a, PT b, PT c) {
    double r = dist2(a, b);
    if (sign(r) == 0) return a;
    r = dot(c - a, b - a) / r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b - a) * r;
}
// minimum distance from point c to segment ab
double dist_from_point_to_seg(PT a, PT b, PT c) {
    return dist(c, project_from_point_to_seg(a, b, c));
}
// 0 if not parallel, 1 if parallel, 2 if collinear
int is_parallel(PT a, PT b, PT c, PT d) {
    double k = fabs(cross(b - a, d - c));
    if (k < eps){
        if (fabs(cross(a - b, a - c)) < eps && fabs(cross(c - d, c - a)) < eps) return 2;
        else return 1;
    }
    else return 0;
}
// check if two lines are same
bool are_lines_same(PT a, PT b, PT c, PT d) {
    if (fabs(cross(a - c, c - d)) < eps && fabs(cross(b - c, c - d)) < eps) return true;
    return false;
}
// bisector vector of <abc
PT angle_bisector(PT &a, PT &b, PT &c){
    PT p = a - b, q = c - b;
    return p + q * sqrt(dot(p, p) / dot(q, q));
}
// 1 if point is ccw to the line, 2 if point is cw to the line, 3 if point is on the line
int point_line_relation(PT a, PT b, PT p) {
    int c = sign(cross(p - a, b - a));
    if (c < 0) return 1;
    if (c > 0) return 2;
    return 3;
}
// intersection point between ab and cd assuming unique intersection exists
bool line_line_intersection(PT a, PT b, PT c, PT d, PT &ans) {
    double a1 = a.y - b.y, b1 = b.x - a.x, c1 = cross(a, b);
    double a2 = c.y - d.y, b2 = d.x - c.x, c2 = cross(c, d);
    double det = a1 * b2 - a2 * b1;
    if (det == 0) return 0;
    ans = PT((b1 * c2 - b2 * c1) / det, (c1 * a2 - a1 * c2) / det);
    return 1;
}
// intersection point between segment ab and segment cd assuming unique intersection exists
bool seg_seg_intersection(PT a, PT b, PT c, PT d, PT &ans) {
    double oa = cross2(c, d, a), ob = cross2(c, d, b);
    double oc = cross2(a, b, c), od = cross2(a, b, d);
    if (oa * ob < 0 && oc * od < 0){
        ans = (a * ob - b * oa) / (ob - oa);
        return 1;
    }
    else return 0;
}
// intersection point between segment ab and segment cd assuming unique intersection may not exists
// se.size()==0 means no intersection
// se.size()==1 means one intersection
// se.size()==2 means range intersection
set<PT> seg_seg_intersection_inside(PT a,  PT b,  PT c,  PT d) {
    PT ans;
    if (seg_seg_intersection(a, b, c, d, ans)) return {ans};
    set<PT> se;
    if (is_point_on_seg(c, d, a)) se.insert(a);
    if (is_point_on_seg(c, d, b)) se.insert(b);
    if (is_point_on_seg(a, b, c)) se.insert(c);
    if (is_point_on_seg(a, b, d)) se.insert(d);
    return se;
}
// intersection  between segment ab and line cd
// 0 if do not intersect, 1 if proper intersect, 2 if segment intersect
int seg_line_relation(PT a, PT b, PT c, PT d) {
    double p = cross2(c, d, a);
    double q = cross2(c, d, b);
    if (sign(p) == 0 && sign(q) == 0) return 2;
    else if (p * q < 0) return 1;
    else return 0;
}
// intersection between segament ab and line cd assuming unique intersection exists
bool seg_line_intersection(PT a, PT b, PT c, PT d, PT &ans) {
    bool k = seg_line_relation(a, b, c, d);
    assert(k != 2);
    if (k) line_line_intersection(a, b, c, d, ans);
    return k;
}
// minimum distance from segment ab to segment cd
double dist_from_seg_to_seg(PT a, PT b, PT c, PT d) {
    PT dummy;
    if (seg_seg_intersection(a, b, c, d, dummy)) return 0.0;
    else return min({dist_from_point_to_seg(a, b, c), dist_from_point_to_seg(a, b, d), 
        dist_from_point_to_seg(c, d, a), dist_from_point_to_seg(c, d, b)});
}
// minimum distance from point c to ray (starting point a and direction vector b)
double dist_from_point_to_ray(PT a, PT b, PT c) {
    b = a + b;
    double r = dot(c - a, b - a);
    if (r < 0.0) return dist(c, a);
    return dist_from_point_to_line(a, b, c);
}
// starting point as and direction vector ad
bool ray_ray_intersection(PT as, PT ad, PT bs, PT bd) {
    double dx = bs.x - as.x, dy = bs.y - as.y;
    double det = bd.x * ad.y - bd.y * ad.x;
    if (fabs(det) < eps) return 0;
    double u = (dy * bd.x - dx * bd.y) / det;
    double v = (dy * ad.x - dx * ad.y) / det;
    if (sign(u) >= 0 && sign(v) >= 0) return 1;
    else return 0;
}
double ray_ray_distance(PT as, PT ad, PT bs, PT bd) {
    if (ray_ray_intersection(as, ad, bs, bd)) return 0.0;
    double ans = dist_from_point_to_ray(as, ad, bs);
    ans = min(ans, dist_from_point_to_ray(bs, bd, as));
    return ans;
}
struct circle {
    PT p; double r;
    circle() {}
    circle(PT _p, double _r): p(_p), r(_r) {};
    // center (x, y) and radius r
    circle(double x, double y, double _r): p(PT(x, y)), r(_r) {};
    // circumcircle of a triangle
    // the three points must be unique
    circle(PT a, PT b, PT c) {
        b = (a + b) * 0.5;
        c = (a + c) * 0.5;
        line_line_intersection(b, b + rotatecw90(a - b), c, c + rotatecw90(a - c), p);
        r = dist(a, p);
    }
    // inscribed circle of a triangle
    // pass a bool just to differentiate from circumcircle
    circle(PT a, PT b, PT c, bool t) {
        line u, v;
        double m = atan2(b.y - a.y, b.x - a.x), n = atan2(c.y - a.y, c.x - a.x);
        u.a = a;
        u.b = u.a + (PT(cos((n + m)/2.0), sin((n + m)/2.0)));
        v.a = b;
        m = atan2(a.y - b.y, a.x - b.x), n = atan2(c.y - b.y, c.x - b.x);
        v.b = v.a + (PT(cos((n + m)/2.0), sin((n + m)/2.0)));
        line_line_intersection(u.a, u.b, v.a, v.b, p);
        r = dist_from_point_to_seg(a, b, p);
    }
    bool operator == (circle v) { return p == v.p && sign(r - v.r) == 0; }
    double area() { return PI * r * r; }
    double circumference() { return 2.0 * PI * r; }
};
//0 if outside, 1 if on circumference, 2 if inside circle
int circle_point_relation(PT p, double r, PT b) {
    double d = dist(p, b);
    if (sign(d - r) < 0) return 2;
    if (sign(d - r) == 0) return 1;
    return 0;
}
// 0 if outside, 1 if on circumference, 2 if inside circle
int circle_line_relation(PT p, double r, PT a, PT b) {
    double d = dist_from_point_to_line(a, b, p);
    if (sign(d - r) < 0) return 2;
    if (sign(d - r) == 0) return 1;
    return 0;
}
//compute intersection of line through points a and b with
//circle centered at c with radius r > 0
vector<PT> circle_line_intersection(PT c, double r, PT a, PT b) {
    vector<PT> ret;
    long long ax = round(a.x), ay = round(a.y);
    long long bx = round(b.x), by = round(b.y);
    long long cx = round(c.x), cy = round(c.y);
    long long ri = round(r);
    
    __int128 vx = bx - ax, vy = by - ay;
    __int128 ux = ax - cx, uy = ay - cy;
    
    __int128 A_int = vx * vx + vy * vy;
    if (A_int == 0) return ret;
    __int128 B_int = ux * vx + uy * vy;
    __int128 C_int = ux * ux + uy * uy - (__int128)ri * ri;
    
    __int128 D_int = B_int * B_int - A_int * C_int;
    if (D_int < 0) return ret;
    
    double A = (double)A_int;
    double B = (double)B_int;
    double D = (double)D_int;
    
    ret.push_back(a + (b - a) * (-B + sqrt(D)) / A);
    if (D > 0) ret.push_back(a + (b - a) * (-B - sqrt(D)) / A);
    return ret;
}
//5 - outside and do not intersect
//4 - intersect outside in one point
//3 - intersect in 2 points
//2 - intersect inside in one point
//1 - inside and do not intersect
int circle_circle_relation(PT a, double r, PT b, double R) {
    double d = dist(a, b);
    if (sign(d - r - R) > 0)  return 5;
    if (sign(d - r - R) == 0) return 4;
    double l = fabs(r - R);
    if (sign(d - r - R) < 0 && sign(d - l) > 0) return 3;
    if (sign(d - l) == 0) return 2;
    if (sign(d - l) < 0) return 1;
    assert(0); return -1;
}
vector<PT> circle_circle_intersection(PT a, double r, PT b, double R) {
    if (a == b && sign(r - R) == 0) return {PT(1e18, 1e18)};
    vector<PT> ret;
    double d = sqrt(dist2(a,  b));
    if (d > r + R || d + min(r,  R) < max(r,  R)) return ret;
    double x = (d * d - R * R + r * r) / (2 * d);
    double y = sqrt(r * r - x * x);
    PT v = (b - a) / d;
    ret.push_back(a + v * x  +  rotateccw90(v) * y);
    if (y > 0) ret.push_back(a + v * x - rotateccw90(v) * y);
    return ret;
}
// returns two circle c1, c2 through points a, b and of radius r
// 0 if there is no such circle, 1 if one circle, 2 if two circle
int get_circle(PT a, PT b, double r, circle &c1, circle &c2) {
    vector<PT> v = circle_circle_intersection(a, r, b, r);
    int t = v.size();
    if (!t) return 0;
    c1.p = v[0], c1.r = r;
    if (t == 2) c2.p = v[1], c2.r = r;
    return t;
}
// returns two circle c1, c2 which is tangent to line u,  goes through
// point q and has radius r1; 0 for no circle, 1 if c1 = c2 , 2 if c1 != c2
int get_circle(line u, PT q, double r1, circle &c1, circle &c2) {
    double d = dist_from_point_to_line(u.a, u.b, q);
    if (sign(d - r1 * 2.0) > 0) return 0;
    if (sign(d) == 0) {
        cout << u.v.x << ' ' << u.v.y << '\n';
        c1.p = q + rotateccw90(u.v).truncate(r1);
        c2.p = q + rotatecw90(u.v).truncate(r1);
        c1.r = c2.r = r1;
        return 2;
    }
    line u1 = line(u.a + rotateccw90(u.v).truncate(r1), u.b + rotateccw90(u.v).truncate(r1));
    line u2 = line(u.a + rotatecw90(u.v).truncate(r1), u.b + rotatecw90(u.v).truncate(r1));
    circle cc = circle(q, r1);
    PT p1, p2; vector<PT> v;
    v = circle_line_intersection(q, r1, u1.a, u1.b);
    if (!v.size()) v = circle_line_intersection(q, r1, u2.a, u2.b);
    v.push_back(v[0]);
    p1 = v[0], p2 = v[1];
    c1 = circle(p1, r1);
    if (p1 == p2) {
        c2 = c1;
        return 1;
    }
    c2 = circle(p2, r1);
    return 2;
}
// returns the circle such that for all points w on the circumference of the circle
// dist(w, a) : dist(w, b) = rp : rq
// rp != rq
// https://en.wikipedia.org/wiki/Circles_of_Apollonius
circle get_apollonius_circle(PT p, PT q, double rp, double rq ){
    rq *= rq ;
    rp *= rp ;
    double a = rq - rp ;
    assert(sign(a));
    double g = rq * p.x - rp * q.x ; g /= a ;
    double h = rq * p.y - rp * q.y ; h /= a ;
    double c = rq * p.x * p.x - rp * q.x * q.x + rq * p.y * p.y - rp * q.y * q.y ;
    c /= a ;
    PT o(g, h);
    double r = g * g + h * h - c ;
    r = sqrt(r);
    return circle(o,r);
}
// returns area of intersection between two circles
double circle_circle_area(PT a, double r1, PT b, double r2) {
    double d = (a - b).norm();
    if(r1 + r2 < d + eps) return 0;
    if(r1 + d < r2 + eps) return PI * r1 * r1;
    if(r2 + d < r1 + eps) return PI * r2 * r2;
    double theta_1 = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d)), 
        theta_2 = acos((r2 * r2 + d * d - r1 * r1)/(2 * r2 * d));
    return r1 * r1 * (theta_1 - sin(2 * theta_1)/2.) + r2 * r2 * (theta_2 - sin(2 * theta_2)/2.);
}
// tangent lines from point q to the circle
int tangent_lines_from_point(PT p, double r, PT q, line &u, line &v) {
    int x = sign(dist2(p, q) - r * r);
    if (x < 0) return 0; // point in cricle
    if (x == 0) { // point on circle
        u = line(q, q + rotateccw90(q - p));
        v = u;
        return 1;
    }
    double d = dist(p, q);
    double l = r * r / d;
    double h = sqrt(r * r - l * l);
    u = line(q, p + ((q - p).truncate(l) + (rotateccw90(q - p).truncate(h))));
    v = line(q, p + ((q - p).truncate(l) + (rotatecw90(q - p).truncate(h))));
    return 2;
}
// returns outer tangents line of two circles
// if inner == 1 it returns inner tangent lines
int tangents_lines_from_circle(PT c1, double r1, PT c2, double r2, bool inner, line &u, line &v) {
    if (inner) r2 = -r2;
    PT d = c2 - c1;
    double dr = r1 - r2, d2 = d.norm2(), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0) {
        assert(h2 != 0);
        return 0;
    }
    vector<pair<PT, PT>>out;
    for (int tmp: {- 1, 1}) {
        PT v = (d * dr + rotateccw90(d) * sqrt(h2) * tmp) / d2;
        out.push_back({c1 + v * r1, c2 + v * r2});
    }
    u = line(out[0].first, out[0].second);
    if (out.size() == 2) v = line(out[1].first, out[1].second);
    return 1 + (h2 > 0);
}
// O(n^2 log n)
// https://vjudge.net/problem/UVA-12056
struct CircleUnion {
    int n;
    double x[2020], y[2020], r[2020];
    int covered[2020];
    vector<pair<double, double> > seg, cover;
    double arc, pol;
    inline int sign(double x) {return x < -eps ? -1 : x > eps;}
    inline int sign(double x, double y) {return sign(x - y);}
    inline double SQ(const double x) {return x * x;}
    inline double dist(double x1, double y1, double x2, double y2) {return sqrt(SQ(x1 - x2) + SQ(y1 - y2));}
    inline double angle(double A, double B, double C) {
        double val = (SQ(A) + SQ(B) - SQ(C)) / (2 * A * B);
        if (val < -1) val = -1;
        if (val > +1) val = +1;
        return acos(val);
    }
    CircleUnion() {
        n = 0;
        seg.clear(), cover.clear();
        arc = pol = 0;
    }
    void init() {
        n = 0;
        seg.clear(), cover.clear();
        arc = pol = 0;
    }
    void add(double xx, double yy, double rr) {
        x[n] = xx, y[n] = yy, r[n] = rr, covered[n] = 0, n++;
    }
    void getarea(int i, double lef, double rig) {
        arc += 0.5 * r[i] * r[i] * (rig - lef - sin(rig - lef));
        double x1 = x[i] + r[i] * cos(lef), y1 = y[i] + r[i] * sin(lef);
        double x2 = x[i] + r[i] * cos(rig), y2 = y[i] + r[i] * sin(rig);
        pol += x1 * y2 - x2 * y1;
    }
    double solve() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (!sign(x[i] - x[j]) && !sign(y[i] - y[j]) && !sign(r[i] - r[j])) {
                    r[i] = 0.0;
                    break;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && sign(r[j] - r[i]) >= 0 && sign(dist(x[i], y[i], x[j], y[j]) - (r[j] - r[i])) <= 0) {
                    covered[i] = 1;
                    break;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (sign(r[i]) && !covered[i]) {
                seg.clear();
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        double d = dist(x[i], y[i], x[j], y[j]);
                        if (sign(d - (r[j] + r[i])) >= 0 || sign(d - abs(r[j] - r[i])) <= 0) {
                            continue;
                        }
                        double alpha = atan2(y[j] - y[i], x[j] - x[i]);
                        double beta = angle(r[i], d, r[j]);
                        pair<double, double> tmp(alpha - beta, alpha + beta);
                        if (sign(tmp.first) <= 0 && sign(tmp.second) <= 0) {
                            seg.push_back(pair<double, double>(2 * PI + tmp.first, 2 * PI + tmp.second));
                        }
                        else if (sign(tmp.first) < 0) {
                            seg.push_back(pair<double, double>(2 * PI + tmp.first, 2 * PI));
                            seg.push_back(pair<double, double>(0, tmp.second));
                        }
                        else {
                            seg.push_back(tmp);
                        }
                    }
                }
                sort(seg.begin(), seg.end());
                double rig = 0;
                for (vector<pair<double, double> >::iterator iter = seg.begin(); iter != seg.end(); iter++) {
                    if (sign(rig - iter->first) >= 0) {
                        rig = max(rig, iter->second);
                    }
                    else {
                        getarea(i, rig, iter->first);
                        rig = iter->second;
                    }
                }
                if (!sign(rig)) {
                    arc += r[i] * r[i] * PI;
                }
                else {
                    getarea(i, rig, 2 * PI);
                }
            }
        }
        return pol / 2.0 + arc;
    }
} CU; 
double area_of_triangle(PT a, PT b, PT c) {
    return fabs(cross(b - a, c - a) * 0.5);
}
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
int is_point_in_triangle(PT a, PT b, PT c, PT p) {
    if (sign(cross(b - a,c - a)) < 0) swap(b, c);
    int c1 = sign(cross(b - a,p - a));
    int c2 = sign(cross(c - b,p - b));
    int c3 = sign(cross(a - c,p - c));
    if (c1<0 || c2<0 || c3 < 0) return 1;
    if (c1 + c2 + c3 != 3) return 0;
    return -1;
}
double perimeter(vector<PT> &p) {
    double ans=0; int n = p.size();
    for (int i = 0; i < n; i++) ans += dist(p[i], p[(i + 1) % n]);
    return ans;
}
double area(vector<PT> &p) {
    double ans = 0; int n = p.size();
    for (int i = 0; i < n; i++) ans += cross(p[i], p[(i + 1) % n]);
    return fabs(ans) * 0.5;
}
// centroid of a (possibly non-convex) polygon, 
// assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.  Note that the centroid is often known as
// the "center of gravity" or "center of mass".
PT centroid(vector<PT> &p) {
    int n = p.size(); PT c(0, 0);
    double sum = 0;
    for (int i = 0; i < n; i++) sum += cross(p[i], p[(i + 1) % n]);
    double scale = 3.0 * sum;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        c = c + (p[i] + p[j]) * cross(p[i], p[j]);
    }
    return c / scale;
}
// 0 if cw, 1 if ccw
bool get_direction(vector<PT> &p) {
    double ans = 0; int n = p.size();
    for (int i = 0; i < n; i++) ans += cross(p[i], p[(i + 1) % n]);
    if (sign(ans) > 0) return 1;
    return 0;
}
// it returns a point such that the sum of distances
// from that point to all points in p  is minimum
// O(n log^2 MX)
PT geometric_median(vector<PT> p) {
    auto tot_dist = [&](PT z) {
        double res = 0;
        for (int i = 0; i < p.size(); i++) res += dist(p[i], z);
        return res;
    };
    auto findY = [&](double x) {
        double yl = -1e5, yr = 1e5;
        for (int i = 0; i < 60; i++) {
            double ym1 = yl + (yr - yl) / 3;
            double ym2 = yr - (yr - yl) / 3;
            double d1 = tot_dist(PT(x, ym1));
            double d2 = tot_dist(PT(x, ym2));
            if (d1 < d2) yr = ym2;
            else yl = ym1;
        }
        return pair<double, double> (yl, tot_dist(PT(x, yl)));
    };
    double xl = -1e5, xr = 1e5;
    for (int i = 0; i < 60; i++) {
        double xm1 = xl + (xr - xl) / 3;
        double xm2 = xr - (xr - xl) / 3;
        double y1, d1, y2, d2;
        auto z = findY(xm1); y1 = z.first; d1 = z.second;
        z = findY(xm2); y2 = z.first; d2 = z.second;
        if (d1 < d2) xr = xm2;
        else xl = xm1;
    }
    return {xl, findY(xl).first };
}
vector<PT> convex_hull(vector<PT> &p) {
    if (p.size() <= 1) return p;
    vector<PT> v = p;
    sort(v.begin(), v.end());
    vector<PT> up, dn;
    for (auto& p : v) {
        while (up.size() > 1 && orientation(up[up.size() - 2], up.back(), p) >= 0) {
            up.pop_back();
        }
        while (dn.size() > 1 && orientation(dn[dn.size() - 2], dn.back(), p) <= 0) {
            dn.pop_back();
        }
        up.push_back(p);
        dn.push_back(p);
    }
    v = dn;
    if (v.size() > 1) v.pop_back();
    reverse(up.begin(), up.end());
    up.pop_back();
    for (auto& p : up) {
        v.push_back(p);
    }
    if (v.size() == 2 && v[0] == v[1]) v.pop_back();
    return v;
}
 //checks if convex or not
bool is_convex(vector<PT> &p) {
    bool s[3]; s[0] = s[1] = s[2] = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        int k = (j + 1) % n;
        s[sign(cross(p[j] - p[i], p[k] - p[i])) + 1] = 1;
        if (s[0] && s[2]) return 0;
    }
    return 1;
}
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
// it must be strictly convex, otherwise make it strictly convex first
int is_point_in_convex(vector<PT> &p, const PT& x) { // O(log n)
    int n = p.size(); assert(n >= 3);
    int a = orientation(p[0], p[1], x), b = orientation(p[0], p[n - 1], x);
    if (a < 0 || b > 0) return 1;
    int l = 1, r = n - 1;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (orientation(p[0], p[mid], x) >= 0) l = mid;
        else r = mid;
    }
    int k = orientation(p[l], p[r], x);
    if (k <= 0) return -k;
    if (l == 1 && a == 0) return 0;
    if (r == n - 1 && b == 0) return 0;
    return -1;
}
bool is_point_on_polygon(vector<PT> &p, const PT& z) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (is_point_on_seg(p[i], p[(i + 1) % n], z)) return 1;
    }
    return 0;
}
// returns 1e9 if the point is on the polygon 
int winding_number(vector<PT> &p, const PT& z) { // O(n)
    if (is_point_on_polygon(p, z)) return 1e9;
    int n = p.size(), ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        bool below = p[i].y < z.y;
        if (below != (p[j].y < z.y)) {
            auto orient = orientation(z, p[j], p[i]);
            if (orient == 0) return 0;
            if (below == (orient > 0)) ans += below ? 1 : -1;
        }
    }
    return ans;
}
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
int is_point_in_polygon(vector<PT> &p, const PT& z) { // O(n)
    int k = winding_number(p, z);
    return k == 1e9 ? 0 : k == 0 ? 1 : -1;
}
// id of the vertex having maximum dot product with z
// polygon must need to be convex
// top - upper right vertex
// for minimum dot product negate z and return -dot(z, p[id])
int extreme_vertex(vector<PT> &p, const PT &z, const int top) { // O(log n)
    int n = p.size();
    if (n == 1) return 0;
    double ans = dot(p[0], z); int id = 0;
    if (dot(p[top], z) > ans) ans = dot(p[top], z), id = top;
    int l = 1, r = top - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (dot(p[mid + 1], z) >= dot(p[mid], z)) l = mid + 1;
        else r = mid;
    }
    if (dot(p[l], z) > ans) ans = dot(p[l], z), id = l;
    l = top + 1, r = n - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (dot(p[(mid + 1) % n], z) >= dot(p[mid], z)) l = mid + 1;
        else r = mid;
    }
    l %= n;
    if (dot(p[l], z) > ans) ans = dot(p[l], z), id = l;
    return id;
}
// maximum distance from any point on the perimeter to another point on the perimeter
double diameter(vector<PT> &p) {
    int n = (int)p.size();
    if (n == 1) return 0;
    if (n == 2) return dist(p[0], p[1]);
    double ans = 0;
    int i = 0, j = 1;
    while (i < n) {
        while (cross(p[(i + 1) % n] - p[i], p[(j + 1) % n] - p[j]) >= 0) {
            ans = max(ans, dist2(p[i], p[j]));
            j = (j + 1) % n;
        }
        ans = max(ans, dist2(p[i], p[j]));
        i++;
    }
    return sqrt(ans);
}
// minimum distance between two parallel lines (non necessarily axis parallel)
// such that the polygon can be put between the lines
double width(vector<PT> &p) {
    int n = (int)p.size();
    if (n <= 2) return 0;
    double ans = inf;
    int i = 0, j = 1;
    while (i < n) {
        while (cross(p[(i + 1) % n] - p[i], p[(j + 1) % n] - p[j]) >= 0) j = (j + 1) % n;
        ans = min(ans, dist_from_point_to_line(p[i], p[(i + 1) % n], p[j]));
        i++;
    }
    return ans;
}
// minimum perimeter
double minimum_enclosing_rectangle(vector<PT> &p) {
    int n = p.size();
    if (n <= 2) return perimeter(p);
    int mndot = 0; double tmp = dot(p[1] - p[0], p[0]);
    for (int i = 1; i < n; i++) {
        if (dot(p[1] - p[0], p[i]) <= tmp) {
            tmp = dot(p[1] - p[0], p[i]);
            mndot = i;
        }
    }
    double ans = inf;
    int i = 0, j = 1, mxdot = 1;
    while (i < n) {
        PT cur = p[(i + 1) % n] - p[i];
        while (cross(cur, p[(j + 1) % n] - p[j]) >= 0) j = (j + 1) % n;
        while (dot(p[(mxdot + 1) % n], cur) >= dot(p[mxdot], cur)) mxdot = (mxdot + 1) % n;
        while (dot(p[(mndot + 1) % n], cur) <= dot(p[mndot], cur)) mndot = (mndot + 1) % n;
        ans = min(ans, 2.0 * ((dot(p[mxdot], cur) / cur.norm() - dot(p[mndot], cur) / cur.norm()) + dist_from_point_to_line(p[i], p[(i + 1) % n], p[j])));
        i++;
    }
    return ans;
}
// given n points, find the minimum enclosing circle of the points
// call convex_hull() before this for faster solution
// expected O(n)
circle minimum_enclosing_circle(vector<PT> &p) {
    random_shuffle(p.begin(), p.end());
    int n = p.size();
    circle c(p[0], 0);
    for (int i = 1; i < n; i++) {
        if (sign(dist(c.p, p[i]) - c.r) > 0) {
            c = circle(p[i], 0);
            for (int j = 0; j < i; j++) {
                if (sign(dist(c.p, p[j]) - c.r) > 0) {
                    c = circle((p[i] + p[j]) / 2, dist(p[i], p[j]) / 2);
                    for (int k = 0; k < j; k++) {
                        if (sign(dist(c.p, p[k]) - c.r) > 0) {
                            c = circle(p[i], p[j], p[k]);
                        }
                    }
                }
            }
        }
    }
    return c;
}
// returns a vector with the vertices of a polygon with everything 
// to the left of the line going from a to b cut away.
vector<PT> cut(vector<PT> &p, PT a, PT b) {
    vector<PT> ans;
    int n = (int)p.size();
    for (int i = 0; i < n; i++) {
        double c1 = cross(b - a, p[i] - a);
        double c2 = cross(b - a, p[(i + 1) % n] - a);
        if (sign(c1) >= 0) ans.push_back(p[i]);
        if (sign(c1 * c2) < 0) {
            if (!is_parallel(p[i], p[(i + 1) % n], a, b)) {
                PT tmp; line_line_intersection(p[i], p[(i + 1) % n], a, b, tmp);
                ans.push_back(tmp);
            }
        }
    }
    return ans;
}
// not necessarily convex, boundary is included in the intersection
// returns total intersected length
// it returns the sum of the lengths of the portions of the line that are inside the polygon
double polygon_line_intersection(vector<PT> p, PT a, PT b) {
    int n = p.size();
    p.push_back(p[0]);
    line l = line(a, b);
    double ans = 0.0;
    vector< pair<double, int> > vec;
    for (int i = 0; i < n; i++) {
        int s1 = orientation(a, b, p[i]);
        int s2 = orientation(a, b, p[i + 1]);
        if (s1 == s2) continue;
        line t = line(p[i], p[i + 1]);
        PT inter = (t.v * l.c - l.v * t.c) / cross(l.v, t.v);
        double tmp = dot(inter, l.v);
        int f;
        if (s1 > s2) f = s1 && s2 ? 2 : 1;
        else f = s1 && s2 ? -2 : -1;
        vec.push_back(make_pair((f > 0 ? tmp - eps : tmp + eps), f)); // keep eps very small like 1e-12
    }
    sort(vec.begin(), vec.end());
    for (int i = 0, j = 0; i + 1 < (int)vec.size(); i++){
        j += vec[i].second;
        if (j) ans += vec[i + 1].first - vec[i].first; // if this portion is inside the polygon
        // else ans = 0; // if we want the maximum intersected length which is totally inside the polygon, uncomment this and take the maximum of ans
    }
    ans = ans / sqrt(dot(l.v, l.v));
    p.pop_back();
    return ans;
}
// given a convex polygon p, and a line ab and the top vertex of the polygon
// returns the intersection of the line with the polygon
// it returns the indices of the edges of the polygon that are intersected by the line
// so if it returns i, then the line intersects the edge (p[i], p[(i + 1) % n])
array<int, 2> convex_line_intersection(vector<PT> &p, PT a, PT b, int top) {
    int end_a = extreme_vertex(p, (a - b).perp(), top);
    int end_b = extreme_vertex(p, (b - a).perp(), top);
    auto cmp_l = [&](int i) { return orientation(a, p[i], b); };
    if (cmp_l(end_a) < 0 || cmp_l(end_b) > 0)
        return {-1, -1}; // no intersection
    array<int, 2> res;
    for (int i = 0; i < 2; i++) {
        int lo = end_b, hi = end_a, n = p.size();
        while ((lo + 1) % n != hi) {
            int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
            (cmp_l(m) == cmp_l(end_b) ? lo : hi) = m;
        }
        res[i] = (lo + !cmp_l(hi)) % n;
        swap(end_a, end_b);
    }
    if (res[0] == res[1]) return {res[0], -1}; // touches the vertex res[0]
    if (!cmp_l(res[0]) && !cmp_l(res[1])) 
        switch ((res[0] - res[1] + (int)p.size() + 1) % p.size()) {
            case 0: return {res[0], res[0]}; // touches the edge (res[0], res[0] + 1)
            case 2: return {res[1], res[1]}; // touches the edge (res[1], res[1] + 1)
        }
    return res; // intersects the edges (res[0], res[0] + 1) and (res[1], res[1] + 1)
}

pair<PT, int> point_poly_tangent(vector<PT> &p, PT Q, int dir, int l, int r) {
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        bool pvs = orientation(Q, p[mid], p[mid - 1]) != -dir;
        bool nxt = orientation(Q, p[mid], p[mid + 1]) != -dir;
        if (pvs && nxt) return {p[mid], mid};
        if (!(pvs || nxt)) {
            auto p1 = point_poly_tangent(p, Q, dir, mid + 1, r);
            auto p2 = point_poly_tangent(p, Q, dir, l, mid - 1);
            return orientation(Q, p1.first, p2.first) == dir ? p1 : p2;
        }
        if (!pvs) {
            if (orientation(Q, p[mid], p[l]) == dir)  r = mid - 1;
            else if (orientation(Q, p[l], p[r]) == dir) r = mid - 1;
            else l = mid + 1;
        }
        if (!nxt) {
            if (orientation(Q, p[mid], p[l]) == dir)  l = mid + 1;
            else if (orientation(Q, p[l], p[r]) == dir) r = mid - 1;
            else l = mid + 1;
        }
    }
    pair<PT, int> ret = {p[l], l};
    for (int i = l + 1; i <= r; i++) ret = orientation(Q, ret.first, p[i]) != dir ? make_pair(p[i], i) : ret;
    return ret;
}
// (ccw, cw) tangents from a point that is outside this convex polygon
// returns indexes of the points
// ccw means the tangent from Q to that point is in the same direction as the polygon ccw direction
pair<int, int> tangents_from_point_to_polygon(vector<PT> &p, PT Q){
    int ccw = point_poly_tangent(p, Q, 1, 0, (int)p.size() - 1).second;
    int cw = point_poly_tangent(p, Q, -1, 0, (int)p.size() - 1).second;
    return make_pair(ccw, cw);
}

// minimum distance from a point to a convex polygon
// it assumes point lie strictly outside the polygon
double dist_from_point_to_polygon(vector<PT> &p, PT z) {
    double ans = inf;
    int n = p.size();
    if (n <= 3) {
        for(int i = 0; i < n; i++) ans = min(ans, dist_from_point_to_seg(p[i], p[(i + 1) % n], z));
        return ans;
    }
    auto [r, l] = tangents_from_point_to_polygon(p, z);
    if(l > r) r += n;
    while (l < r) {
        int mid = (l + r) >> 1;
        double left = dist2(p[mid % n], z), right= dist2(p[(mid + 1) % n], z);
        ans = min({ans, left, right});
        if(left < right) r = mid;
        else l = mid + 1;
    }
    ans = sqrt(ans);
    ans = min(ans, dist_from_point_to_seg(p[l % n], p[(l + 1) % n], z));
    ans = min(ans, dist_from_point_to_seg(p[l % n], p[(l - 1 + n) % n], z));
    return ans;
}
// minimum distance from convex polygon p to line ab
// returns 0 is it intersects with the polygon
// top - upper right vertex
double dist_from_polygon_to_line(vector<PT> &p, PT a, PT b, int top) { //O(log n)
    PT orth = (b - a).perp();
    if (orientation(a, b, p[0]) > 0) orth = (a - b).perp();
    int id = extreme_vertex(p, orth, top);
    if (dot(p[id] - a, orth) > 0) return 0.0; //if orth and a are in the same half of the line, then poly and line intersects
    return dist_from_point_to_line(a, b, p[id]); //does not intersect
}
// minimum distance from a convex polygon to another convex polygon
// the polygon doesnot overlap or touch
// tested in https://toph.co/p/the-wall
double dist_from_polygon_to_polygon(vector<PT> &p1, vector<PT> &p2) { // O(n log n)
    double ans = inf;
    for (int i = 0; i < p1.size(); i++) {
        ans = min(ans, dist_from_point_to_polygon(p2, p1[i]));
    }
    for (int i = 0; i < p2.size(); i++) {
        ans = min(ans, dist_from_point_to_polygon(p1, p2[i]));
    }
    return ans;
}
// maximum distance from a convex polygon to another convex polygon
double maximum_dist_from_polygon_to_polygon(vector<PT> &u, vector<PT> &v){ //O(n)
    int n = (int)u.size(), m = (int)v.size();
    double ans = 0;
    if (n < 3 || m < 3) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) ans = max(ans, dist2(u[i], v[j]));
        }
        return sqrt(ans);
    }
    if (u[0].x > v[0].x) swap(n, m), swap(u, v);
    int i = 0, j = 0, step = n + m + 10;
    while (j + 1 < m && v[j].x < v[j + 1].x) j++ ;
    while (step--) {
        if (cross(u[(i + 1)%n] - u[i], v[(j + 1)%m] - v[j]) >= 0) j = (j + 1) % m;
        else i = (i + 1) % n;
        ans = max(ans, dist2(u[i], v[j]));
    }
    return sqrt(ans);
}

// calculates the area of the union of n polygons (not necessarily convex). 
// the points within each polygon must be given in CCW order.
// complexity: O(N^2), where N is the total number of points
double rat(PT a, PT b, PT p) {
        return !sign(a.x - b.x) ? (p.y - a.y) / (b.y - a.y) : (p.x - a.x) / (b.x - a.x);
 };
double polygon_union(vector<vector<PT>> &p) {
    int n = p.size();
    double ans=0;
    for(int i = 0; i < n; ++i) {
        for (int v = 0; v < (int)p[i].size(); ++v) {
            PT a = p[i][v], b = p[i][(v + 1) % p[i].size()];
            vector<pair<double, int>> segs;
            segs.emplace_back(0,  0), segs.emplace_back(1,  0);
            for(int j = 0; j < n; ++j) {
                if(i != j) {
                    for(size_t u = 0; u < p[j].size(); ++u) {
                        PT c = p[j][u], d = p[j][(u + 1) % p[j].size()];
                        int sc = sign(cross(b - a, c - a)), sd = sign(cross(b - a, d - a));
                        if(!sc && !sd) {
                            if(sign(dot(b - a, d - c)) > 0 && i > j) {
                                segs.emplace_back(rat(a, b, c), 1), segs.emplace_back(rat(a, b, d),  -1);
                            }
                        } 
                        else {
                            double sa = cross(d - c, a - c), sb = cross(d - c, b - c);
                            if(sc >= 0 && sd < 0) segs.emplace_back(sa / (sa - sb), 1);
                            else if(sc < 0 && sd >= 0) segs.emplace_back(sa / (sa - sb),  -1);
                        }
                    }
                }
            }
            sort(segs.begin(),  segs.end());
            double pre = min(max(segs[0].first, 0.0), 1.0), now, sum = 0;
            int cnt = segs[0].second;
            for(int j = 1; j < segs.size(); ++j) {
                now = min(max(segs[j].first, 0.0), 1.0);
                if (!cnt) sum += now - pre;
                cnt += segs[j].second;
                pre = now;
            }
            ans += cross(a, b) * sum;
        }
    }
    return ans * 0.5;
}
// contains all points p such that: cross(b - a, p - a) >= 0
struct HP {
    PT a, b;
    HP() {}
    HP(PT a, PT b) : a(a), b(b) {}
    HP(const HP& rhs) : a(rhs.a), b(rhs.b) {}
    int operator < (const HP& rhs) const {
        PT p = b - a;
        PT q = rhs.b - rhs.a;
        int fp = (p.y < 0 || (p.y == 0 && p.x < 0));
        int fq = (q.y < 0 || (q.y == 0 && q.x < 0));
        if (fp != fq) return fp == 0;
        if (cross(p, q)) return cross(p, q) > 0;
        return cross(p, rhs.b - a) < 0;
    }
    PT line_line_intersection(PT a, PT b, PT c, PT d) {
        b = b - a; d = c - d; c = c - a;
        return a + b * cross(c, d) / cross(b, d);
    }
    PT intersection(const HP &v) {
        return line_line_intersection(a, b, v.a, v.b);
    }
};
int check(HP a, HP b, HP c) {
    return cross(a.b - a.a, b.intersection(c) - a.a) > -eps; //-eps to include polygons of zero area (straight lines, points)
}
// consider half-plane of counter-clockwise side of each line
// if lines are not bounded add infinity rectangle
// returns a convex polygon, a point can occur multiple times though
// complexity: O(n log(n))
vector<PT> half_plane_intersection(vector<HP> h) {
    sort(h.begin(), h.end());
    vector<HP> tmp;
    for (int i = 0; i < h.size(); i++) {
        if (!i || cross(h[i].b - h[i].a, h[i - 1].b - h[i - 1].a)) {
            tmp.push_back(h[i]);
        }
    }
    h = tmp;
    vector<HP> q(h.size() + 10);
    int qh = 0, qe = 0;
    for (int i = 0; i < h.size(); i++) {
        while (qe - qh > 1 && !check(h[i], q[qe - 2], q[qe - 1])) qe--;
        while (qe - qh > 1 && !check(h[i], q[qh], q[qh + 1])) qh++;
        q[qe++] = h[i];
    }
    while (qe - qh > 2 && !check(q[qh], q[qe - 2], q[qe - 1])) qe--;
    while (qe - qh > 2 && !check(q[qe - 1], q[qh], q[qh + 1])) qh++;
    vector<HP> res; 
    for (int i = qh; i < qe; i++) res.push_back(q[i]);
    vector<PT> hull;
    if (res.size() > 2) {
        for (int i = 0; i < res.size(); i++) {
             hull.push_back(res[i].intersection(res[(i + 1) % ((int)res.size())]));
        }
    }
    return hull;
}
// rotate the polygon such that the (bottom, left)-most point is at the first position
void reorder_polygon(vector<PT> &p) {
  int pos = 0;
  for (int i = 1; i < p.size(); i++) {
    if (p[i].y < p[pos].y || (sign(p[i].y - p[pos].y) == 0 && p[i].x < p[pos].x)) pos = i;
  }
  rotate(p.begin(), p.begin() + pos, p.end());
}
// a and b are convex polygons
// returns a convex hull of their minkowski sum
// min(a.size(), b.size()) >= 2
// https://cp-algorithms.com/geometry/minkowski.html
vector<PT> minkowski_sum(vector<PT> a, vector<PT> b) {
  reorder_polygon(a); reorder_polygon(b);
  int n = a.size(), m = b.size();
  int i = 0, j = 0;
  a.push_back(a[0]); a.push_back(a[1]);
  b.push_back(b[0]); b.push_back(b[1]);
  vector<PT> c;
  while (i < n || j < m) {
    c.push_back(a[i] + b[j]);
    double p = cross(a[i + 1] - a[i], b[j + 1] - b[j]);
    if (sign(p) >= 0) ++i;
    if (sign(p) <= 0) ++j;
  }
  return c;
}
// returns the area of the intersection of the circle with center c and radius r
// and the triangle formed by the points c, a, b
double _triangle_circle_intersection(PT c, double r, PT a, PT b) {
    double sd1 = dist2(c, a), sd2 = dist2(c, b);
    if(sd1 > sd2) swap(a, b), swap(sd1, sd2);
    double sd = dist2(a, b);
    double d1 = sqrtl(sd1), d2 = sqrtl(sd2), d = sqrt(sd);
    double x = abs(sd2 - sd - sd1) / (2 * d);
    double h = sqrtl(sd1 - x * x);
    if(r >= d2) return h * d / 2;
    double area = 0;
    if(sd + sd1 < sd2) {
        if(r < d1) area = r * r * (acos(h / d2) - acos(h / d1)) / 2;
        else {
            area = r * r * ( acos(h / d2) - acos(h / r)) / 2;
            double y = sqrtl(r * r - h * h);
            area += h * (y - x) / 2;
        }
    } 
    else {
        if(r < h) area = r * r * (acos(h / d2) + acos(h / d1)) / 2;
        else {
            area += r * r * (acos(h / d2) - acos(h / r)) / 2;
            double y = sqrtl(r * r - h * h);
            area += h * y / 2;
            if(r < d1) {
                area += r * r * (acos(h / d1) - acos(h / r)) / 2;
                area += h * y / 2;
            } 
            else area += h * x / 2;
        }
    }
    return area;
}
// intersection between a simple polygon and a circle
double polygon_circle_intersection(vector<PT> &v, PT p, double r) {
    int n = v.size();
    double ans = 0.00;
    PT org = {0, 0};
    for(int i = 0; i < n; i++) {
        int x = orientation(p, v[i], v[(i + 1) % n]);
        if(x == 0) continue;
        double area = _triangle_circle_intersection(org, r, v[i] - p, v[(i + 1) % n] - p);
        if (x < 0) ans -= area;
        else ans += area;
    }
    return abs(ans);
}
// find a circle of radius r that contains as many points as possible
// O(n^2 log n);
double maximum_circle_cover(vector<PT> p, double r, circle &c) {
    int n = p.size();
    int ans = 0;
    int id = 0; double th = 0;
    for (int i = 0; i < n; ++i) {
        // maximum circle cover when the circle goes through this point
        vector<pair<double, int>> events = {{-PI, +1}, {PI, -1}};
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            double d = dist(p[i], p[j]);
            if (d > r * 2) continue;
            double dir = (p[j] - p[i]).arg();
            double ang = acos(d / 2 / r);
            double st = dir - ang, ed = dir + ang;
            if (st > PI) st -= PI * 2;
            if (st <= -PI) st += PI * 2;
            if (ed > PI) ed -= PI * 2;
            if (ed <= -PI) ed += PI * 2;
            events.push_back({st - eps, +1}); // take care of precisions!
            events.push_back({ed, -1});
            if (st > ed) {
                events.push_back({-PI, +1});
                events.push_back({+PI, -1});
            }
        }
        sort(events.begin(), events.end());
        int cnt = 0;
        for (auto &&e: events) {
            cnt += e.second;
            if (cnt > ans) {
                ans = cnt;
                id = i; th = e.first;
            }
        }
    }
    PT w = PT(p[id].x + r * cos(th), p[id].y + r * sin(th));
    c = circle(w, r); //best_circle
    return ans;
}
// radius of the maximum inscribed circle in a convex polygon
double maximum_inscribed_circle(vector<PT> p) {
    int n = p.size();
    if (n <= 2) return 0;
    double l = 0, r = 20000;
    while (r - l > eps) {
        double mid = (l + r) * 0.5;
        vector<HP> h;
        const int L = 1e9;
        h.push_back(HP(PT(-L, -L), PT(L, -L)));
        h.push_back(HP(PT(L, -L), PT(L, L)));
        h.push_back(HP(PT(L, L), PT(-L, L)));
        h.push_back(HP(PT(-L, L), PT(-L, -L)));
        for (int i = 0; i < n; i++) {
            PT z = (p[(i + 1) % n] - p[i]).perp();
            z = z.truncate(mid);
            PT y = p[i] + z, q = p[(i + 1) % n] + z;
            h.push_back(HP(p[i] + z, p[(i + 1) % n] + z));
        }
        vector<PT> nw = half_plane_intersection(h);
        if (!nw.empty()) l = mid;
        else r = mid;
    }
    return l;
}
// ear decomposition, O(n^3) but faster
vector<vector<PT>> triangulate(vector<PT> p) {
  vector<vector<PT>> v;
  while (p.size() >= 3) {
    for (int i = 0, n = p.size(); i < n; i++) {
      int pre = i == 0 ? n - 1 : i - 1;;
      int nxt = i == n - 1 ? 0 : i + 1;;
      int ori = orientation(p[i], p[pre], p[nxt]);
      if (ori < 0) {
        int ok = 1;
        for (int j = 0; j < n; j++) {
          if (j == i || j == pre || j == nxt)continue;
          if (is_point_in_triangle(p[i], p[pre], p[nxt] , p[j]) < 1) {
            ok = 0;
            break;
          }
        }
        if (ok) {
          v.push_back({p[pre], p[i], p[nxt]});
          p.erase(p.begin() + i);
          break;
        }
      }
    }
  }
  return v;
}

struct star {
    int n;    // number of sides of the star
    double r; // radius of the circumcircle
    star(int _n, double _r) {
        n = _n;
        r = _r;
    }

    double area() {
        double theta = PI / n;
        double s = 2 * r * sin(theta);
        double R = 0.5 * s / tan(theta);
        double a = 0.5 * n * s * R;
        double a2 = 0.25 * s * s / tan(1.5 * theta);
        return a - n * a2;
    }
};

// given a list of lengths of the sides of a polygon in counterclockwise order
// returns the maximum area of a non-degenerate polygon that can be formed using those lengths
double get_maximum_polygon_area_for_given_lengths(vector<double> v) {
  if (v.size() < 3) {
    return 0;
  }
  int m = 0;
  double sum = 0;
  for (int i = 0; i < v.size(); i++) {
    if (v[i] > v[m]) {
      m = i;
    }
    sum += v[i];
  }
  if (sign(v[m] - (sum - v[m])) >= 0) {
    return 0; // no non-degenerate polygon is possible
  }
  // the polygon should be a circular polygon
  // that is all points are on the circumference of a circle
  double l = v[m] / 2, r = 1e6; // fix it correctly
  int it = 60;
  auto ang = [](double x, double r) { // x = length of the chord, r = radius of the circle
    return 2 * asin((x / 2) / r);
  };
  auto calc = [=](double r) {
    double sum = 0;
    for (auto x: v) {
      sum += ang(x, r);
    }
    return sum;
  };
  // compute the radius of the circle
  while (it--) {
    double mid = (l + r) / 2;
    if (calc(mid) <= 2 * PI) {
      r = mid;
    }
    else {
      l = mid;
    }
  }

  if (calc(r) <= 2 * PI - eps) { // the center of the circle is outside the polygon
    auto calc2 = [&](double r) {
      double sum = 0;
      for (int i = 0; i < v.size(); i++) {
        double x = v[i];
        double th = ang(x, r);
        if (i != m) {
          sum += th;
        }
        else {
          sum += 2 * PI - th;
        }
      }
      return sum;
    };
    l = v[m] / 2; r = 1e6;
    it = 60;
    while (it--) {
      double mid = (l + r) / 2;
      if (calc2(mid) > 2 * PI) {
        r = mid;
      }
      else {
        l = mid;
      }
    }
    auto get_area = [=](double r) {
      double ans = 0;
      for (int i = 0; i < v.size(); i++) {
        double x = v[i];
        double area = r * r * sin(ang(x, r)) / 2;
        if (i != m) {
          ans += area;
        }
        else {
          ans -= area;
        }
      }
      return ans;
    };
    return get_area(r);
  }
  else { // the center of the circle is inside the polygon
    auto get_area = [=](double r) {
      double ans = 0;
      for (auto x: v) {
        ans += r * r * sin(ang(x, r)) / 2;
      }
      return ans;
    };
    return get_area(r);
  }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    return 0;   
}


//Trie
struct Node {
    Node *links[26] = {nullptr};
    int cntEndWith = 0, cntPrefix = 0;
    bool containsKey(char ch) {
        return (links[ch - 'a'] != nullptr);
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void increaseEnd() {
        cntEndWith++;
    }

    void increasePrefix() {
        cntPrefix++;
    }

    void deleteEnd() {
        cntEndWith--;
    }

    void reducePrefix() {
        cntPrefix--;
    }

    int getEnd() {
        return cntEndWith;
    }

    int getPrefix() {
        return cntPrefix;
    }
};

class Trie {
private:
    Node* root;
    void clear(Node* node) {
        if (!node) return;
        for (int i = 0; i < 26; i++) {
            if (node->links[i]) {
                clear(node->links[i]);
            }
        }
        delete node;
    }

public:
    Trie() {
        root = new Node();
    }

    ~Trie() {
        clear(root);
    }

    void insert(const string &word) {
        Node* node = root;
        for (auto &c : word) {
            if (!node->containsKey(c)) 
                node->put(c, new Node());
            node = node->get(c);
            node->increasePrefix();
        }
        node->increaseEnd();
    }

    int countWordsEqualTo(const string &word) {
        Node* node = root;
        for (auto &c : word) {
            if (!node->containsKey(c))
                return 0;
            node = node->get(c);
        }
        return node->getEnd();
    }

    int countWordsStartingWith(const string &prefix) {
        Node* node = root;
        for (auto &c : prefix) {
            if (!node->containsKey(c))
                return 0;
            node = node->get(c);
        }
        return node->getPrefix();
    }

    void erase(const string &word) {
        if (countWordsEqualTo(word) == 0)
            return; 
        Node* node = root;
        for (auto &c : word) {
            node = node->get(c);
            node->reducePrefix();
        }
        node->deleteEnd();
    }
};

// Z-algorithm
vector<int> z_function(string &s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

// end

// Flow Algorithms

// Edmonds-Karp

ll n;
vector<vector<ll>> capacity;
vector<vector<ll>> adj;

ll bfs(ll s, ll t, vector<ll>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<ll, ll>> q;
    q.push({s, inf});

    while (!q.empty()) {
        ll cur = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for (ll next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                ll new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

ll maxflow(ll s, ll t) {
    ll flow = 0;
    vector<ll> parent(n);
    ll new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        ll cur = t;
        while (cur != s) {
            ll prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

// Edmonds-Karp end

// Eulerian Path (Directed)
struct DirectedEulerianPath {
    int n, edges, offset;
    vector<vector<pair<int, int>>> g;
    vector<int> in, out, done, ans_nodes, ans_edges;
    DirectedEulerianPath(int nodes, int index_offset) {
        n = nodes;
        offset = index_offset;
        edges = 0;
        g.assign(n + offset, vector<pair<int, int>>());
        in.assign(n + offset, 0);
        out.assign(n + offset, 0);
        done.assign(n + offset, 0);
    }
    void addEdge(int u, int v) {
        addEdge(u, v, edges); 
    }
    void addEdge(int u, int v, int id) {
        int max_node = max(u, v);
        if (max_node >= g.size()) {
            g.resize(max_node + 1);
            in.resize(max_node + 1, 0);
            out.resize(max_node + 1, 0);
            done.resize(max_node + 1, 0);
            n = max_node + 1 - offset;
        }
        g[u].push_back({v, id});
        out[u]++;
        in[v]++;
        edges++;
    }
    void dfs(int start_node) {
        vector<pair<int, int>> st;
        st.push_back({start_node, -1});
        
        while (!st.empty()) {
            int u = st.back().first;
            if (done[u] < g[u].size()) {
                auto e = g[u][done[u]++];
                st.push_back({e.first, e.second});
            } 
            else {
                ans_nodes.push_back(u);
                int edge_id = st.back().second;
                st.pop_back();
                if (edge_id != -1) {
                    ans_edges.push_back(edge_id);
                }
            }
        }
    }
    bool solve() {
        if (edges == 0) {
            ans_nodes.push_back(offset);
            return true;
        }
        int cnt1 = 0, cnt2 = 0, root = -1;
        int start_node = offset;
        int end_node = n - 1 + offset;
        for (int i = start_node; i <= end_node; i++) {
            if (in[i] - out[i] == 1) cnt1++;
            if (out[i] - in[i] == 1) cnt2++, root = i;
            if (abs(in[i] - out[i]) > 1) return false;
        }
        if (cnt1 > 1 || cnt2 > 1) return false;
        if (root == -1) {
            for (int i = start_node; i <= end_node; i++) {
                if (out[i] > 0) {
                    root = i;
                    break;
                }
            }
        }
        if (root == -1) return false; 
        dfs(root);
        if (ans_edges.size() != edges) return false; 
        reverse(ans_nodes.begin(), ans_nodes.end());
        reverse(ans_edges.begin(), ans_edges.end());
        return true;
    }
    bool solve(int x, int y) {
        if (edges == 0) {
            if (x != y) return false;
            ans_nodes.push_back(x);
            return true;
        }
        int start_node = offset;
        int end_node = n - 1 + offset;
        for (int i = start_node; i <= end_node; i++) {
            int diff = out[i] - in[i];
            if (x != y) {
                if (i == x && diff != 1) return false;
                else if (i == y && diff != -1) return false;
                else if (i != x && i != y && diff != 0) return false;
            } else {
                if (diff != 0) return false; // Circuit check
            }
        }
        dfs(x);
        if (ans_edges.size() != edges) return false; 
        reverse(ans_nodes.begin(), ans_nodes.end());
        reverse(ans_edges.begin(), ans_edges.end());
        return true;
    }
};

// end

// Eulerian Path (Undirected)

struct UndirectedEulerianPath {
    struct Edge {
        int to;
        int id;          
        int internal_id; 
    };
    int n, edge_cnt, offset;
    vector<vector<Edge>> g;
    vector<int> deg, done, vis;
    vector<int> ans_nodes, ans_edges;
    UndirectedEulerianPath(int nodes, int index_offset) {
        n = nodes;
        offset = index_offset;
        edge_cnt = 0;
        g.assign(n + offset, vector<Edge>());
        deg.assign(n + offset, 0);
        done.assign(n + offset, 0);
    }
    void addEdge(int u, int v) {
        addEdge(u, v, edge_cnt); 
    }
    void addEdge(int u, int v, int id) {
        int max_node = max(u, v);
        if (max_node >= g.size()) {
            g.resize(max_node + 1);
            deg.resize(max_node + 1, 0);
            done.resize(max_node + 1, 0);
            n = max_node + 1 - offset;
        }
        g[u].push_back({v, id, edge_cnt});
        g[v].push_back({u, id, edge_cnt});
        deg[u]++;
        deg[v]++;
        vis.push_back(0); 
        edge_cnt++;
    }
    void dfs(int start_node) {
        vector<pair<int, int>> st;
        st.push_back({start_node, -1});
        while (!st.empty()) {
            int u = st.back().first;
            bool found = false;
            while (done[u] < g[u].size()) {
                auto e = g[u][done[u]++];
                if (vis[e.internal_id]) continue; 
                vis[e.internal_id] = 1;
                st.push_back({e.to, e.id});
                found = true;
                break;
            }
            if (!found) {
                ans_nodes.push_back(u);
                int edge_id = st.back().second;
                st.pop_back();
                if (edge_id != -1) {
                    ans_edges.push_back(edge_id);
                }
            }
        }
    }
    bool solve() {
        if (edge_cnt == 0) {
            ans_nodes.push_back(offset);
            return true;
        }
        int odd = 0, root = -1;
        int start_node = offset;
        int end_node = n - 1 + offset;
        for (int i = start_node; i <= end_node; i++) {
            if (deg[i] % 2 != 0) {
                odd++;
                root = i;
            }
        }
        if (odd > 2) return false;
        if (root == -1) {
            for (int i = start_node; i <= end_node; i++) {
                if (deg[i] > 0) {
                    root = i;
                    break;
                }
            }
        }
        if (root == -1) return false;
        dfs(root);
        if (ans_edges.size() != edge_cnt) return false;
        reverse(ans_nodes.begin(), ans_nodes.end());
        reverse(ans_edges.begin(), ans_edges.end());
        return true;
    }
    bool solve(int x, int y) {
        if (edge_cnt == 0) {
            if (x != y) return false;
            ans_nodes.push_back(x);
            return true;
        }
        int start_node = offset;
        int end_node = n - 1 + offset;
        for (int i = start_node; i <= end_node; i++) {
            bool is_odd = (deg[i] % 2 != 0);
            if (x != y) {
                if (i == x && !is_odd) return false;
                else if (i == y && !is_odd) return false;
                else if (i != x && i != y && is_odd) return false;
            } else {
                if (is_odd) return false;
            }
        }
        dfs(x);
        if (ans_edges.size() != edge_cnt) return false;
        reverse(ans_nodes.begin(), ans_nodes.end());
        reverse(ans_edges.begin(), ans_edges.end());
        return true;
    }
};

// End

// Ternary Search

double ternary_search(double l, double r) {
    double eps = 1e-9;              //set the error limit here
    while (r - l > eps) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double f1 = f(m1);      //evaluates the function at m1
        double f2 = f(m2);      //evaluates the function at m2
        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }
    return f(l);                    //return the maximum of f(x) in [l, r]
}

// for integers

int lo = -1, hi = n;
while (hi - lo > 1){
    int mid = (hi + lo)>>1;
    if (f(mid) > f(mid + 1)) 
         hi = mid;
    else 
         lo = mid; 
}
//lo + 1 is the answer

// end
