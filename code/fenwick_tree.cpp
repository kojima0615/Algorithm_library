//1-indexだから0にaddすると死んじゃうよ
struct fenwick_tree {
    typedef int T;
    T n;
    vector<T> bit;
    T b = 1;
    // 各要素の初期値は 0
    fenwick_tree(T num) : bit(num+1, 0) { n = num; }

    // a_i += w
    void add(T i, T w) {
        for (T x = i; x <= n; x += x & -x) {
            bit[x] += w;
        }
    }
    ll get(T i){
        ll s = 0;
		while(i > 0) { s += bit[i]; i -= i & -i; }
		return s;
    }
    // [1, i] の和を計算.
    T sum(T i) {
        T ret = 0;
        for (T x = i; x > 0; x -= x & -x) {
            ret += bit[x];
        }
        return ret;
    }
    // [left+1, right] の和を計算.
    T sum(T left, T right) {
        return sum(right) - sum(left);
    }
    int get_index(ll x) { //something like lower_bound(all(sum), a). O(logn)
		x--;
        while(b * 2 <= n) b *= 2;
		int r = b;
		int res = 0;
		while(r > 0) {
			if((r | res) <= n) {
				int rv = bit[r | res];
				if(x >= rv) {
					x -= rv;
					res += r;
				}
			}
			r >>= 1;
		}
		return res + 1;
	}
};
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    int q;
    cin >> q;
    vector<ll> ans;
    int n=200001;
    fenwick_tree ft(n);
    for (int i = 0; i < q; i++)
    {
        int t, x;
        cin >>t>>x;
        if(t==1){
            ft.add(x,1);
        }
        else{
            int j=ft.get_index(x);
            ans.push_back(j);
            ft.add(j,-1);
        }
    }
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<"\n";
    }
}
//https://atcoder.jp/contests/arc033/submissions/8373951
//ここを見るとBITを拡張できそう
