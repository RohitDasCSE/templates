const long long INF = LLONG_MAX/4;


struct segtree{
    int n;
    vector<int> st, lazy;

    explicit segtree(int size) : n(size), st(4*n, INF), lazy(4*n, 0) {};



    void build(int start, int end, int cur, const vector<int>& v){
        if (start == end){
            st[cur] = v[start];
            return;
        }

        int mid = start + (end - start)/2;
        build(start, mid, 2*cur + 1, v);
        build(mid + 1, end, 2*cur + 2, v);
        st[cur] = min(st[2*cur + 1], st[2*cur + 2]);
    }


    void apply(int cur, int add){
        st[cur] += add;
        lazy[cur] += add;
    }

    void push(int cur, int start, int end){
        if (lazy[cur] == 0) return;
        if (start != end){
            apply(2*cur + 1, lazy[cur]);
            apply(2*cur + 2, lazy[cur]);
        }
        lazy[cur] = 0;
    }

    int query(int l, int r, int start, int end, int cur){
        if (start > r or end < l) return INF;
        push(cur, start, end);
        if (start >= l and end <= r) return st[cur];
        int mid = start + (end-start)/2;
        int q1 = query(l, r, start, mid, 2*cur + 1);
        int q2 = query(l, r, mid + 1, end, 2*cur + 2);
        return min(q1, q2);
    }

    void rangeUpdate(int l, int r, int value, int start, int end, int cur){
        if (start > r or end < l) return;
        push(cur, start, end);
        if (start >= l and end <= r){
            apply(cur, value);
            return;
        }
        int mid = start + (end-start)/2;
        rangeUpdate(l, r, value, start, mid, 2*cur + 1);
        rangeUpdate(l, r, value, mid + 1, end, 2*cur + 2);
        st[cur] = min(st[2*cur + 1], st[2*cur + 2]);
    }


    void pointUpdate(int idx, int val, int start, int end, int cur){
        push(cur, start, end);
        if (start == end){
            st[cur] = val;
            return;
        }
        int mid = start + (end-start)/2;
        if (idx <= mid) pointUpdate(idx, val, start, mid, 2*cur+1);
        else pointUpdate(idx, val, mid+1, end, 2*cur+2);
        st[cur] = min(st[2*cur + 1], st[2*cur + 2]);
    }



    void build(const vector<int>& v){
        build(0, n-1, 0, v);
    }

    void build(){
        const vector<int> v(n, 0);
        build(0,n-1,0,v);
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