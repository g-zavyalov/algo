void output()  {
    output(1, 0, N, 0);
}

void output(int v, int vl, int vr, int depth)  {
    int vm = (vl + vr) / 2;
    if (vr - vl > 1)
        output(2 * v, vl, vm, depth + 1);

    printf("%*s%d\n", 2 * depth, "", a[v]); 
    if (vr - vl > 1)
        output(2 * v + 1, vm, vr, depth + 1);
}
