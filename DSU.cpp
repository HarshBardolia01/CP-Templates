class DSU {
public:
    int n;
    vector<int> parent;
    vector<int> size;

    DSU(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int n) {
        if (n == parent[n])
            return n;
        return parent[n] = find(parent[n]);
    }

    void unionset(int a, int b) {
        a = find(a);
        b = find(b);

        if (a != b) {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};