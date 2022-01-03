struct STNode {
    int x;
    STNode() : x(0) {}
    STNode(int _) : x(_) {}
    STNode operator*(STNode &r) { return x + r.x; }
};

template<class T>
struct SegmentTree {
    int n;
    vector<T> tree;

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

