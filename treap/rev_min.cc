mt19937 rnd(237);

typedef struct node* Node;
struct node {
    int x, y;
    int mn = INT_MAX, size = 1;
    int rev = 0;
    Node l = 0, r = 0;

    node(int _x) { x = mn = _x; y = rnd(); }

    void print() {
        if (rev) rev = 0, swap(l, r);
        if (l) l->print();
        cerr << x << ' ';
        if (r) r->print();
    }
};

int size(Node v) { return v ? v->size : 0; }
int mn(Node v) { return v ? v->mn : INT_MAX; }

void update (Node v) {
    v->size = 1 + size(v->l) + size(v->r);
    v->mn = min({v->x, mn(v->l), mn(v->r)});
}

void push(Node v) {
    if (!v) return;
    if (!v->rev) return;
    swap(v->l, v->r);
    if (v->l) v->l->rev ^= 1; 
    if (v->r) v->r->rev ^= 1; 
    v->rev = 0;
}



void Print(Node t) {
    if (t) { t->print(); }
    else cerr << "nil";
    cerr << '\n';
}

pair<Node, Node> split(Node v, int x) { // cut first x elements
    if (!v) return {0, 0};
    push(v);
    if (size(v->l) + 1 <= x) {
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

void push_back(Node &tree, int x) {
    tree = merge(tree, new node(x));
}

void solve() {
    Node tree = 0;

    int n, q; cin >> n >> q;

    forn (i, n) {
        int x; cin >> x;
        tree = merge(tree, new node(x));
    }
    while (q--) {
        int m, l, r; cin >> m >> l >> r;
        if (m & 1) {
            auto [la, ra] = split(tree, r);
            auto [lb, rb] = split(la, l - 1);
            rb->rev ^= 1;
            tree = merge(lb, merge(rb, ra));
        } else {
            auto [la, ra] = split(tree, r);
            auto [lb, rb] = split(la, l - 1);
            cout << rb->mn << '\n';
            tree = merge(lb, merge(rb, ra));
        }
    }
}
