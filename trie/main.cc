const int size = 1e5 + 1; // max trie size;
int mx_cnt = 1; // count of all the Vs in trie
vector<map<char, int>> trie(size);
auto trie_down = [&] (const string &s) {
    int v = 0; // root
    for (char x : s) {
        int &r = trie[v][x];
        if (!r) r = mx_cnt++;
        v = r;
    }
    return v;
};
