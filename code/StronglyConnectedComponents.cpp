//#include <tourist>
#include <bits/stdc++.h>
//#include <atcoder/all>
using namespace std;
//using namespace atcoder;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<ll, ll> p;
const int INF = 1e9;
const ll LINF = ll(1e18);
const int MOD = 1000000007;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {-1, 0, 1, 0};
const int Dx[8] = {0, 1, 1, 1, 0, -1, -1, -1}, Dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
#define yes cout << "Yes" << endl
#define YES cout << "YES" << endl
#define no cout << "No" << endl
#define NO cout << "NO" << endl
#define rep(i, n) for (int i = 0; i < n; i++)
#define FOR(i, m, n) for (int i = m; i < n; i++)
#define ALL(v) v.begin(), v.end()
#define debug(v)          \
    cout << #v << ":";    \
    for (auto x : v)      \
    {                     \
        cout << x << ' '; \
    }                     \
    cout << endl;
template <class T>
bool chmax(T &a, const T &b)
{
    if (a < b)
    {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
bool chmin(T &a, const T &b)
{
    if (b < a)
    {
        a = b;
        return 1;
    }
    return 0;
}
//cout<<fixed<<setprecision(15);有効数字15桁
//-std=c++14
//g++ yarudake.cpp -std=c++17 -I .
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

struct StronglyConnectedComponents
{
    vector<vector<int>> g;
    vector<vector<int>> to, from;
    vector<int> comp, order, used;
    StronglyConnectedComponents(vector<vector<int>> &g) : g(g), to(g.size()), from(g.size()), comp(g.size(), -1), used(g.size())
    {
        for (int i = 0; i < g.size(); i++)
        {
            for (auto x : g[i])
            {
                to[i].push_back(x);
                from[x].push_back(i);
            }
        }
    }
    int operator[](int k)
    {
        return comp[k];
    }
    void dfs(int now)
    {
        if (used[now])
            return;
        used[now] = true;
        for (int x : to[now])
            dfs(x);
        order.push_back(now);
    }
    void rdfs(int now, int cnt)
    {
        if (comp[now] != -1)
            return;
        comp[now] = cnt;
        for (int x : from[now])
            rdfs(x, cnt);
    }
    vector<vector<int>> build()
    {
        vector<vector<int>> t;
        for (int i = 0; i < to.size(); i++)
            dfs(i);
        reverse(order.begin(), order.end());
        int ptr = 0;
        for (int i : order)
            if (comp[i] == -1)
                rdfs(i, ptr), ptr++;

        t.resize(ptr);
        for (int i = 0; i < g.size(); i++)
        {
            for (auto v : to[i])
            {
                int x = comp[i], y = comp[v];
                if (x == y)
                    continue;
                t[x].push_back(y);
            }
        }
        return t;
    }
};
bool dfs(int k, vector<bool> check, vector<vector<int>> &t, int count)
{
    check[k] = true;
    count++;
    bool c = false;
    if (t.size() == count)
        return true;
    rep(i, t[k].size())
    {
        if (!check[t[k][i]])
        {
            c |= dfs(t[k][i], check, t, count);
        }
    }
    return c;
}
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];
    rep(i, n) a[i] %= m;
    vector<vector<int>> g(m); //m点のグラフとして表現
    rep(i, n)
    {
        rep(j, m)
        {
            g[j].push_back((j * a[i] % m));
        }
    }
    StronglyConnectedComponents scc(g);
    vector<vector<int>> t = scc.build();
    /*
    vector<bool> check(t.size(),false);
    if(dfs(scc[1], check,t,0))yes;
    else no;
    */
    if (scc[1] != 0)
    {
        return no, 0;
    }
    rep(i, t.size()-1)
    {
        bool f = false;
        rep(j, t[i].size())
        {
            if (t[i][j] == i + 1)
                f = true;
        }
        if (!f)
            return no, 0;
    }
    yes;
}
class StronglyConnectedComponents
{
public:
    StronglyConnectedComponents(ll n) : n_(n),
                                        edges_(n),
                                        reverse_edges_(n),
                                        order_(n),
                                        num_(0) {}

    void addEdge(ll from, ll to)
    {
        edges_[from].push_back(to);
        reverse_edges_[to].push_back(from);
    }

    vector<vector<ll>> scc()
    {
        visit.assign(n_, false);
        for (ll i = 0; i < n_; i++)
        {
            dfsForward(i);
        }
        sort(order_.begin(), order_.end(), [](const Order &lhs, const Order &rhs) {
            return lhs.order > rhs.order;
        });
        visit.assign(n_, false);
        for (ll i = 0; i < n_; i++)
        {
            auto curr_result = dfsBackward(order_[i].index);
            if (curr_result.size() == 0)
            {
                continue;
            }
            result_.push_back(curr_result);
        }
        return result_;
    }

    vector<vector<ll>> sccEdges()
    {
        vector<vector<ll>> scc_edges(result_.size());
        vector<ll> indexToScc(n_);
        for (ll i = 0; i < (ll)result_.size(); i++)
        {
            for (ll j : result_[i])
            {
                indexToScc[j] = i;
            }
        }

        for (ll i = 0; i < (ll)result_.size(); i++)
        {
            for (ll from : result_[i])
            {
                for (ll to : edges_[from])
                {
                    if (indexToScc[to] == i)
                    {
                        continue;
                    }
                    scc_edges[i].push_back(indexToScc[to]);
                }
            }
        }
        return scc_edges;
    }

private:
    void dfsForward(ll curr)
    {
        if (visit[curr])
        {
            return;
        }
        visit[curr] = true;
        for (ll next : edges_[curr])
        {
            dfsForward(next);
        }
        order_[curr] = {curr, num_++};
        return;
    }

    vector<ll> dfsBackward(ll curr)
    {
        vector<ll> curr_result;
        if (visit[curr])
        {
            return curr_result;
        }
        visit[curr] = true;
        curr_result.push_back(curr);
        for (ll next : reverse_edges_[curr])
        {
            auto members = dfsBackward(next);
            for (ll m : members)
            {
                curr_result.push_back(m);
            }
        }
        return curr_result;
    }

    ll n_;
    vector<vector<ll>> edges_;
    vector<vector<ll>> reverse_edges_;
    struct Order
    {
        ll index, order;
    };
    vector<Order> order_;
    vector<bool> visit;
    vector<vector<ll>> result_;
    ll num_;
};