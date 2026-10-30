// #pragma GCC optimize("Ofast")
// #pragma GCC optimization ("O3")
// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
typedef long long ll;
#define ld long double
#define ull unsigned long long
#define F first
#define S second
#define gcd __gcd
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define pb push_back
#define eb emplace_backmin
#define ub upper_bound
using namespace std;
 
constexpr ll inf = 1e18;
const ll N = 1e6+5;
const ll M = 1000;
const ll MOD = 1e9+7; // 998244353 // 1000000007

typedef struct item {
    ll mx;
    ll pref;
    ll suf;
    ll sum;
} item;

struct segtree {
    ll size;
    vector<item>segs;

    item single (ll val) {
        return {max(val,0ll),max(val,0ll),max(val,0ll),val};
    }

    item merge (item a, item b) {
        return {max({a.mx,b.mx,a.suf+b.pref}),max(a.pref,a.sum+b.pref),max(b.suf,a.suf+b.sum),a.sum+b.sum};
    }

    void init (ll n) {
        size = 1;
        while (size<n)
            size *= 2;
        segs.assign(2*size,{-inf,-inf,-inf,0ll});
    }

    void build (vector<ll>&v, ll x, ll lx, ll rx) {
        if (rx-lx==1) {
            if (lx<(ll)v.size())
                segs[x] = single(v[lx]);
            return;
        }
        ll mid  = (lx+rx)/2;
        build(v,2*x+1,lx,mid);
        build(v,2*x+2,mid,rx);
        segs[x] = merge(segs[2*x+1],segs[2*x+2]);
    }

    void build (vector<ll>&v) {
        build(v,0,0,size);
    }

    void set (ll i, ll val, ll x, ll lx, ll rx) {
        if (rx-lx==1) {
            segs[x] = single(val);
            return;
        }
        ll mid = (lx+rx)/2;
        if (i<mid) 
            set(i,val,2*x+1,lx,mid);
        else
            set(i,val,2*x+2,mid,rx);
        segs[x] = merge(segs[2*x+1],segs[2*x+2]);
    }

    void set(ll i, ll val) {
        set(i,val,0,0,size);
    }

    item query(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx>=r || rx<=l)
            return {-inf,-inf,-inf,0};
        if (lx>=l && rx<=r)
            return segs[x];
        ll mid = (lx+rx)/2;
        item s1 = query(l,r,2*x+1,lx,mid);
        item s2 = query(l,r,2*x+2,mid,rx);
        return merge(s1,s2);
    }

    item query(ll l, ll r) {
        return query(l,r,0,0,size);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);



    int tc = 1, C = 1;
    //cin >> tc;
    while (tc--) {
        //cout << "Case " << C++ << ": ";

        ll n,m;
        cin >> n >> m;

        segtree st;
        st.init(n);
        vector<ll>v(n);
        for (ll i = 0; i < n; ++i)
            cin >> v[i];
        st.build(v);
        cout << st.query(0,n).mx << "\n";
        while (m--) {
            ll i,val;
            cin >> i >> val;
            st.set(i,val);
            cout << st.query(0,n).mx << "\n";
        }
    }           
}
