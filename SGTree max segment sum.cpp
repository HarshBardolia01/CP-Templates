typedef struct node {
    ll pre;
    ll suf;
    ll tot;
    ll maxsum;

    node() {
        pre = LLONG_MIN;
        suf = LLONG_MIN;
        tot = LLONG_MIN;
        maxsum = LLONG_MIN;
    }
} node;

class SGTree {
public:
    vector<node> seg;
    ll n;

    SGTree(vector<ll>& a) {
        this->n = sz(a);
        seg.resize(4 * n + 1);
        Build(a);
    }

    node merge(node left, node right) {
        node res;
        res.pre = max(left.pre, left.tot + right.pre);
        res.suf = max(right.suf, right.tot + left.suf);
        res.tot = left.tot + right.tot;
        res.maxsum = max({left.maxsum, right.maxsum, left.suf + right.pre});
        return res;
    }

    void build(ll ind, ll low, ll high, vector<ll> &a) {
        if (low == high) {
            seg[ind].pre = a[low];
            seg[ind].suf = a[low];
            seg[ind].tot = a[low];
            seg[ind].maxsum = a[low];
            return;
        }

        ll mid = low + (high - low) / 2;
        build(2 * ind + 1, low , mid, a);
        build(2 * ind + 2, mid + 1, high, a);
        seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    void update(ll ind, ll low, ll high, ll pos, ll val) {
        if (low == high) {
            seg[ind].pre = val;
            seg[ind].suf = val;
            seg[ind].tot = val;
            seg[ind].maxsum = val;
            return;
        }

        ll mid = low + (high - low) / 2;
        if (pos <= mid)
            update(2 * ind + 1, low, mid, pos, val);
        else
            update(2 * ind + 2, mid + 1, high, pos, val);
        seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    node query(ll ind, ll low, ll high, ll l, ll r) {
        node t;
        if (l > high || r < low)
            return t;

        if (low >= l && high <= r)
            return seg[ind];

        ll mid = low + (high - low) / 2;
        node left = query(2 * ind + 1, low, mid, l, r);
        node right = query(2 * ind + 2, mid + 1, high, l, r);
        return merge(left, right);
    }

    void Build(vector<ll>& a) {
        build(0, 0, n - 1, a);
    }

    void Update(ll pos, ll val) {
        update(0, 0, n - 1, pos, val);
    }

    ll Query(ll l, ll r) {
        node res = query(0, 0, n - 1, l, r);
        return res.maxsum;
    }
};