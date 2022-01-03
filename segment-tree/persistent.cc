typedef struct Node* node;
struct Node {
    int64_t i, x;
    node l = 0, r = 0;

    Node(int64_t ni, int64_t nx) {
        i = ni, x = nx;
    }

    Node(int64_t ni, int64_t nx, node ll, node rr) {
        i = ni, x = nx, l = ll, r = rr;
    }

    void update() {
        int64_t nx = 0;
        if (l) nx += l->x;
        if (r) nx += r->x;
        x = nx;
    }

    void print() {
        if (l) l->print();
        cerr << i << ' ' << x << '\n';
        if (r) r->print();
    }
};

struct PersistentSegmentTree { //STRESSED
    int64_t mxl = -1e9,  mxr = 1e9 + 1; // Be careful! [mxl, mxr)
    node tree;

    PersistentSegmentTree() {
        tree = new Node(0, 0);
    }

    PersistentSegmentTree(const node &v) {
        tree = v;
    }

    node set(int64_t i, int64_t x) {
        return set(i, x, mxl, mxr, tree);
    }

    node set(int64_t i, int64_t x, int64_t lx, int64_t rx, node v) {
        if (i < lx || i >= rx) return v;
        if (rx - lx == 1) { v = new Node(i, x); return v;}
        if (!v) v = new Node(0, 0);
        else v = new Node(0, 0, v->l, v->r);
        int m = (lx + rx) / 2;
        v->l = set(i, x, lx, m, v->l);
        v->r = set(i, x, m, rx, v->r);
        v->update();
        return v;
    }

    int64_t get(int64_t l, int64_t r) {
        return get(l, r, mxl, mxr, tree);
    }

    int64_t get(int64_t l, int64_t r, int64_t lx, int64_t rx, node v) {
        if (!v || rx <= l || lx >= r) return 0;
        if (l <= lx && rx <= r) return v->x;
        int m = (lx + rx) / 2;
        int64_t a1 = get(l, r, lx, m, v->l);
        int64_t a2 = get(l, r, m, rx, v->r);
        return a1 + a2;
    }
};

vector<PersistentSegmentTree> time_machine;
vector<int64_t> answ;
PersistentSegmentTree tree;
time_machine.pb(tree);

forn (i, n) {
    node nv = time_machine.back().set(v[i], time_machine.back().get(v[i], v[i] + 1) + 1);
    time_machine.pb(PersistentSegmentTree(nv));
}
