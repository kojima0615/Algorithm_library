
//ベルマンフォード
class BellmanFord
{
public:
    typedef struct Edge
    {
        ll from;
        ll to;
        ll cost;
        Edge(ll f, ll t, ll c) : from(f), to(t), cost(c) {}
    } Edge;
    ll edge_num, vertex_num, start, goal;
    vector<Edge> edges;
    vector<ll> dist;
    vector<ll> afby_nc;

    BellmanFord(ll e, ll v, ll s, ll g) : edge_num(e), vertex_num(v), start(s), goal(g)
    {
        dist = vector<ll>(vertex_num, INF);
        dist[start] = 0;
        afby_nc = vector<ll>(vertex_num, false);
    }

    void connect(ll from, ll to, ll cost)
    {
        edges.push_back(Edge(from, to, cost));
    }

    void relax()
    {
        REP(i, vertex_num)
        {
            for (auto edge : edges)
            {
                if (dist[edge.from] != INF && dist[edge.to] > dist[edge.from] + edge.cost)
                    dist[edge.to] = dist[edge.from] + edge.cost;
            }
        }
    }

    void check_negative_cycle()
    {
        REP(i, vertex_num)
        {
            for (auto edge : edges)
            {
                if (dist[edge.from] == INF)
                    continue;
                if (dist[edge.to] > dist[edge.from] + edge.cost)
                {
                    afby_nc[edge.to] = true;
                    dist[edge.to] = dist[edge.from] + edge.cost;
                }
                if (afby_nc[edge.from] == true)
                    afby_nc[edge.to] = true;
            }
        }
    }

    ll distance()
    {
        this->relax(); //this->object内で自分のメンバ関数を呼び出すときに使う
        ll ans_dist = dist[goal];
        //for(auto vv:dist)prllf("###%lld\n",vv);
        this->check_negative_cycle();
        //for(auto vv:dist)prllf("######%lld\n",vv);
        if (ans_dist > dist[goal] || afby_nc[goal] == true)
            return -INF;
        else
            return ans_dist;
    }
};
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    ll a, b, c;
    BellmanFord bf(m, n, 0, n - 1);
    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        bf.connect(a - 1, b - 1, -c);
    }
    ll dist = bf.distance();
    if (dist == -INF)
        cout << "inf"
             << "\n";
    else
        cout << -dist << "\n";
}