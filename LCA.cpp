class LCA {
public:
    vector<int> height, euler, first, last, subtree, seg;
    vector<vector<int>> parent;
    vector<bool> visited;
    int n, m, LOG;

    LCA(vector<vector<int>>& tree, int root = 0) {
        n = (int) tree.size();
        LOG = log2(n);
        height.resize(n);
        parent.resize(n, vector<int>(LOG + 1, -1));
        first.resize(n);
        last.resize(n);
        subtree.resize(n, 1);
        visited.resize(n, false);
        euler.clear();
        dfs(tree, root);
        initiate();
        m = (int) euler.size();
        seg.resize(4 * m + 1);
        build(0, 0, m - 1);
    }

    void dfs(vector<vector<int>>& tree, int node, int h = 0) {
        visited[node] = true;
        height[node] = h;
        first[node] = (int) euler.size();
        euler.push_back(node);
        for (auto next : tree[node]) {
            if (!visited[next]) {
                parent[next][0] = node;
                dfs(tree, next, h + 1);
                subtree[node] += subtree[next];
                euler.push_back(node);
            }
        }
        last[node] = (int) euler.size();
    }

    void initiate() {
        for (int i = 1; i <= LOG; i++) {
            for (int node = 0; node < n; node++) {
                int v = parent[node][i - 1];
                if (v != -1)
                    parent[node][i] = parent[v][i - 1];
            }
        }
    }

    void build(int ind, int low, int high) {
        if (low == high) {
            seg[ind] = euler[low];
            return;
        }

        int mid = low + (high - low) / 2;
        build(2 * ind + 1, low, mid);
        build(2 * ind + 2, mid + 1, high);
        int left = seg[2 * ind + 1];
        int right = seg[2 * ind + 2];
        seg[ind] = (height[left] < height[right]) ? left : right;
    }

    int query(int ind, int low, int high, int l, int r) {
        if (low > r || high < l)
            return -1;

        if (low >= l && high <= r)
            return seg[ind];

        int mid = low + (high - low) / 2;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);

        if (left == -1)
            return right;
        if (right == -1)
            return left;

        return (height[left] < height[right]) ? left : right;
    }

    int getLCA(int a, int b) {
        int l = first[a];
        int r = first[b];

        if (l > r)
            swap(l, r);

        return query(0, 0, m - 1, l, r);
    }

    int kthparent(int node, int k) {
        while (k > 0) {
            int x = log2(k);
            node = parent[node][x];
            if (node == -1)
                return node;
            k -= (1 << x);
        }
        return node;
    }
};