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

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef TEST_LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):\t", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

int TEST_NUM = 1;

void solve() {
    
}


int main(){
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
