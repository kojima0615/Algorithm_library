template< typename T >
struct SparseTable {
  vector< vector< T > > st;
  vector< int > lookup;

  SparseTable(const vector< T > &v) {
    int b = 0;
    while((1 << b) <= v.size()) ++b;
    st.assign(b, vector< T >(1 << b));
    for(int i = 0; i < v.size(); i++) {
      st[0][i] = v[i];
    }
    for(int i = 1; i < b; i++) {
      for(int j = 0; j + (1 << i) <= (1 << b); j++) {
        //ここでmin, maxを入れ替える
        st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
    lookup.resize(v.size() + 1);
    for(int i = 2; i < lookup.size(); i++) {
      lookup[i] = lookup[i >> 1] + 1;
    }
  }

  inline T rmq(int l, int r) {
    int b = lookup[r - l];
    return min(st[b][l], st[b][r - (1 << b)]);
  }
};
int q;
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n;
    vector<int> vs;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        vs.push_back(temp);
    }
    SparseTable<int> table(vs);
    cin>>q;
    for(int i=0;i<q;i++){
        int x, y;
        cin>>x>>y;
        //[x,y)yを含まない最小,最大値
        cout<<table.rmq(x,y)<<"\n";
    }
}
