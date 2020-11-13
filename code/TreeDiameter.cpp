vector<vector<int>> G;
// treeDFS(親, 現在地, 根から現在地までの距離, 根からの最大の距離, 根から最大の距離となる頂点
void treeDFS(int from, int current, int dist, int &maxDist, int &maxVertex)
{
    // 距離と終点を更新
    if (dist > maxDist)
    {
        maxDist = dist;
        maxVertex = current;
    }

    for (auto to : G[current])
    {
        // 逆流を防ぐ
        if (to == from)
            continue;
        treeDFS(current, to, dist + 1, maxDist, maxVertex);
    }
}

int getTreeDiameter()
{
    //ある点からDFSして最も遠かった点から2回目のDFSする
    //二回目の始点と最も遠い点が直径になる
    int start = 0, end = 0, maxDist = 0;
    treeDFS(-1, start, 0, maxDist, end);
    start = end, end = 0, maxDist = 0;
    treeDFS(-1, start, 0, maxDist, end);
    return maxDist;
    //printf("start: %d, end: %d, diameter: %d\n", start, end, maxDist);
}