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

// spf start

const ll N = 2000001;
ll lp[N+1];
vector<ll> pr;
 
void sieve(){
    ll i,j;
    for (i=2; i<=N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back (i);
        }
        for (j=0; j<(ll)pr.size() && pr[j]<=lp[i] && i*pr[j]<=N; ++j)
            lp[i*pr[j]] = pr[j];
    }
}
 
vector<ll> spf(ll n){
    vector<ll> pf;
    while (n != 1){
        pf.push_back(lp[n]);
        n = n / lp[n];
    }
    return pf;
}

void pre()
{
    sieve();
}

// spf end

// nCr

ll fact[N+1];

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

void pre() 
{
    fact[0] = 1;
    for (int i = 1; i <= N; i++) 
        fact[i] = fact[i-1]*i%MOD;
}

// nCr end

// Modular Inverse Start

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

// Modular Inverse End

void dfs(ll node, vector<vector<ll>>& adj, vector<ll>& vis) 
{
    vis[node] = 1;
    for (auto c:adj[node]) 
    {
        if (vis[c])
            continue;
        dfs(c, adj, vis);
    }
}

void bfs (ll x, vector<vector<ll>>& adj, vector<ll>& dis, queue<ll>& q) 
{
    dis[x] = 0;
    q.push(x);
    while (!q.empty()) 
    {
        ll s = q.front(); 
        q.pop();
        for (auto u : adj[s]) 
        {
            if (dis[u]==-1) 
            {
                dis[u] = dis[s]+1;
                q.push(u);
            }
        }
    }
}

// sparse table start
// --------one indexing--------
const ll N = 2e5 + 1;
ll t[N][20], a[N];

void build(ll n) 
{
    for(ll i = 1; i <= n; ++i) 
    {
        t[i][0] = a[i];
    }
    for(ll k = 1; k < 20; ++k) 
    {
        for(ll i = 1; i + (1 << k) - 1 <= n; ++i) 
        {
            t[i][k] = min(t[i][k - 1], t[i + (1 << (k - 1))][k - 1]);
        }
    }
}

ll query(ll l, ll r) 
{
    ll k = 31 - __builtin_clz(r - l + 1);
    return min(t[l][k], t[r - (1 << k) + 1][k]);
}
// sparse table end

//topological sort

vector<ll> topoSort(vector<vector<ll>>& adj) 
{
    ll n = adj.size()-1;
    vector<ll> indegree(n+1, 0);
    queue<ll> q;
    vector<ll> list;

    // Compute indegrees
    for (ll i = 1; i <= n; i++) 
    {
        for (ll next : adj[i])
            indegree[next]++;
    }

    // Add all nodes with indegree 0 
    // into the queue
    for (ll i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }
    // Kahn’s Algorithm (BFS)
    while (!q.empty()) 
    {
        ll top = q.front();
        q.pop();
        list.push_back(top);
        for (ll next : adj[top]) 
        {
            indegree[next]--;
            if (indegree[next] == 0)
                q.push(next);
        }
    }
    return list;
}

//topological sort end

//topological sort using dfs

void findTopoSort(ll node, vector<ll>& vis, vector<vector<ll>>& adj, stack<ll>& st) {
    vis[node] = 1;
    for (ll it : adj[node]) {
        if (!vis[it]) {
            findTopoSort(it, vis, adj, st);
        }
    }
    // push the node after all its neighbours
    st.push(node);
}

vector<ll> topoSort(vector<vector<ll>>& adj) {
    ll n = adj.size() + 1;
    stack<ll> st;
    vector<ll> vis(n+1, 0);

    for (ll i = 1; i <= n; i++) {
        if (!vis[i]) {
            findTopoSort(i, vis, adj, st);
        }
    }
    vector<ll> topo;
    
    // popping elements from stack and 
    // pushing into the list
    while (!st.empty()) {
        topo.push_back(st.top());
        st.pop();
    }
    return topo;
}

//end

