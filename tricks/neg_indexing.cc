template<class T>
struct nvector {
    int lx, rx; // [l, r)
    vector<T> array;

    nvector(int l, int r, T &&values = T()) : lx(l), rx(r) {
        array.resize(abs(l) + r, values);
    }

    T& operator[](int i) {
        i += abs(lx);
        assert(0 <= i && i < int(array.size()));
        return array[i];
    }
};
