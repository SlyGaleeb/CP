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

ll modInv (ll a, ll MOD) {
    return mod_exp(a, MOD - 2, MOD);
}

string convert_base(ll n, int base) {
    if (n==0)
        return "0";
    ll power = 1;
    while (power*base<=n)
        power *= base;
    string result;
    while (power>0) {
        ll k = n/power;
        result += k + '0';
        n -= power*k;
        power /= base;
    }
    return result;
}

ll nCr (ll n, ll r) {
    if (n<r)
        return 0ll;
    return (fact[n]*mod_exp(fact[r]*fact[n-r]%MOD,MOD-2,MOD))%MOD;
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

void flood(ll r, ll c) {
    if (r<0 || r>=n || c<0 || c>=m || vis[r][c])
        return;
    vis[r][c] = 1;
    flood(r,c+1);
    flood(r,c-1);
    flood(r+1,c);
    flood(r-1,c);
}

void bfs (ll x) {
    vis[x] = 1;
    dis[x] = 0;
    q.push(x);
    while (!q.empty()) {
        ll s = q.front(); 
        q.pop();
        for (auto u : adj[s]) {
            if (vis[u]) 
                continue;
            vis[u] = 1;
            dis[u] = dis[s]+1;
            q.push(u);
        }
    }
}

void treedfs(ll child, ll par) {
    for (auto c:adj[child]) {
        if (c==par)
            continue;
        treedfs(c,child);
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
    for (int p = 2; p * p <= n; p++) {
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

template<int MOD, int RT> struct mint {
    static const int mod = MOD;
    static constexpr mint rt() { return RT; } // primitive root
    int v; 
    explicit operator int() const { return v; } 
    mint():v(0) {}
    mint(ll _v):v(int(_v%MOD)) { v += (v<0)*MOD; }
    mint& operator+=(mint o) { 
        if ((v += o.v) >= MOD) v -= MOD; 
        return *this; }
    mint& operator-=(mint o) { 
        if ((v -= o.v) < 0) v += MOD; 
        return *this; }
    mint& operator*=(mint o) { 
        v = int((ll)v*o.v%MOD); return *this; }
    friend mint pow(mint a, ll p) { assert(p >= 0);
        return p==0?1:pow(a*a,p/2)*(p&1?a:1); }
    friend mint inv(mint a) { assert(a.v != 0); return pow(a,MOD-2); }
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
};

// DSU start

void init (int n) {
    for (int i = 1; i <= n; ++i)
        par[i] = i;
}

int find (int node) {
    if (par[node]!=node)
        par[node] = find(par[node]);
    return par[node];
}

void unite (int A, int B) {
    int rootA = find(A);
    int rootB = find(B);
    if (rand()%2)
        par[rootB] = rootA;
    else
        par[rootA] = rootB;
}

// DSU end

class SegmentTree {
public:
    int n;
    vector<ll> tree;
    SegmentTree(int n) : n(n) {
        tree.resize(4 * n);
    }
    void build(const vector<ll>& arr, int node, int start, int end) {
        if(start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }
    ll query(int node, int start, int end, int l, int r) {
        if(r < start || end < l) {
            return -1e18;
        }
        if(l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        ll leftQuery = query(2 * node, start, mid, l, r);
        ll rightQuery = query(2 * node + 1, mid + 1, end, l, r);
        return max(leftQuery, rightQuery);
    }
};


using T = pair<ll,int>;
priority_queue<T,vector<T>,greater<T>>pq;
void dijkstra (int node) {
    dis[node] = 0;
    pq.push({0,node});
    while (!pq.empty()) {
        int curr = pq.top().S;
        pq.pop();
        if (vis[curr])
            continue;
        vis[curr] = 1;
        for (auto [d,x]:adj[curr]) {
            if (dis[curr]+d<dis[x]) {
                dis[x] = dis[curr]+d;
                pq.push({dis[x],x});
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

const ll LG = (ll)ceil(log2(N))+1;
ll par[N][LG];
vector<ll>depth(N,0);

void dfs(ll u, ll p) {
    par[u][0] = (p==-1?u:p);
    for (ll i = 1; i < LG; i++) 
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (ll v:adj[u]) {
        if (v==p) 
            continue;
        par[v][0] = u;
        depth[v] = depth[u] + 1;
        dfs(v,u);
    }
}
ll lca(ll u, ll v) {
    if (depth[u]>depth[v]) 
        swap(u,v);
    for (ll i = LG-1; i >= 0; i--) {
        if (depth[par[v][i]]>=depth[u]) 
            v = par[v][i];
    }
    if (u==v) 
        return u;
    for (ll i = LG - 1; i >= 0; i--) {
        if (par[v][i]!=par[u][i]) 
            v = par[v][i], u = par[u][i];
    }
    return par[u][0];
}

ll dist (ll u, ll v) {
    return depth[u]+depht[v]-2*depth[(lca(u,v))];
}

// LCA end


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

using u128 = __uint128_t;  // for safe modular multiplication

// ---------- modular arithmetic ----------
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

// ---------- Miller-Rabin ----------
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

// ---------- Pollard's Rho ----------
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
            d = gcd(abs(x - y), n);
        }
        if (d != n) return d;
    }
}

// ---------- Factorization ----------
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

// Code for solving sytem of 2 linear equations

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