struct sparse_table{
    int H, N;
    vector<vector<int>>table; vector<int>d, par;
    vector<vector<int>>edges;

    sparse_table(int n) {
        N = n; H = __lg(N) + 1;
        table.resize(H + 1, vector<int>(N + 1)); edges.resize(N + 1);
        d.resize(N + 1, 0); par.resize(N + 1, 0);
    }

    int lca(int u, int v){
        if(d[u] < d[v]) swap(u, v);

        int dh = d[u] - d[v];
        for(int k=H; k>=0; k--){
            if((1<<k) > dh) continue;
            else{ u = table[k][u]; dh -= (1 << k); }
        } if(u==v) return u;

        for(int k=H; k>=0; k--){
            if((1 << k) > d[u]) continue;
            if(table[k][u] == table[k][v]) continue;

            u = table[k][u];
            v = table[k][v];
        } return par[u];
    }

    void build() {
        bool vis[N + 1]; fill(vis, vis + N + 1, 0);
        dfs(1, 1, vis);

        for(int i=1; i<=N; i++){
            table[0][i] = par[i];
        }
        for(int k=1; k<=H; k++){
            for(int i=1; i<=N; i++){
                table[k][i] = table[k-1][table[k-1][i]];
            }
        }
    }

    void dfs(int cur, int dep, bool vis[]) {
        d[cur] = dep; vis[cur] = 1;
        for(int &nxt:edges[cur]) {
            if(vis[nxt]) continue;
            par[nxt] = cur;
            dfs(nxt, dep + 1, vis);
        }
    }
};