void topologicalSort(vector<vector<ll>>& adj)
{
    ll V = adj.size();
    // Create a vector to store indegrees of all
    // the vertices
    // Initialize all indegrees to 0
    vector<ll> in_degree(V, 0);

    // Traverse adjacency lists to fill indegrees of
    // vertices
    // This step takes O(V+E) time
    for (ll u = 0; u < V; u++) {
        for (auto x : adj[u])
            in_degree[x]++;
    }

    // Create a min-heap priority queue and inserting all
    // vertices with indegree 0
    priority_queue<ll, vector<ll>, greater<ll> > pq;
    for (ll i = 0; i < V; i++)
        if (in_degree[i] == 0)
            pq.push(i);

    // Initialize count of visited vertices
    ll cnt = 0;

    // Create a vector to store result (A topological
    // ordering of the vertices)
    vector<ll> top_order;

    // One by one erase vertices from setand insert
    // adjacents if indegree of adjacent becomes 0
    while (!pq.empty()) {

        // Extract vertex with minimum number from priority
        // queue and add it to topological order
        ll u = pq.top();
        pq.pop();
        top_order.push_back(u);

        // Iterate through all its neighbouring nodes
        // of erased node u and decrease their in-degree
        // by 1
        for (auto x : adj[u])

            // If in-degree becomes zero, add it to queue
            if (--in_degree[x] == 0)
                pq.push(x);

        cnt++;
    }

    // Check if there was a cycle
    if (cnt != V) {
        cout << -1 << "\n";
        return;
    }

    // Print topological order
    vector<ll> ans(top_order.size());
    for (ll i = 0; i < top_order.size(); i++)
    {
        ans[top_order[i]] = i+1;
    }
    for (ll i = 0; i < top_order.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << "\n";
}

//bipartite check

int n;
vector<vector<int>> adj;

vector<int> side(n+1, -1);
bool is_bipartite = true;
queue<int> q;
for (int st = 1; st <= n; ++st) 
{
    if (side[st] == -1) 
    {
        q.push(st);
        side[st] = 0;
        while (!q.empty()) 
        {
            int v = q.front();
            q.pop();
            for (int u : adj[v]) 
            {
                if (side[u] == -1) 
                {
                    side[u] = side[v] ^ 1;
                    q.push(u);
                } 
                else 
                {
                    is_bipartite &= (side[u] != side[v]);
                }
            }
        }
    }
}

cout << (is_bipartite ? "YES" : "NO") << endl;

// bipartite end

// Simple segment tree. Supports range query and point update.

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

//code end

// Segment Tree with Lazy Propagation

struct segtree {
    ll size;
    vector<ll>operations,sums;
    ll NO_OP = inf;
 
    ll op (ll a, ll b) {
        if (b==NO_OP)
            return a;
        return b;
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

// DSU start

vector<ll> par, height;
 
void init (ll n) {
    height.assign(n + 1, 0);
    par.resize(n + 1);
    for (ll i = 1; i <= n; ++i)
        par[i] = i;
}
 
ll find (ll node) {
    if (par[node] != node) {
        par[node] = find(par[node]);
    }
    return par[node];
}
 
void unite (ll A, ll B) {
    if (A == B)
        return;
    ll rootA = find(A);
    ll rootB = find(B);
    if (height[rootA] <= height[rootB])
        swap(rootA, rootB);
    par[rootB] = rootA;
    if (height[rootA] == height[rootB])
        height[rootA]++; 
}

// DSU end

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

using T = pair<ll, ll>;

void dijkstra(ll node, vector<vector<pair<ll, ll>>>& adj, vector<ll>& vis, vector<ll>& dis) 
{
    priority_queue<T,vector<T>,greater<T>>pq;
    dis[node] = 0;
    pq.push({0,node});
    while (!pq.empty()) 
    {
        ll curr = pq.top().S;
        pq.pop();
        if (vis[curr])
            continue;
        vis[curr] = 1;
        for (auto [x, d]:adj[curr]) 
        {
            if (dis[curr]+d<dis[x]) 
            {
                dis[x] = dis[curr]+d;
                pq.push({dis[x],x});
            }
        }
    }
}

// Mo's Algorithm

class MosAlgorithm {
private:
    struct Query {ll l, r, id;};
    ll block_size;
    long long current_answer;
    vector<ll> arr;
    inline void add(ll idx) {}
    inline void remove(ll idx){}
public:
    MosAlgorithm(const vector<ll>& input_array) {
        arr = input_array;
        current_answer = 0;
        ll n = arr.size();
        block_size = max(1ll, (ll)sqrt(n));
    }
    vector<long long> processQueries(const vector<pair<ll, ll>>& raw_queries) {
        ll q = raw_queries.size();
        vector<Query> queries(q);
        vector<long long> answers(q);
        for (ll i = 0; i < q; i++) {
            queries[i].l = raw_queries[i].first;
            queries[i].r = raw_queries[i].second;
            queries[i].id = i;
        }
        sort(queries.begin(), queries.end(), [this](const Query& a, const Query& b) {
            ll block_a = a.l / block_size;
            ll block_b = b.l / block_size;
            if (block_a != block_b) {return block_a < block_b;}
            return (block_a & 1) ? (a.r < b.r) : (a.r > b.r);
        });
        ll current_l = 0;
        ll current_r = -1;
        for (const Query& qry : queries) {
            while (current_l > qry.l) {current_l--; add(current_l);}
            while (current_r < qry.r) {current_r++; add(current_r);}
            while (current_l < qry.l) {remove(current_l); current_l++;}
            while (current_r > qry.r) {remove(current_r); current_r--;}
            answers[qry.id] = current_answer;
        }
        return answers;
    }
};


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

//Binary Trie

struct Trie {
  static const int B = 31;
  struct node {
    node* nxt[2];
    int sz;
    node() {
      nxt[0] = nxt[1] = NULL;
      sz = 0;
    }
  }*root;
  Trie() {
    root = new node();
  }
  void insert(int val) {
    node* cur = root;
    cur -> sz++;
    for (int i = B - 1; i >= 0; i--) {
      int b = val >> i & 1;
      if (cur -> nxt[b] == NULL) cur -> nxt[b] = new node();
      cur = cur -> nxt[b];
      cur -> sz++;
    }
  }
  int query(int x, int k) { // number of values s.t. val ^ x < k
    node* cur = root;
    int ans = 0;
    for (int i = B - 1; i >= 0; i--) {
      if (cur == NULL) break;
      int b1 = x >> i & 1, b2 = k >> i & 1;
      if (b2 == 1) {
        if (cur -> nxt[b1]) ans += cur -> nxt[b1] -> sz;
        cur = cur -> nxt[!b1];
      } else cur = cur -> nxt[b1];
    }
    return ans;
  }
  int get_max(int x) { // returns maximum of val ^ x
    node* cur = root;
    int ans = 0;
    for (int i = B - 1; i >= 0; i--) {
      int k = x >> i & 1;
      if (cur -> nxt[!k]) cur = cur -> nxt[!k], ans <<= 1, ans++;
      else cur = cur -> nxt[k], ans <<= 1;
    }
    return ans;
  }
  int get_min(int x) { // returns minimum of val ^ x
    node* cur = root;
    int ans = 0;
    for (int i = B - 1; i >= 0; i--) {
      int k = x >> i & 1;
      if (cur -> nxt[k]) cur = cur -> nxt[k], ans <<= 1;
      else cur = cur -> nxt[!k], ans <<= 1, ans++;
    }
    return ans;
  }
  void del(node* cur) {
    for (int i = 0; i < 2; i++) if (cur -> nxt[i]) del(cur -> nxt[i]);
    delete(cur);
  }
} t;

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


// Returns a vector where ans[i] is the job index assigned to applicant i, 
// or -1 if applicant i does not get a job.
vector<int> kuhn(const vector<vector<int>>& mat) {
    if (mat.empty() || mat[0].empty()) return {};
    int n = mat.size();    // Number of applicants
    int m = mat[0].size(); // Number of jobs
    // match[j] stores the applicant assigned to job j
    vector<int> match(m, -1);
    vector<bool> visited(m, false);
    // DFS to find an augmenting path
    auto dfs = [&](auto& self, int u) -> bool {
        for (int v = 0; v < m; ++v) {
            if (mat[u][v] == 1 && !visited[v]) {
                visited[v] = true;
                // If job v is unassigned, or the current assignee can find another job
                if (match[v] == -1 || self(self, match[v])) {
                    match[v] = u;
                    return true;
                }
            }
        }
        return false;
    };
    // Attempt to match each applicant
    for (int i = 0; i < n; ++i) {
        fill(visited.begin(), visited.end(), false);
        dfs(dfs, i);
    }
    // Construct the result mapping applicant -> job
    vector<int> applicant_to_job(n, -1);
    for (int v = 0; v < m; ++v) {
        if (match[v] != -1) {
            applicant_to_job[match[v]] = v;
        }
    }
    return applicant_to_job;
}

//Hopcroft-Karp

// BFS Function
// Builds layers using shortest augmenting paths
bool bfs(vector<vector<int>> &mat, vector<int> &pairU, vector<int> &pairV, vector<int> &dist,
         int totalApplicants, int totalJobs)
{
    // Queue used for BFS traversal
    queue<int> q;

    // Traverse all applicants
    for (int applicant = 1; applicant <= totalApplicants; applicant++)
    {
        // If applicant is free
        if (pairU[applicant] == 0)
        {
            // Free applicants belong to level 0
            dist[applicant] = 0;

            // Push applicant into queue
            q.push(applicant);
        }
        else
        {
            // Mark matched applicants as unvisited
            dist[applicant] = INT_MAX;
        }
    }

    // Distance to NIL node
    dist[0] = INT_MAX;

    // Perform BFS traversal
    while (!q.empty())
    {
        // Get current applicant
        int applicant = q.front();

        // Remove from queue
        q.pop();

        // If current layer is useful
        if (dist[applicant] < dist[0])
        {
            // Traverse all jobs
            for (int job = 1; job <= totalJobs; job++)
            {
                // If edge exists
                if (mat[applicant - 1][job - 1])
                {
                    // Get applicant assigned
                    // to current job
                    int nextApplicant = pairV[job];

                    // If not visited
                    if (dist[nextApplicant] == INT_MAX)
                    {
                        // Assign next BFS layer
                        dist[nextApplicant] = dist[applicant] + 1;

                        // Push into queue
                        q.push(nextApplicant);
                    }
                }
            }
        }
    }

    // If NIL node reachable,
    // augmenting path exists
    return dist[0] != INT_MAX;
}

// DFS Function
// Finds augmenting paths using BFS layers
bool canAssignJob(int applicant, vector<vector<int>> &mat, vector<int> &pairU, vector<int> &pairV,
                  vector<int> &dist, int totalJobs)
{
    // If NIL node reached,
    // augmenting path found
    if (applicant == 0)
    {
        return true;
    }

    // Traverse all jobs
    for (int job = 1; job <= totalJobs; job++)
    {
        // If edge exists
        if (mat[applicant - 1][job - 1])
        {
            // Get applicant assigned
            // to current job
            int nextApplicant = pairV[job];

            // Follow only valid BFS layers
            if (dist[nextApplicant] == dist[applicant] + 1)
            {
                // Recursively try to find
                // augmenting path
                if (canAssignJob(nextApplicant, mat, pairU, pairV, dist, totalJobs))
                {
                    // Assign current job
                    // to current applicant
                    pairV[job] = applicant;

                    // Assign current applicant
                    // to current job
                    pairU[applicant] = job;

                    // Matching successful
                    return true;
                }
            }
        }
    }

    // Mark node as useless
    dist[applicant] = INT_MAX;

    // No augmenting path found
    return false;
}


// Function to find maximum bipartite matching
int maximumMatch(vector<vector<int>> &mat)
{
    // Number of applicants
    int totalApplicants = mat.size();

    // Number of jobs
    int totalJobs = mat[0].size();

    // pairU[u] stores job assigned
    // to applicant u
    vector<int> pairU(totalApplicants + 1, 0);

    // pairV[v] stores applicant assigned
    // to job v
    vector<int> pairV(totalJobs + 1, 0);

    // Distance array used in BFS
    vector<int> dist(totalApplicants + 1);

    // Stores final maximum matching
    int maximumMatching = 0;

    // Repeat while augmenting path exists
    while (bfs(mat, pairU, pairV, dist, totalApplicants, totalJobs))
    {
        // Traverse all applicants
        for (int applicant = 1; applicant <= totalApplicants; applicant++)
        {
            // If applicant is free
            if (pairU[applicant] == 0)
            {
                // Try assigning a job
                if (canAssignJob(applicant, mat, pairU, pairV, dist, totalJobs))
                {
                    // Increase matching count
                    maximumMatching++;
                }
            }
        }
    }

    // Return final answer
    return maximumMatching;
}

int main()
{
    // Adjacency matrix representation
    // mat[i][j] = 1 means
    // applicant i interested in job j
    vector<vector<int>> mat = {{0, 1, 1, 0, 0, 0}, {1, 0, 0, 1, 0, 0}, {0, 0, 1, 0, 0, 0},
                               {0, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1}};

    // Print maximum matching
    cout << maximumMatch(mat);

    return 0;
}


// Max Flow

int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}