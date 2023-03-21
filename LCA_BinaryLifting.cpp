class LCA_BinaryLifting {
public:
    int n, time, LOG;
    vector<int> inTime, outTime;
    vector<vector<int>> parent;

    LCA_BinaryLifting(vector<vector<int>> &tree, int root = 0) {
        n = (int) tree.size();
        LOG = log2(n);
        inTime.resize(n);
        outTime.resize(n);
        parent.resize(n, vector<int>(LOG + 1));
        time = 0;
        dfs(tree, root);
    }

    void dfs(vector<vector<int>> &adj, int cur) {
        inTime[cur] = time++;
        for (int i = 1; i <= LOG; i++)
            parent[cur][i] = parent[parent[cur][i - 1]][i - 1];
        for (auto nx : adj[cur]) {
            if (nx == parent[cur][0]) continue;
            parent[nx][0] = cur;
            dfs(adj, nx);
        }
        outTime[cur] = time++;
    }

    // is v in subTree of u
    bool isInSubTree(int u, int v) {
        return (inTime[u] < inTime[v] && outTime[v] < outTime[u]);
    }

    int getLCA(int u, int v) {
        if (isInSubTree(u, v)) return u;
        if (isInSubTree(v, u)) return v;
        for (int upLen = LOG; upLen >= 0; upLen--) {
            if (!isInSubTree(parent[u][upLen], v))
                u = parent[u][upLen];
        }
        return parent[u][0];
    }

    int kthparent(int node, int k) {
        while (k > 0) {
            int x = log2(k);
            node = parent[node][x];
            k -= (1 << x);
        }
        return node;
    }
};