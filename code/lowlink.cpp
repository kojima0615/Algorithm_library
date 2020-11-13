/*
[橋]
辺を消すと、連結成分が増加するような辺

[関節点]
頂点とその頂点に付随する辺を消すと、連結成分が増加するような頂点
頂点に接続された橋が存在するとき、関節点といえる
*/
template<class T>
 struct Edge {
     int from, to;
     T cost;
 
     Edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}
 
     explicit operator int() const { return to; }
 };
 
 template<class T>
 using Edges = vector<Edge<T>>;
 
 template<class T>
 using WeightedGraph = vector<Edges<T>>;
 
 using UnWeightedGraph = vector<vector<int>>;
 
 template<class T>
 using DistMatrix = vector<vector<T>>;
 
 struct GraphAdapter {
     template<class T>
     static UnWeightedGraph to_unweighted_graph(const WeightedGraph<T> &origin) {
         int V = origin.size();
         UnWeightedGraph graph(V);
         for (int i = 0; i < V; i++) for (auto &e: origin[i]) graph[i].push_back((int) e);
         return graph;
     }
 
     static WeightedGraph<int> to_weighted_graph(const UnWeightedGraph &origin) {
         int V = origin.size();
         WeightedGraph<int> graph(V);
         for (int i = 0; i < V; i++) for (auto to: origin[i]) graph[i].push_back({i, to, 1});
         return graph;
     }
 
     template<class T>
     static DistMatrix<T> to_dist_matrix(const WeightedGraph<T> &origin, T INF) {
         int V = origin.size();
         DistMatrix<T> matrix(V, vector<T>(V, INF));
         for (int i = 0; i < V; i++) for (auto &e:origin[i]) matrix[i][e.to] = e.cost;
         for (int i = 0; i < V; i++) matrix[i][i] = 0;
         return matrix;
     }
 };
 
 template<typename G>
 struct LowLink {
     const G &g;
 
     int k;
     vector<int> used, ord, low;
 
     vector<int> articulations;
     vector<pair<int, int>> bridges;
 
     LowLink(const G &g) : g(g) {}
 
     void dfs(int v, int p) {
         used[v] = 1;
         ord[v] = low[v] = k++;
         bool is_art = false;
         int cnt = 0;
         for (auto &to: g[v]) {
             if (!used[to]) {
                 cnt++;
                 dfs(to, v);
                 low[v] = min(low[v], low[to]);
                 is_art |= ~p && ord[v] <= low[to];
                 if (ord[v] < low[to]) bridges.emplace_back(min(v, (int) to), max(v, (int) to));
             } else if (to != p) {
                 low[v] = min(low[v], ord[to]);
             }
         }
         is_art |= p == -1 and cnt > 1;
         if (is_art) articulations.push_back(v);
     }
 
     void build() {
         int n = g.size();
         used.assign(n, 0);
         ord.assign(n, 0);
         low.assign(n, 0);
         k = 0;
         for (int i = 0; i < n; i++) {
             if (!used[i]) {
                 dfs(i, -1);
             }
         }
     }
 };
 
 int main() {
 
     int N;
     cin >> N;
 
     UnWeightedGraph G(N);
 
     UnionFind UF(N);
     REP(i, N - 1) {
         int a, b;
         cin >> a >> b;
         UF.unite(a, b);
         G[a].push_back(b);
         G[b].push_back(a);
     }
 
     int connects = UF.get_connectivity();
     if (connects == 1) {
         cout << "Bob" << endl;
         return 0;
     }
     if (connects >= 3) {
         cout << "Alice" << endl;
         return 0;
     }
 
     LowLink<UnWeightedGraph> lowLink(G);
     lowLink.build();
 
     auto bridges = lowLink.bridges;
     if (bridges.size()) cout << "Alice" << endl;
     else cout << "Bob" << endl;
 
 }