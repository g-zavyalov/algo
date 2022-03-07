mt19937 rnd(3452);

typedef struct TreapNode* Node;
struct TreapNode {
    int x, y;
    Node l = 0, r = 0;
    
    int size = 1;
    int mn = INT_MAX;
    int rev = 0;

    TreapNode(int _) {
        x = _, y = rnd();

        mn = x;
    }
};

int size(Node v) { return v ? v->size : 0; }
int mn(Node v) { return v ? v->mn : INT_MAX; }

void update (Node v) {
    v->size = 1 + size(v->l) + size(v->r);
    v->mn = min({v->x, mn(v->l), mn(v->r)});
}

void push(Node v) {
    if (!v || !v->rev) return;
    swap(v->l, v->r);
    if (v->l) v->l->rev ^= 1;
    if (v->r) v->r->rev ^= 1;
    v->rev = 0;
}

void print(Node v) {
    if (!v) { return; }
    push(v);
    print(v->l); dbg(v->x, v->mn, v->size); print(v->r);
}


struct Treap {
    Node tree = 0;

    pair<Node, Node> split(Node v, int x) {
        if (!v) return {0, 0};
        push(v);
        if (size(v->l) < x) {
            auto [l, r] = split(v->r, x - size(v->l) - 1);
            v->r = l;
            update(v);
            return {v, r};
        } else {
            auto [l, r] = split(v->l, x);
            v->l = r;
            update(v);
            return {l, v};
        }
    }

    pair<Node, Node> split(int x) {
        return split(tree, x);
    }

    Node merge(Node l, Node r) {
        if (!l || !r) return max(l, r);
        push(l), push(r);
        if (l->y > r->y) {
            l->r = merge(l->r, r);
            update(l);
            return l;
        } else {
            r->l = merge(l, r->l);
            update(r);
            return r;
        }
    }

    void push_back(int x) {
        tree = merge(tree, new TreapNode(x));
    }

    int apply(int l, int r, function<int(Node)> f) { // [ )
        auto [T, R] = split(tree, r);
        auto [L, M] = split(T, l);
        int res = f(M);
        tree = merge(L, merge(M, R));
        return res;
    }
};


void solve() {
    auto treap = Treap();
    #define tree treap.tree

    int n; cin >> n;
    forn (i, n) treap.pb(i);
    print(tree);

    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        treap.apply(l, r, [](Node v) {
            v->rev = 1;
            return 0;
        });
        print(tree);
    }

}
