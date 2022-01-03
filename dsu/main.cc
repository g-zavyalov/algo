struct dsu {
    vector<int> tree;
    dsu(int n) : tree(n) {
        forn (i, n) tree[i] = i;
    }
    void union_set(int x, int y) {
        tree[get_set(x)] = get_set(y);
    }
    int get_set(int x) {
        return x == tree[x] ? x : tree[x] = get_set(tree[x]);
    }
};
