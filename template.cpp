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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

constexpr ll inf = 1e18;
const ll N = 3e5 + 5;
const ll M = 505;
const ll MOD = 1e9 + 7; // 998244353 // 1000000007

void solve() {

}   

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc = 1, C = 1;
    //cin >> tc;
    cout << fixed << setprecision(10);
    while (tc--) {
        //cout << "Case " << C++ << ": ";

        solve();
    }
}