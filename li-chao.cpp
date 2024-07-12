struct Line{
    ll m, c;
    Line(){m = 0, c = INF;}
    Line(ll mm, ll cc){m = mm, c = cc;}
    ll f(ll x) {return m*x + c;}
    bool operator==(Line other) {return m == other.m && c == other.c;}
};

struct Lichao {
    struct Node { Line li; int l; int r; ll s; ll e;};
    // l and r are children, s and e are ends of range
    const ll S = -1e9-7, E = 1e9+7;
    vector<Node> tree;
    stack< pair<int, Node> >op; //idx, lichao_node

    void init(){
        tree.push_back({Line(), -1, -1, S, E});
    }

    void insert(int idx, Line line){
        op.push({idx, tree[idx]}); //store previous state for rollback

        ll st = tree[idx].s, ed = tree[idx].e;
        ll mid = (st + ed) >> 1LL;

        Line v = tree[idx].li, w = line;
        if(v.f(st) < w.f(st)) swap(v, w);
        if(v.f(ed) >= w.f(ed)) {
            tree[idx].li = w; return;
        }
        if(v.f(mid) > w.f(mid)){
            tree[idx].li = w;
            if(tree[idx].r == -1){
                tree[idx].r = tree.size();
                tree.push_back({Line(), -1, -1, mid + 1, ed});
            }
            insert(tree[idx].r, v);
        }
        else{
            tree[idx].li = v;
            if(tree[idx].l == -1){
                tree[idx].l = tree.size();
                tree.push_back({Line(), -1, -1, st, mid});
            }
            insert(tree[idx].l, w);
        }
    }

    ll query(int idx, ll x){
        if(idx == -1) return INF;
        ll st = tree[idx].s, ed = tree[idx].e;
        ll mid = (st+ed)>>1LL;
        if(x <= mid) return min(tree[idx].li.f(x), query(tree[idx].l , x));
        else return min(tree[idx].li.f(x), query(tree[idx].r, x));
    }

    void rollback(int t){
        while(t-->0 && !op.empty()){
            int idx = op.top().fr; Node pr = op.top().sc; op.pop();
            tree[idx] = pr;
        }
    }
};
