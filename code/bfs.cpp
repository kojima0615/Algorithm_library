struct Corr
{
    ll y;
    ll x;
    ll depth;
};
ll N, M;               // 迷路の縦，横
ll s_y, s_x, g_y, g_x; // スタート，ゴールの座標
ll y, x, depth;        // キューから取り出した座標
vector<string> vec;    // 座標を受け取る配列
queue<Corr> q;

vector<ll> y_vec = {0, 0, -1, +1}; // 進む方向の簡便化，テクニックとして覚えておく．
vector<ll> x_vec = {-1, +1, 0, 0}; // ループで回すことで上下左右に移動できるようになっている
ll bfs()
{
    while (!q.empty())
    {
        Corr now = q.front();
        q.pop();                                 // キューの先頭を取り出す
        y = now.y, x = now.x, depth = now.depth; // 行，列が y, x になっているので注意

        // 停止条件：現在の座標がゴールなら深さを返す
        if (y == g_y && x == g_x)
            return depth;

        // 上下左右 4 方向を探索．進むことができればキューに格納する．
        for (ll i = 0; i < 4; ++i)
        {
            Corr next = {y + y_vec[i], x + x_vec[i], depth + 1};
            if (0 <= next.y && next.y <= N - 1 && 0 <= next.x && next.x <= M - 1 && vec[next.y][next.x] == '.')
            {
                vec[next.y][next.x] = 'x'; // 同じ場所を探索しないようにする
                q.push(next);
            }
        }
    }
    return 0;
}