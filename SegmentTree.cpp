struct segtree{
    int n;
    vector<int> st, lazy;

    explicit segtree(int size) : n(size), st(4*n, 0), lazy(4*n, 0) {};



    void build(int start, int end, int cur, const vector<int>& v){
        if (start == end){
            st[cur] = v[start];
            return;
        }

        int mid = start + (end - start)/2;
        build(start, mid, 2*cur + 1, v);
        build(mid + 1, end, 2*cur + 2, v);
        st[cur] = st[2*cur + 1] + st[2*cur + 2];
    }


    int query(int l, int r, int start, int end, int cur){
        if (start > r or end < l) return 0;

        if (lazy[cur] != 0){
            st[cur] += lazy[cur]*(end - start +1);
            if (start != end){
                lazy[2*cur + 1] += lazy[cur];
                lazy[2*cur + 2] += lazy[cur];
            }
            lazy[cur] = 0;
        }

        if (start >= l and end <= r) return st[cur];

        int mid = start + (end - start)/2;
        int q1 = query(l, r, start, mid, 2*cur + 1);
        int q2 = query(l, r, mid + 1, end, 2*cur + 2);
        return (q1 + q2);
    }


    void rangeUpdate(int l, int r, int value, int start, int end, int cur){
        if (start > r or end < l) return;

        if (lazy[cur] != 0){
            st[cur] += lazy[cur]*(end - start + 1);
            if (start != end){
                lazy[2*cur + 1] += lazy[cur];
                lazy[2*cur + 2] += lazy[cur];
            }
            lazy[cur] = 0;
        }

        if (start >= l and end <= r){
            st[cur] += value*(end - start + 1);
            if (start != end){
                lazy[2*cur + 1] += value;
                lazy[2*cur + 2] += value;
            }
            return;
        }

        int mid = start + (end - start)/2;
        rangeUpdate(l, r, value, start, mid, 2*cur + 1);
        rangeUpdate(l, r, value, mid + 1, end, 2*cur + 2);
        st[cur] = st[2*cur + 1] + st[2*cur + 2];
    }


    void pointUpdate(int idx, int val, int start, int end, int cur){
        if (start > idx or end < idx) return;

        if (lazy[cur] != 0){
            st[cur] += lazy[cur]*(end-start+1);
            if (start != end){
                lazy[2*cur + 1] += lazy[cur];
                lazy[2*cur + 2] += lazy[cur];
            }
            lazy[cur] = 0;
        }

        if (start == end){
            st[cur] += val;
            return;
        }

        int mid = start + (end-start)/2;
        if (idx <= mid) pointUpdate(idx, val, start, mid, 2*cur+1);
        else pointUpdate(idx, val, mid+1, end, 2*cur+2);
        st[cur] = st[2*cur + 1] + st[2*cur + 2];
    }



    void build(const vector<int>& v){
        build(0, n-1, 0, v);
    }

    int query(int l, int r){
        return query(l, r, 0, n-1, 0);
    }

    void rangeUpdate(int l, int r, int value){
        rangeUpdate(l, r, value, 0, n-1, 0);
    }

    void pointUpdate(int idx, int val){
        pointUpdate(idx, val, 0, n-1, 0);
    }
};
