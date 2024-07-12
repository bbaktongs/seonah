template <const int V, typename T, const T INF>
struct max_flow {
    vector<int> adj[V], ldj[V];
    int src, snk, dist[V]{};
    T res[V][V]{};
    max_flow(int s, int t): src(s), snk(t) {}
    void add(int u, int v, T f) {
        res[u][v] += f;
        if (f == 0 or res[u][v] > f or res[v][u] > 0) return;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    T augment(int s, T a=INF) {
        if (s == snk) return a;
        for (; !ldj[s].empty(); ldj[s].pop_back()) {
            int u = ldj[s].back();
            if (!res[s][u]) continue;
            T r = augment(u, min(a,res[s][u]));
            if (r > 0) {
                res[s][u] -= r;
                res[u][s] += r;
                return r;
            }
        }
        return 0;
    }
    bool build() {
        queue<int> q;
        for(int i=0; i<V; i++) ldj[i].clear(), dist[i]=1e9;
        dist[src]=0, q.push(src);
        while (not q.empty()) {
            int s = q.front(); q.pop();
            for (auto u : adj[s]) if (res[s][u] > 0) {
                if (dist[u] == int(1e9)) dist[u] = dist[s]+1, q.push(u);
                if (dist[u] == dist[s]+1) ldj[s].push_back(u);
            }
        }
        return dist[snk] != int(1e9);
    }
    T get() {
        T r = 0;
        while (build()) for (T d; (d=augment(src)); r += d);
        return r;
    }
};
