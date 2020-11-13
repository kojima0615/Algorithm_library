struct Bipartite_Matching
{
    vector<vector<int>> graph;
    vector<int> match, alive, used;
    int timestamp;

    Bipartite_Matching(int n)
    {
        timestamp = 0;
        graph.resize(n);
        alive.assign(n, 1);
        used.assign(n, 0);
        match.assign(n, -1);
    }

    void add_edge(int u, int v)
    {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    bool dfs(int v)
    {
        used[v] = timestamp;
        for (int i = 0; i < graph[v].size(); i++)
        {
            int u = graph[v][i], w = match[u];
            if (alive[u] == 0)
                continue;
            if (w == -1 || (used[w] != timestamp && dfs(w)))
            {
                match[v] = u;
                match[u] = v;
                return (true);
            }
        }
        return (false);
    }

    int bipartite_matching()
    {
        int ret = 0;
        for (int i = 0; i < graph.size(); i++)
        {
            if (alive[i] == 0)
                continue;
            if (match[i] == -1)
            {
                ++timestamp;
                ret += dfs(i);
            }
        }
        return (ret);
    }
};
Bipartite_Matching bm(node数);
//最小点被覆=二部マッチングの数
//点から伸びる辺で全ての点をカバーできる
//頂点からなる集合のうち、それらの頂点から出ている辺をすべて集めるとすべての辺を覆うようなものを点被覆とよび、
//最小サイズの点被覆を求める問題です。下図では赤丸で示した 3 頂点が最小点被覆の一例になっています。

//最大安定集合
//頂点数-マッチングの数
//頂点からなる集合のうち、どの 2 頂点も辺で結ばれていないようなものを安定集合とよび、最大サイズの安定集合を求める問題です。
//下図では赤丸で示した 3 頂点が最大安定集合の一例になっています。

int n;
int V;
int a[200], b[200], c[100], d[100];
vector<int> G[200];
int match[200];
bool used[200];
void add_edge(int u, int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
bool dfs(int v)
{
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++)
    {
        int u = G[v][i], w = match[u];
        if (w < 0 || !used[w] && dfs(w))
        {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}
int bipartite_matching()
{
    int res = 0;
    for (int i = 0; i < V; i++)
    {
        match[i] = -1;
    }
    for (int v = 0; v < V; v++)
    {
        if (match[v] < 0)
        {
            for (int i = 0; i < V; i++)
            {
                used[i] = 0;
            }
            if (dfs(v))
            {
                res++;
            }
        }
    }
    return res;
}
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n;
    V = n * 2;
    for (int i = 0; i < 2 * n; i++)
    {
        cin >> a[i] >> b[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i] < a[j + n] && b[i] < b[j + n])
            {
                add_edge(i, j + n);
            }
        }
    }
    cout << bipartite_matching() << "\n";
}
