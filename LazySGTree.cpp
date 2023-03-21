class SGTree {
public:
	int n;
	vector<int> seg, lazy;

	SGTree(vector<int>& a) {
		n = sz(a);
		seg.resize(4 * n + 1);
		lazy.resize(4 * n + 1);
		Build(a);
	}

	int merge(int left, int right) {
		return (left + right);
	}

	void build(int ind, int low, int high, vector<int>& a) {
		if (low == high) {
			seg[ind] = a[low];
			return;
		}

		int mid = low + (high - low) / 2;
		build(2 * ind + 1, low, mid, a);
		build(2 * ind + 2, mid + 1, high, a);
		seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
	}

	void update(int ind, int low, int high, int l, int r, int val) {
		if (lazy[ind] != 0) {
			seg[ind] += (high - low + 1) * lazy[ind];
			if (low != high) {
				lazy[2 * ind + 1] += lazy[ind];
				lazy[2 * ind + 2] += lazy[ind];
			}
			lazy[ind] = 0;
		}

		if (r < low || high < l)
			return;

		if (l <= low && high <= r) {
			seg[ind] += (high - low + 1) * val;
			if (low != high) {
				lazy[2 * ind + 1] += val;
				lazy[2 * ind + 2] += val;
			}
			return;
		}

		int mid = low + (high - low) / 2;
		update(2 * ind + 1, low, mid, l, r, val);
		update(2 * ind + 2, mid + 1, high, l, r, val);
		seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
	}

	int query(int ind, int low, int high, int l, int r) {
		if (lazy[ind] != 0) {
			seg[ind] += (high - low + 1) * lazy[ind];
			if (low != high) {
				lazy[2 * ind + 1] += lazy[ind];
				lazy[2 * ind + 2] += lazy[ind];
			}
			lazy[ind] = 0;
		}

		if (r < low || high < l)
			return 0;

		if (l <= low && high <= r)
			return seg[ind];

		int mid = low + (high - low) / 2;
		int left = query(2 * ind + 1, low, mid, l, r);
		int right = query(2 * ind + 2, mid + 1, high, l, r);
		return left + right;
	}

	int Query(int l, int r) {
		return query(0, 0, n - 1, l, r);
	}

	void Update(int l, int r, int val) {
		update(0, 0, n - 1, l, r, val);
	}

	void Build(vector<int>& a) {
		build(0, 0, n - 1, a);
	}
};

class SGTreeMIN {
public:
	ll n;
	vector<ll> seg, lazy;

	SGTreeMIN(ll n) {
		this->n = n;
		seg.resize(4 * n + 1);
		lazy.resize(4 * n + 1, -1);
	}

	ll merge(ll left, ll right) {
		return min(left, right);
	}

	void pre(ll ind, ll low, ll high) {
		if (lazy[ind] == -1)
			return;

		seg[ind] = lazy[ind];
		if (low != high) {
			lazy[2 * ind + 1] = lazy[ind];
			lazy[2 * ind + 2] = lazy[ind];
		}
		lazy[ind] = -1;
	}

	void update(ll ind, ll low, ll high, ll l, ll r, ll val) {
		pre(ind, low, high);

		if (high < l || r < low)
			return;

		if (l <= low && high <= r) {
			lazy[ind] = val;
			pre(ind, low, high);
			return;
		}

		ll mid = low + (high - low) / 2;
		update(2 * ind + 1, low, mid, l, r, val);
		update(2 * ind + 2, mid + 1, high, l, r, val);
		seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
	}

	ll query(ll ind, ll low, ll high, ll l, ll r) {
		pre(ind, low, high);

		if (high < l || r < low)
			return LLONG_MAX;

		if (l <= low && high <= r)
			return seg[ind];

		ll mid = low + (high - low) / 2;
		ll left = query(2 * ind + 1, low, mid, l, r);
		ll right = query(2 * ind + 2, mid + 1, high, l, r);
		return merge(left, right);
	}

	void Update(ll l, ll r, ll val) {
		update(0, 0, n - 1, l, r, val);
	}

	void Update(ll pos, ll val) {
		update(0, 0, n - 1, pos, pos, val);
	}

	ll Query(ll l, ll r) {
		return query(0, 0, n - 1, l, r);
	}
};