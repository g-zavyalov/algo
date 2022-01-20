#ifdef TEST_LOCAL
#define _GLIBCXX_DEBUG 1
#endif

#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define x first
#define y second

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef TEST_LOCAL
#define dbg(...) cerr << __func__ << ":" << __LINE__ << " (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

int TEST_NUM = 1;

typedef struct Node* node;
struct Node {
    int64_t i, x;
    node l = 0, r = 0;

    Node(int64_t ni, int64_t nx) {
        i = ni, x = nx;
    }

    void update() {
        int64_t nx = 0;
        if (l) nx += l->x;
        if (r) nx += r->x;
        x = nx;
    }
};


struct SegmentTree { // STRESSED
    int64_t mxl = -1e9,  mxr = 1e9 + 1; // Be careful! [mxl, mxr)
    node tree;
    SegmentTree() {
        tree = new Node(0, 0);
    }

    void set(int64_t i, int64_t x) {
        set(i, x, mxl, mxr, tree);
    }

    void set(int64_t i, int64_t x, int64_t lx, int64_t rx, node &v) {
        if (i < lx || i >= rx) return;
        if (rx - lx == 1) { v = new Node(i, x); return; }
        if (!v) v = new Node(0, 0);
        int m = (lx + rx) / 2;
        set(i, x, lx, m, v->l);
        set(i, x, m, rx, v->r);
        v->update();
    }

    int64_t get(int64_t l, int64_t r) {
        return get(l, r, mxl, mxr, tree);
    }

    int64_t get(int64_t l, int64_t r, int64_t lx, int64_t rx, node &v) {
        if (!v || rx <= l || lx >= r) return 0;
        if (l <= lx && rx <= r) return v->x;
        int m = (lx + rx) / 2;
        int64_t a1 = get(l, r, lx, m, v->l);
        int64_t a2 = get(l, r, m, rx, v->r);
        return a1 + a2;
    }
};

vector<int64_t> solve_st(int n, int qq, const vector<int64_t> &v, const vector<pair<int64_t, int64_t>> &q) {
    SegmentTree tree;
    vector<int64_t> answ;

    forn (i, n) tree.set(i, v[i]);
    forn (i, qq) answ.pb(tree.get(q[i].x, q[i].y));
    
    return answ;
}

vector<int64_t> solve_sl(int n, int qq, const vector<int64_t> &v, const vector<pair<int64_t, int64_t>> &q) {
    vector<int64_t> answ;

    forn (i, qq) {
        auto [l, r] = q[i];
        int64_t a = 0;
        for (; l < r && l < n; l++) a += v[l];
        answ.pb(a);
    }

    return answ;
}

mt19937 rnd(3452);

int64_t gen(int64_t l, int64_t r) {
    return l + rnd() % (r - l + 1);
}



int main(){
#ifndef TEST_LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#endif
    // cin >> TEST_NUM;
    for (int _t = 1; ; _t++) {
#ifdef TEST_LOCAL
        if (TEST_NUM != 1) cout << "Test #" << _t << '\n';       
#endif
        int n = 1e4, q = 10;
        vector<int64_t> v(n);
        vector<pair<int64_t, int64_t>> qq(q);
        forn (i, n) v[i] = gen(-100, 100);
        forn (i, q) {
            int64_t l = gen(0, 3 * n);
            int64_t r = gen(0, 3 * n);
            if (l > r) swap(l, r);
            if (l == r) {i--; continue;}
            qq[i] = {l, r};
        }
        auto a1 = solve_sl(n, q, v, qq);
        auto a2 = solve_st(n, q, v, qq);
        if (a1 == a2)
            cerr << "Test #" << ' ' << _t << " passed!" << '\n';
        else {
            cerr << "Test #" << ' ' << _t << " WA!" << '\n';
            dbg(n, q);
            forn (i, n) cerr << v[i] << " \n"[i == n - 1];
            forn (i, q) {
                auto [l, r] = qq[i];
                dbg(l, r);
            }
            return 0;
        }
    }
}
