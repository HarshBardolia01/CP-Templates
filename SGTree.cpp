class SGTree {
public:
    vector<ll> seg;
    ll n;

    SGTree(vector<ll>& a) {
        this->n = sz(a);
        seg.resize(4 * n + 1);
        Build(a);
    }

    ll func(ll left, ll right) {
        return min(left, right);
    }

    void build(ll ind, ll low, ll high, vector<ll>& a) {
        if (low == high) {
            seg[ind] = a[low];
            return;
        }

        ll mid = low + (high - low) / 2;
        build(2 * ind + 1, low, mid, a);
        build(2 * ind + 2, mid + 1, high, a);
        seg[ind] = func(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    ll query(ll ind, ll low, ll high, ll l, ll r) {
        // no overlapping
        // l r low high OR low high l r
        // return value depends on que
        if (r < low || l > high)
            return LLONG_MAX;

        // complete overlap
        // l low high r
        if (low >= l && high <= r)
            return seg[ind];

        // partial overlap
        ll mid = low + (high - low) / 2;
        ll left = query(2 * ind + 1, low, mid, l, r);
        ll right = query(2 * ind + 2, mid + 1, high, l, r);
        return func(left, right);
    }

    void update(ll ind, ll low, ll high, ll pos, ll val) {
        if (low == high) {
            seg[ind] = val;
            return;
        }

        ll mid = low + (high - low) / 2;
        if (pos <= mid)
            update(2 * ind + 1, low, mid, pos, val);
        else
            update(2 * ind + 2, mid + 1, high, pos, val);
        seg[ind] = func(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    void Build(vector<ll>& a) {
        build(0, 0, n - 1, a);
    }

    ll Query(ll l, ll r) {
        return query(0, 0, n - 1, l, r);
    }

    void Update(ll pos, ll val) {
        update(0, 0, n - 1, pos, val);
    }
};