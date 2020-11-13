//ダイクストラ
//LINFにしてあるよ
struct edge
{
    ll to, cost;
};
typedef pair<ll, ll> P;
struct graph
{
    ll V;
    vector<vector<edge>> G;
    vector<ll> d;
    //vector<ll> count;経路の本数
    //vector<ll> prev; // prev[v] := v から復元できる辺たち
    graph(ll n)
    {
        init(n);
    }

    void init(ll n)
    {
        V = n;
        G.resize(V);
        d.resize(V);
        //count.resize(V);
        rep(i, V)
        {
            d[i] = LINF;
            //count[i] = 0;
        }
    }

    void add_edge(ll s, ll t, ll cost)
    {
        edge e;
        e.to = t, e.cost = cost;
        G[s].push_back(e);
    }

    void dijkstra(ll s)
    {
        rep(i, V)
        {
            d[i] = LINF;
            //count[i] = 0;
        }
        d[s] = 0;
        //count[s] = 1;
        priority_queue<P, vector<P>, greater<P>> que;
        que.push(P(0, s));
        while (!que.empty())
        {
            P p = que.top();
            que.pop();
            ll v = p.second;
            if (d[v] < p.first)
                continue;
            for (auto e : G[v])
            {
                if (d[e.to] > d[v] + e.cost)
                {
                    d[e.to] = d[v] + e.cost;
                    que.push(P(d[e.to], e.to));
                    //count[e.to] = count[v];
                    // 復元のための
                    //prev[e.to]=v;
                }
                /*
        else if (d[e.to] == d[v] + e.cost)
                {
                    count[e.to] += count[v];
                    count[e.to] %= MOD;
                }
                */
            }
        }
    }
};
graph g(n);

g.add_edge(a, b, cost);
g.dijkstra(s);

int dist = g.d[i]:
