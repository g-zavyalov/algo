struct Node {
    int x, i;
    Node() : x(INT_MAX), i(-1) {}
    Node(int _, int __) : x(_), i(__) {}
    Node operator*(Node &r) {
        if (x < r.x) return Node(x, i);
        else return r;
    }
};

template<class T>
struct SegmentTree { // SegmentTree template
    int n;
    vector<T> tree;

    SegmentTree() {}
    SegmentTree(int size) : n(size), tree(size * 4, T()) {}

    void set(int i, T x) { set(i, x, 1, 0, n); }

    void set(int i, T x, int v, int lx, int rx) {
        if (i < lx || i >= rx) return;
        if (rx - lx == 1) {
            tree[v] = x;
            return;
        }
        int m = (lx + rx) / 2;
        set(i, x, v * 2, lx, m);
        set(i, x, v * 2 + 1, m, rx);
        tree[v] = tree[v * 2] * tree[v * 2 + 1];
    }

    T get(int l, int r) { return get(l, r, 1, 0, n); }

    T get(int l, int r, int v, int lx, int rx) {
        if (lx >= r || rx <= l) return T();
        if (lx >= l && rx <= r) return tree[v];
        int m = (lx + rx) / 2;
        auto subl = get(l, r, v * 2, lx, m);
        auto subr = get(l, r, v * 2 + 1, m, rx);
        return subl * subr;
    }
};

struct Graph {
    int n, root = -1;
    vector<vector<int>> G;

    Graph(const int &size): n(size), G(size) {} 
    Graph(const Graph &_): n(_.n), root(_.root) {
        G = _.G;
    } 

    void add_edge(int a, int b, bool oriented = false) {
        G[a].pb(b);
        if (!oriented) G[b].pb(a);
    }

    vector<int> &operator[](int i) {
        assert(i < n);
        return G[i];
    };
};

template <class T>
struct LCA {
    T G;
    vector<int> depth;
    vector<int> euler, first_occ;
    SegmentTree<Node> st;


    LCA(const T &_) : G(_) {
        depth = vector<int>(G.n, 0);
        first_occ = vector<int>(G.n, 0);
        count_depth(G.root, -1, 0);
        make_euler(G.root, -1);
        st = SegmentTree<Node>(euler.size());
        forn (i, euler.size())
            st.set(i, Node(depth[euler[i]], i));
    }

    void make_euler(int v, int p) {
        first_occ[v] = euler.size();
        euler.pb(v);
        for (int x : G[v]) {
            if (x == p) continue;
            make_euler(x, v);
            euler.pb(v);

        }
    }

    void count_depth(int v, int p, int d) {
        depth[v] = d;
        for (int x : G[v]) {
            if (x == p) continue;
            count_depth(x, v, d + 1);
        }
    }

    int get(int a, int b) {
        a = first_occ[a], b = first_occ[b];
        if (a > b) swap(a, b);
        return euler[st.get(a, b + 1).i];
    }
};

void solve() {
    int n; cin >> n;
    int root; cin >> root;
    Graph G(n);
    G.root = root - 1;

    forn (i, n - 1) {
        int a, b; cin >> a >> b;
        G.add_edge(a - 1, b - 1);
    }

    LCA<Graph> lca(G);
    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        a--, b--;
        cout << lca.get(a, b) << '\n';
    }
}