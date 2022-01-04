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

int64_t gen(int64_t l, int64_t r) {
    return l + rand() % (r - l + 1);
}

void solve() {
    cout << 1 << '\n';
    int n = 4;
    cout << n << '\n';
    forn (i, n) {
        int64_t l = gen(1, 5), r = l + gen(1, 5), c = gen(1, 5);
        cout << l << ' ' << r << ' ' << c;
        cout << '\n';
    }
}


int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
#ifndef TEST_LOCAL
    cin.tie(0)->sync_with_stdio(0);
#endif
    
    for (int _t = 1; _t <= TEST_NUM; _t++) {
#ifdef TEST_LOCAL
        if (TEST_NUM != 1) cout << "Test #" << _t << '\n';
#endif
        solve();
    }
}
